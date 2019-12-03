#include <stdio.h>
#include <stdint.h>
#include "patterns.h"

int main(void)
{
	auto a = singleton::get_instance();
	auto b = singleton::get_instance();
	a->show();
	b->show();

	return 0;
}
