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
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

/*******************user head files******************/
#include "syscap.h"


syscap_t g_syscap;

void print_thread_cpulist(pid_t pid)
{
	char buffer[256] = {0};
	char buffer_tmp[256] = {0};
	sprintf(buffer, "pid is %d\n", getpid());
	sprintf(buffer_tmp, "thread id is %#lx\n", pthread_self());
	strcat(buffer, buffer_tmp);

	cpu_set_t cpu_mask;
	sched_getaffinity(0, sizeof (cpu_set_t), &cpu_mask);
	sprintf(buffer_tmp, "cpu: ");
	strcat(buffer, buffer_tmp);
	for (int i=0; i<g_syscap.cpu_num; i++) {
		if (1 == CPU_ISSET(i, &cpu_mask)) {
			sprintf(buffer_tmp, "%d,", i);
			strcat(buffer, buffer_tmp);
		}
	}
	sprintf(buffer_tmp, "\b \n");
	strcat(buffer, buffer_tmp);
	printf("%s", buffer);
}
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
void waste(void *arg)
{
	print_thread_cpulist(0);
	cpu_set_t cpu_mask;
	CPU_ZERO(&cpu_mask);
	CPU_SET(1, &cpu_mask);
	sched_setaffinity(0, sizeof (cpu_set_t), &cpu_mask);
	print_thread_cpulist(0);
	int i = 0;
	while (1) {
		i++;
	}
}

int get_sys_capacity(void)
{
	g_syscap.cpu_num = sysconf(_SC_NPROCESSORS_CONF);
	printf("g_syscap.cpu_num : %ld\n", g_syscap.cpu_num);
	return 0;
}

int main(int argc, char *argv[]) 
{
	get_sys_capacity();

	waste(NULL);
	return 0;
}
