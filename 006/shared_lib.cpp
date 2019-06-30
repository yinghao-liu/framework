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
/**
 * situation 2,3:
 *
 */
void shared_leak_fun(void)
{
	printf("enter shared_leak_fun\n");
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
	printf("exit shared_leak_fun\n");
}

