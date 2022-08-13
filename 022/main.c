#include <stdio.h>
#include <time.h>
#include <sys/time.h>

long gettime(int type)
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	//return tp.tv_nsec;

	switch (type){
	case 0:
		return tp.tv_nsec;
	case 1:// s
		return (long)tp.tv_sec;
	case 2:// ms
		return (long)tp.tv_sec*1000 + tp.tv_nsec/1000000;
	case 3:// us
		return (long)tp.tv_sec*1000000 + tp.tv_nsec/1000;
	case 4:// ns
		return (long)tp.tv_sec*1000000000 + tp.tv_nsec;
	default:
		return 0;
	}
}


int main(void)
{
	/*
	long data1 = 0;
	long data2 = 0;
	long data3 = 0;
	long data41 = 0;
	long data42 = 0;

	long fast1 = 0;
	long fast2 = 0;

	data1 = gettime(1);
	data2 = gettime(2);
	data3 = gettime(3);
	data41 = gettime(4);
	data42 = gettime(4);

	fast1 = gettime(0);
	fast2 = gettime(0);

	printf("second:%ld\n", data1);
	printf("millisecond:%ld\n", data2);
	printf("microsecond:%ld\n", data3);

	printf("------------------------------\n");
	printf("nanosecond1:%ld\n", data41);
	printf("nanosecond2:%ld\n", data42);

	printf("gettime cost: %ld ns\n",data42-data41);


	printf("------------------------------\n");
	printf("fast nanosecond1:%ld\n", fast1);
	printf("fast nanosecond2:%ld\n", fast2);
	printf("gettimefast cost: %ld ns\n",fast2-fast1);
	*/

	struct timeval ttimeEnd;
	struct timespec tp1;

	struct timespec tp2;
	struct timespec tp3;
	struct timespec tp4;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	clock_gettime(CLOCK_MONOTONIC, &tp2);

	clock_gettime(CLOCK_MONOTONIC, &tp3);
	gettimeofday(&ttimeEnd, NULL);
	clock_gettime(CLOCK_MONOTONIC, &tp4);
	printf("package cost: %ld ns\n",tp2.tv_nsec-tp1.tv_nsec);
	printf("clock_gettime  cost: %ld ns\n",tp3.tv_nsec-tp1.tv_nsec);
	printf("gettimeofday cost:   %ld ns\n",tp4.tv_nsec-tp3.tv_nsec);

	/*int i;
	for (i=0; i<10000000;i++){
		clock_gettime(CLOCK_MONOTONIC, &tp1);
		gettimeofday(&ttimeEnd, NULL);
	}*/

	return 0;
}
