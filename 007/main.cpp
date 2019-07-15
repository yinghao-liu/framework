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
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

/******************* user head files ******************/
#include "syscap.h"


syscap_t g_syscap;
struct pthread_args {
	char name[16];					///< The name can be up to 16 bytes long, including the terminating null byte
	int policy = SCHED_OTHER;		///< scheduling policy, SCHED_OTHER default
	int priority = 0;				///< priority, it's always 0 for normal policy(not real-time ones)
};

const char *g_policy_name[10] = {nullptr};

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
void *waste(void *arg)
{
	int ret;
	char errmsg[64] = {0};

	pthread_args *args = (pthread_args *)arg;
	if (nullptr != args) {
		printf("-------pthread name is %s\n", args->name);
		pthread_setname_np(pthread_self(), args->name);
	}
	print_thread_cpulist(0);

	cpu_set_t cpu_mask;
	CPU_ZERO(&cpu_mask);
	CPU_SET(1, &cpu_mask);
	sched_setaffinity(0, sizeof (cpu_set_t), &cpu_mask);
	print_thread_cpulist(0);

	int policy;
	struct sched_param param;
	memset(&param, 0, sizeof (param));
	policy = sched_getscheduler(0);
	printf("policy is %d:%s\n", policy, g_policy_name[policy]);

	int priority;
	priority =  getpriority(PRIO_PROCESS, 0);
	printf("policy(nice value) is %d\n", priority);

	printf("policy set to %d:%s\n", SCHED_BATCH, g_policy_name[SCHED_BATCH]);
	param.sched_priority = 0; // param->sched_priority must be 0. for those not "real-time" policy
	ret = sched_setscheduler(0, SCHED_BATCH, &param);
	if (0 != ret) {
		printf("sched_setscheduler error %s\n", strerror_r(errno, errmsg, sizeof (errmsg)));
	}
	policy = sched_getscheduler(0);
	printf("policy is %d:%s\n", policy, g_policy_name[policy]);



	int i = 0;
	while (1) {
		i++;
	}
	return nullptr;
}


int sys_init(void)
{
	int max;
	int min;

	printf("---------- normal scheduling policies ----------\n");
	g_policy_name[SCHED_OTHER] = "SCHED_OTHER";
	max = sched_get_priority_max(SCHED_OTHER);
	min = sched_get_priority_min(SCHED_OTHER);
	printf("SCHED_OTHER is %u, %d-%d\n", SCHED_OTHER, min, max);

	g_policy_name[SCHED_BATCH] = "SCHED_BATCH";
	max = sched_get_priority_max(SCHED_BATCH);
	min = sched_get_priority_min(SCHED_BATCH);
	printf("SCHED_BATCH is %u, %d-%d\n", SCHED_BATCH, min, max);

	g_policy_name[SCHED_IDLE] = "SCHED_IDLE";
	max = sched_get_priority_max(SCHED_IDLE);
	min = sched_get_priority_min(SCHED_IDLE);
	printf("SCHED_IDLE is %u, %d-%d\n", SCHED_IDLE, min, max);

	g_policy_name[SCHED_DEADLINE] = "SCHED_DEADLINE";
	max = sched_get_priority_max(SCHED_DEADLINE);
	min = sched_get_priority_min(SCHED_DEADLINE);
	printf("SCHED_DEADLINE is %u, %d-%d\n", SCHED_DEADLINE, min, max);

	printf("---------- real-time policies ----------\n");
	g_policy_name[SCHED_FIFO] = "SCHED_FIFO";
	max = sched_get_priority_max(SCHED_FIFO);
	min = sched_get_priority_min(SCHED_FIFO);
	printf("SCHED_FIFO is %u, %d-%d\n", SCHED_FIFO, min, max);

	g_policy_name[SCHED_RR] = "SCHED_RR";
	max = sched_get_priority_max(SCHED_RR);
	min = sched_get_priority_min(SCHED_RR);
	printf("SCHED_RR is %u, %d-%d\n", SCHED_RR, min, max);
	printf("---------- policies end ----------\n");

	return 0;
}

int get_sys_capacity(void)
{
	g_syscap.cpu_num = sysconf(_SC_NPROCESSORS_CONF);
	printf("g_syscap.cpu_num : %ld\n", g_syscap.cpu_num);
	return 0;
}

int main(int argc, char *argv[]) 
{
	sys_init();
	get_sys_capacity();
	
	int ret;
	pthread_t thread;
	pthread_args pargs;
	snprintf(pargs.name, sizeof (pargs.name), "waste1");
	ret = pthread_create(&thread, nullptr, waste, &pargs); 
	if (0 != ret) {
		printf("pthread_create error %s\n", strerror(ret));
	}
	while (1) {
		sleep(1);
	}
	return 0;
}
