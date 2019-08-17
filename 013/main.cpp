#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "debug/debug.h"

int leak_test(void)
{
	char *buf = NULL;
	int tick = 0;
	while (!g_debug_quit) {
		buf = (char *)malloc(1024);
		tick++;
		printf("leak_test tick %d\n", tick);
		sleep(3);
	}
	return 0;
}


int main(void)
{
	// after debug_init, only when receive signal DEBUG_QUIT_SIG
	// g_debug_quit turns to true
	debug_init();

	leak_test();

	// all threads should end it's process
	// when g_debug_quit is true or receive signal DEBUG_QUIT_SIG
	while (!g_debug_quit) {
		pause();
	}
	printf("all clean up\n");
	return 0;
}
