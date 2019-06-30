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
#include <stdlib.h>
#include <unistd.h>

#if (4==MODE || 5==MODE)
#include <dlfcn.h>
#endif

/**
 * situation 1:
 *
 */
void leak_fun(void)
{
	printf("enter leak_fun\n");
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
	printf("exit leak_fun\n");
}
/**
 * situation 2、3:
 *
 */
extern void shared_leak_fun(void);
#if (4==MODE || 5==MODE)
/**
 * situation 4、5:
 *
 */
void (*dynamic_leak_fun)(void) = nullptr;
int load_dynamic_lib(void)
{

	void *handle = NULL;

    handle = dlopen("./libdynamic_lib.so", RTLD_LAZY);
    if (NULL == handle) {
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */

	//dynamic_leak_fun = (void (*)())dlsym(handle, "dynamic_leak_fun");
	dynamic_leak_fun = (void (*)())dlsym(handle, "_Z16dynamic_leak_funv");
	if (NULL== dynamic_leak_fun) {
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	dynamic_leak_fun();

	dlclose(handle);
	return 0;
}
#endif
int main(void)
{
	for (int i=0; i<10; i++) {
#if (1==MODE)
		leak_fun();
#elif (2==MODE || 3==MODE)
		shared_leak_fun();
#else
		load_dynamic_lib();
#endif
	}
	printf("after memory test function\n");
	sleep(5);
	printf("will exit\n");
	return 0;
}
