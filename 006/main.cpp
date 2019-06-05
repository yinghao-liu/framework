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
/**
 * situation 1:
 *
 */
void leak_fun(void)
{
	char *waste=nullptr;
	waste = (char *)malloc(4*1024);
	waste[0] = 1;
	waste[1] = waste[0];
}

int main(void)
{
	for (int i=0; i<10; i++) {
		leak_fun();
	}
	printf("after leak function\n");
	for (int i=0; i<5; i++) {
		sleep(1);
	}
	printf("will exit\n");
	return 0;
}
