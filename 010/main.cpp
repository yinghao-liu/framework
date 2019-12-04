#include <stdio.h>
#include <stdint.h>
#include "patterns.h"
using namespace std;

int main(void)
{
	auto a = singleton::get_instance();
	auto b = singleton::get_instance();
	singleton c = (*a);
	shared_ptr<singleton> d(a);

	a->show();
	b->show();
	c.show();
	d->show();


	return 0;
}
