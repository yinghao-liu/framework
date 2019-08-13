#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int g_debug_quit = false;
/**
 * SIGUSR1 for normal return (not exit) process, that can do a memory detecte
 *
 */
void debug_sig_handle(int sig)
{
	printf("\n----%d----\n", sig);
	g_debug_quit = true;
}

int debug_init(void)
{
	int ret = -1;
	struct sigaction sig_act;
	memset(&sig_act, 0, sizeof (sig_act));
	sig_act.sa_handler = debug_sig_handle;
	ret = sigaction(SIGUSR1, &sig_act, NULL);
	if (0 != ret) {
		perror("sigaction");
	}
	return ret;
}

