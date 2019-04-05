//#include <iostream>
#include <dlfcn.h>
#include <stdio.h>

#include "main_module/main_module.h"
//using namespace std;
int load(void)
{

	//external_module();

	void *handle = NULL;
	int (*module_print)(void) = NULL;

    handle = dlopen("libs/libmodule.so", RTLD_LAZY);
    if (NULL == handle) {
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */

	module_print = (int (*)())dlsym(handle, "module");
	if (NULL== module_print) {
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	module_print();


	// open second time, and there is no error
	void *handle_2 = NULL;
	int (*module_print_2)(void) = NULL;
    handle_2 = dlopen("libs/libmodule.so", RTLD_LAZY);
    if (NULL == handle_2) {
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */

	module_print_2 = (int (*)())dlsym(handle_2, "module");
	if (NULL == module_print_2) {
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	module_print_2();

	dlclose(handle);
	dlclose(handle_2);
	return 0;
}

int main(void)
{
	external_module(); // 
	load();
	return 0;
}
