#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <openssl/err.h>
#include <openssl/objects.h>

static const char _asn1_mon[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static int leap_year(const int year)
{
	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
		return 1;
	return 0;
}
int ascii_isdigit(const char inchar) {
	if (inchar > 0x2F && inchar < 0x3A)
		return 1;
	return 0;
}

/*
 * Compute the day of the week and the day of the year from the year, month
 * and day.  The day of the year is straightforward, the day of the week uses
 * a form of Zeller's congruence.  For this months start with March and are
 * numbered 4 through 15.
 */
static void determine_days(struct tm *tm)
{
	static const int ydays[12] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};
	int y = tm->tm_year + 1900;
	int m = tm->tm_mon;
	int d = tm->tm_mday;
	int c;

	tm->tm_yday = ydays[m] + d - 1;
	if (m >= 2) {
		/* March and onwards can be one day further into the year */
		tm->tm_yday += leap_year(y);
		m += 2;
	} else {
		/* Treat January and February as part of the previous year */
		m += 14;
		y--;
	}
	c = y / 100;
	y %= 100;
	/* Zeller's congruence */
	tm->tm_wday = (d + (13 * m) / 5 + y + y / 4 + c / 4 + 5 * c + 6) % 7;
}

int asn1_time_to_tm(struct tm *tm, const ASN1_TIME *d)
{
	static const int min[9] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };
	static const int max[9] = { 99, 99, 12, 31, 23, 59, 59, 12, 59 };
	static const int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	char *a;
	int n, i, i2, l, o, min_l = 11, strict = 0, end = 6, btz = 5, md;
	struct tm tmp;
#if defined(CHARSET_EBCDIC)
	const char upper_z = 0x5A, num_zero = 0x30, period = 0x2E, minus = 0x2D, plus = 0x2B;
#else
	const char upper_z = 'Z', num_zero = '0', period = '.', minus = '-', plus = '+';
