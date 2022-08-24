#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int modify_u32(uint32_t *number)
{
	*number = 0xffffffff;
	// *number = 0xff;
	return 0;
}
void *memory_leak(void *param){
	char *p = malloc(8);
	pthread_exit(NULL);
	while (1){
		sleep(2);
	}
}

int newThread(){
	int ret;
	pthread_t thread;
	ret = pthread_create(&thread, NULL, memory_leak,NULL);
	printf("pthread_create ret is %d\n",ret);
	pthread_join(thread,NULL);
}
int newThreadDetach(){
	int ret;
	pthread_t thread;
	ret = pthread_create(&thread, NULL, memory_leak,NULL);
	printf("pthread_create ret is %d\n",ret);
	//pthread_detach(thread);
}
int main(void)
{
	uint16_t num = 0;
	uint16_t *nump = malloc(sizeof (uint16_t));
	uint16_t *nump2 = malloc(sizeof (uint16_t));
	free(nump2);
	modify_u32(nump);
	//newThread();
	newThreadDetach();
	while(1){
		sleep(1);
	}
	//sleep(1);
	return 0;
}
