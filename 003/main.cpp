#include <iostream>
#include <dlfcn.h>

using namespace std;

int main(void)
{
	int (*module_print)(void) = nullptr;
	void *handle = nullptr;

    handle = dlopen("libs/libmodule.so", RTLD_LAZY);
    if (nullptr == handle){
		printf("dlopen error, %s\n", dlerror());
		return -1;
    }
	dlerror();    /* Clear any existing error */
	module_print = (int (*)())dlsym(handle, "module");
	if (nullptr == module_print){
		printf("dlsym module error, %s\n", dlerror());
		return -1;
	}
	module_print();
	dlclose(handle);
	return 0;
}
