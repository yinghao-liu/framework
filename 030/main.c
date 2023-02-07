#include <time.h>
#include <stdio.h>
#include <string.h>

void show_timeparam()
{
	int i = 0;
	for (i=0; i<2; i++) {
		if (NULL == tzname[i]) {
			break;
		}
		printf("tzname[%d]: %s\n", i, tzname[i]);
	}

	printf("timezone: %ld\n", timezone);
	printf("daylight: %d\n", daylight);
}
int main()
{
	show_timeparam();
	tzset();
	printf("--------------------\n");
	show_timeparam();


	char dst[11] = {};
	const char *src = "12345";
	printf("dst addr is %p\n", dst);
	snprintf(dst, sizeof (dst), "abc");
	size_t size = sizeof (dst);
	size_t len = strlen(dst);
	strncat(dst, src, -2);
	printf("dst %s\n", dst);
	len = strlen(dst);
	return 0;
}