#endif
	if (d->type == V_ASN1_UTCTIME) {
		if (d->flags & ASN1_STRING_FLAG_X509_TIME) {
			min_l = 13;
			strict = 1;
		}
	} else if (d->type == V_ASN1_GENERALIZEDTIME) {
		end = 7;
		btz = 6;
		if (d->flags & ASN1_STRING_FLAG_X509_TIME) {
			min_l = 15;
			strict = 1;
		} else {
			min_l = 13;
		}
	} else {
		return 0;
	}

	l = d->length;
	a = (char *)d->data;
	o = 0;
	memset(&tmp, 0, sizeof(tmp));

	/*
	 * GENERALIZEDTIME is similar to UTCTIME except the year is represented
	 * as YYYY. This stuff treats everything as a two digit field so make
	 * first two fields 00 to 99
	 */

	if (l < min_l)
		goto err;
	for (i = 0; i < end; i++) {
		if (!strict && (i == btz) && ((a[o] == upper_z) || (a[o] == plus) || (a[o] == minus))) {
			i++;
			break;
		}
		if (!ascii_isdigit(a[o]))
			goto err;
		n = a[o] - num_zero;
		/* incomplete 2-digital number */
		if (++o == l)
			goto err;

		if (!ascii_isdigit(a[o]))
			goto err;
		n = (n * 10) + a[o] - num_zero;
		/* no more bytes to read, but we haven't seen time-zone yet */
		if (++o == l)
			goto err;

		i2 = (d->type == V_ASN1_UTCTIME) ? i + 1 : i;

		if ((n < min[i2]) || (n > max[i2]))
			goto err;
		switch (i2) {
			case 0:
				/* UTC will never be here */
				tmp.tm_year = n * 100 - 1900;
				break;
			case 1:
				if (d->type == V_ASN1_UTCTIME)
					tmp.tm_year = n < 50 ? n + 100 : n;
				else
					tmp.tm_year += n;
				break;
			case 2:
				tmp.tm_mon = n - 1;
				break;
			case 3:
				/* check if tm_mday is valid in tm_mon */
				if (tmp.tm_mon == 1) {
					/* it's February */
					md = mdays[1] + leap_year(tmp.tm_year + 1900);
				} else {
					md = mdays[tmp.tm_mon];
				}
				if (n > md)
					goto err;
				tmp.tm_mday = n;
				determine_days(&tmp);
				break;
			case 4:
				tmp.tm_hour = n;
				break;
			case 5:
				tmp.tm_min = n;
				break;
			case 6:
				tmp.tm_sec = n;
				break;
		}
	}

	/*
	 * Optional fractional seconds: decimal point followed by one or more
	 * digits.
	 */
	if (d->type == V_ASN1_GENERALIZEDTIME && a[o] == period) {
		if (strict)
			/* RFC 5280 forbids fractional seconds */
			goto err;
		if (++o == l)
			goto err;
		i = o;
		while ((o < l) && ascii_isdigit(a[o]))
			o++;
		/* Must have at least one digit after decimal point */
		if (i == o)
			goto err;
		/* no more bytes to read, but we haven't seen time-zone yet */
		if (o == l)
			goto err;
	}

	/*
	 * 'o' will never point to '\0' at this point, the only chance
	 * 'o' can point to '\0' is either the subsequent if or the first
	 * else if is true.
	 */
	if (a[o] == upper_z) {
		o++;
	} else if (!strict && ((a[o] == plus) || (a[o] == minus))) {
		int offsign = a[o] == minus ? 1 : -1;
		int offset = 0;

		o++;
		/*
		 * if not equal, no need to do subsequent checks
		 * since the following for-loop will add 'o' by 4
		 * and the final return statement will check if 'l'
		 * and 'o' are equal.
		 */
		if (o + 4 != l)
			goto err;
		for (i = end; i < end + 2; i++) {
			if (!ascii_isdigit(a[o]))
				goto err;
			n = a[o] - num_zero;
			o++;
			if (!ascii_isdigit(a[o]))
				goto err;
			n = (n * 10) + a[o] - num_zero;
			i2 = (d->type == V_ASN1_UTCTIME) ? i + 1 : i;
			if ((n < min[i2]) || (n > max[i2]))
				goto err;
			/* if tm is NULL, no need to adjust */
			if (tm != NULL) {
				if (i == end)
					offset = n * 3600;
				else if (i == end + 1)
					offset += n * 60;
			}
			o++;
		}
		if (offset && !OPENSSL_gmtime_adj(&tmp, 0, offset * offsign))
			goto err;
	} else {
		/* not Z, or not +/- in non-strict mode */
		goto err;
	}
	if (o == l) {
		/* success, check if tm should be filled */
		if (tm != NULL)
			*tm = tmp;
		return 1;
	}
err:
	return 0;
}

int do_time_print(const ASN1_TIME *tm)
{
	char *v;
	int gmt = 0, l;
	struct tm stm;
	const char upper_z = 0x5A, period = 0x2E;

	if (!asn1_time_to_tm(&stm, tm)) {
		/* asn1_time_to_tm will check the time type */
		goto err;
	}

	l = tm->length;
	v = (char *)tm->data;
	if (v[l - 1] == upper_z)
		gmt = 1;

	/*if (tm->type == V_ASN1_GENERALIZEDTIME) {
		char *f = NULL;
		int f_len = 0;

		if (tm->length > 15 && v[14] == period) {
			f = &v[14];
			f_len = 1;
			while (14 + f_len < l && ascii_isdigit(f[f_len]))
				++f_len;
		}

		return BIO_printf(bp, "%s %2d %02d:%02d:%02d%.*s %d%s",
				_asn1_mon[stm.tm_mon], stm.tm_mday, stm.tm_hour,
				stm.tm_min, stm.tm_sec, f_len, f, stm.tm_year + 1900,
				(gmt ? " GMT" : "")) > 0;
	} else {*/
			printf("%s %2d %02d:%02d:%02d %d%s\n",
				_asn1_mon[stm.tm_mon], stm.tm_mday, stm.tm_hour,
				stm.tm_min, stm.tm_sec, stm.tm_year + 1900,
				(gmt ? " GMT" : ""));
	//}
err:
	return 0;
}

