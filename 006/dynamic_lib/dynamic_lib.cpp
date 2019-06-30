#include <stdio.h>
#include <stdlib.h>
/**
 * situation 4,5:
 *
 */
void dynamic_leak_fun(void)
{
	printf("enter dynamic_leak_fun\n");
	char *waste=nullptr;
	char tmp;
	waste = (char *)malloc(1024);
	printf("waste1 pointer: %p\n", waste);
	waste[0] = 1;
	//error 1: out-of-bounds
	waste[1024] = 2;
	tmp = waste[1024];
	//error 2: use-after-free
	free(waste);
	waste[0] = 1;
	//error 3: memory-leak
	waste = (char *)malloc(1024);
	printf("waste2 pointer: %p\n", waste);
	printf("exit dynamic_leak_fun\n");
}

