#include <stdio.h>
#include "external_module.h"

int module(void)
{
	printf("here from module\n");
	external_module();
	return 0;
}