int do_name_ex(const X509_NAME *n)
{
	int cnt = 0;
	int i = 0;
	int fn_nid;
	const char *objbuf;
	const X509_NAME_ENTRY *ent;
	ASN1_OBJECT *fn;
	const ASN1_STRING *val;

	cnt = X509_NAME_entry_count(n);
	for (i = 0; i < cnt; i++) {
		ent = X509_NAME_get_entry(n, i);
		//prev = X509_NAME_ENTRY_set(ent);
		fn = X509_NAME_ENTRY_get_object(ent);
		val = X509_NAME_ENTRY_get_data(ent);
		fn_nid = OBJ_obj2nid(fn);
		objbuf = OBJ_nid2sn(fn_nid);
		printf("%s:%s\n", objbuf, val->data);
	}
	return 0;
}

X509 *load_x509_crt(const char *file_name)
{
	FILE *fp = NULL;
	fp = fopen(file_name, "r");
	if (NULL == fp) {
		fprintf(stderr, "unable to open: %s\n", file_name);
		return NULL;
	}
	X509 *cert = NULL;
	cert = PEM_read_X509(fp, NULL, NULL, NULL);
	if (NULL == cert) {
		fprintf(stderr, "unable to parse certificate\n");
		fclose(fp);
		return NULL;
	}
	return cert;
}

EVP_PKEY *load_x509_pkey(const char *file_name)
{
	FILE *fp = NULL;
	fp = fopen(file_name, "r");
	if (NULL == fp) {
		fprintf(stderr, "unable to open: %s\n", file_name);
		return NULL;
	}
	EVP_PKEY *key = NULL;
	key = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
	if (NULL == key) {
		fprintf(stderr, "unable to parse private key\n");
		fclose(fp);
		return NULL;
	}
	return key;
}

int i2ns_ASN1_INTEGER(const ASN1_INTEGER *a, char *sout, size_t len)
{
	int i, n = 0;
	static const char *h = "0123456789ABCDEF";

	if (a == NULL || len < 16)
		return 0;

	if (a->type & V_ASN1_NEG) {
		if (sprintf(sout, "-") != 1)
			goto err;
		n = 1;
	}

	if (a->length == 0) {
		if (sprintf(sout, "00") != 2)
			goto err;
		n += 2;
	} else {
		for (i = 0; i < a->length; i++) {
			if ((i != 0) && (i % 35 == 0)) {
				if (sprintf(sout, "\\\n") != 2)
					goto err;
				n += 2;
			}
			if (n+2 >= len) {
				break;
			}
			sout[n++] = h[((unsigned char)a->data[i] >> 4) & 0x0f];
			sout[n++] = h[((unsigned char)a->data[i]) & 0x0f];
		}
	}
	return n;
err:
	return -1;
}
int main(void)
{
	int ret = -1;
	char buff[128] = {};

	X509 *cert = NULL;
	cert = load_x509_crt("server.crt");
	if (NULL == cert) {
		return -1;
	}
	/*
	X509_check_private_key()  return 1 if the keys match each other, and 0 if not.
	If the key is invalid or an error occurred, the reason code can be obtained using ERR_get_error(3).
	*/
#if 0
	EVP_PKEY *key = NULL;
	key = load_x509_pkey("server.key");
	if (NULL == key) {
		return -1;
	}
	int private_key_check = 0;
	private_key_check = X509_check_private_key(cert, key);
	printf("X509_check_private_key ret: %d\n", private_key_check);
	return 0;
#endif
	/* X509_get_version() returns the numerical value of the
	 * version field of certificate x. Note: this is defined
	 * by standards (X.509 et al) to be one less than the certificate
	 * version. So a version 3 certificate will return 2 and
	 * a version 1 certificate will return 0
	 */
	long ver = -1;
	ver = X509_get_version(cert);
	printf("V%ld\n", ver+1);

	ASN1_INTEGER *serialNumber = NULL;
	serialNumber = X509_get_serialNumber(cert);
	/*
	unsigned char abc[20] = {};
	unsigned char *aa = abc;
	int ret = i2d_ASN1_INTEGER(serialNumber, &aa);
	printf("%d:%s\n", ret, abc);
	*/
	ret = i2ns_ASN1_INTEGER(serialNumber, buff, sizeof (buff));
	printf("serialNumber %d:%s\n", ret, buff);

	do_name_ex(X509_get_issuer_name(cert));

	do_time_print(X509_get0_notBefore(cert));
	do_time_print(X509_get0_notAfter(cert));

	X509_NAME_oneline(X509_get_subject_name(cert), buff, 64);
	return 0;
}
