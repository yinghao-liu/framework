#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "debug/debug.h"

int main(void)
{
	debug_init();

	char *buf = NULL;
	buf = (char *)malloc(1024);

	while (!g_debug_quit) {
		sleep(2);
	}
	return 0;
}
