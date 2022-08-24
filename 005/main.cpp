/*
 * Copyright (C) 2019 francis_hao <francis_hao@126.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

void backtrace_print(void)
{
	void *buff[16] = {NULL};
	char **symbols = NULL;
	int num_of_symb = 0;

	num_of_symb = backtrace(buff, sizeof (buff));
	printf("backtrace() returned %d addresses\n", num_of_symb);
	symbols = backtrace_symbols(buff, num_of_symb);
	if (NULL == symbols) {
		perror("backtrace_symbols");
		return;
	}
	for (int i=0; i<num_of_symb; i++) {
		printf("%s\n", symbols[i]);
	}
	free(symbols);
}

void sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	ucontext_t *context = (ucontext_t *)ucontext;
	printf("signal %u\n", sig);
	backtrace_print();
	exit(-1);
}



int core_dump_init(void)
{
	struct sigaction sigact;
	memset(&sigact, 0, sizeof (sigact));
	sigact.sa_flags = SA_SIGINFO; //use sa_sigaction instead of sa_handler
	sigact.sa_sigaction = sig_handler;
	int ret = -1;
	ret = sigaction(SIGSEGV, &sigact, NULL);
	if (0 != ret) {
		perror("sigaction");
		return -1;
	}
	return 0;
}


int main(void)
{
	core_dump_init();
	// here bombbbbb
	*((char *)NULL) = 0;
	return 0;
}
