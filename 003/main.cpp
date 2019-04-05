#include <iostream>
#include <dlfcn.h>

using namespace std;

int main(void)
{
	void *handle = nullptr;
	int (*module_print)(void) = nullptr;

    handle = dlopen("libs/libmodule.so", RTLD_LAZY);
    if (nullptr == handle) {
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */

	module_print = (int (*)())dlsym(handle, "module");
	if (nullptr == module_print) {
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	module_print();


	// open second time, and there is no error
	void *handle_2 = nullptr;
	int (*module_print_2)(void) = nullptr;
    handle_2 = dlopen("libs/libmodule.so", RTLD_LAZY);
    if (nullptr == handle_2) {
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */

	module_print_2 = (int (*)())dlsym(handle_2, "module");
	if (nullptr == module_print_2) {
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	module_print_2();

	dlclose(handle);
	dlclose(handle_2);
	return 0;
}
