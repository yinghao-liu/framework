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

struct thread_sem {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
	int tick = 1;
};
thread_sem g_sem_read;


int thread_sem_get(struct thread_sem *sem)
{
	printf("threadid:%lu, in thread_sem_get, mutex_lock is %d\n", pthread_self(), sem->mutex.__data.__lock);
	pthread_mutex_lock(&sem->mutex);
	printf("threadid:%lu, in thread_sem_get, get lock, tick is %d\n", pthread_self(), sem->tick);
	while (sem->tick <= 0) {
		pthread_cond_wait(&sem->cond, &sem->mutex);
	}
	sem->tick--;
	pthread_mutex_unlock(&sem->mutex);
	return 0;
}

int thread_sem_post(struct thread_sem *sem)
{
	printf("threadid:%lu, in thread_sem_post, mutex_lock is %d\n", pthread_self(), sem->mutex.__data.__lock);
	pthread_mutex_lock(&sem->mutex);
	printf("threadid:%lu, in thread_sem_post, get lock, tick is %d\n", pthread_self(), sem->tick);
	sem->tick++;
	pthread_mutex_unlock(&sem->mutex);
	pthread_cond_signal(&sem->cond);
	return 0;
}
void *waste(void *arg)
{
	while (true) {
		thread_sem_get(&g_sem_read);
		printf("thread id:%lu\n", pthread_self());
		sleep(1);
		thread_sem_post(&g_sem_read);
		sleep(1);
	}
	return nullptr;
}

int main(int argc, char *argv[]) 
{
	int ret;
	pthread_t thread1;
	pthread_t thread2;

	thread_sem_get(&g_sem_read);
	
	// thread1 and thread2 will be blocked in pthread_cond_wait after create
	ret = pthread_create(&thread1, nullptr, waste, nullptr); 
	if (0 != ret) {
		printf("pthread_create error %s\n", strerror(ret));
	}
	ret = pthread_create(&thread2, nullptr, waste, nullptr); 
	if (0 != ret) {
		printf("pthread_create error %s\n", strerror(ret));
	}

	int key;
	while (1) {
		key = getchar();
		if ('c' == key) {
			pthread_cancel(thread1);
		}
		if ('p' == key) {
			thread_sem_post(&g_sem_read);
		}
		sleep(1);
	}
	return 0;
}
