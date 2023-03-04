#include <stdio.h>

int over_stack(int *p)
{
	printf("*p:%d\n", *p);
	p[20] = 20;
	return 0;
}
int main()
{
	int a[10]={};
	int b[10] = {};
	printf("a:%p, b:%p\n", a, b);
	printf("a[9]:%p a[10]:%p\n", &a[9], &a[10]);
	over_stack(a);
}

