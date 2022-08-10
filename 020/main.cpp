#include <stdio.h>
#include <unistd.h>
void longa() 
{ 
	int i,j; 
	for(i = 0; i < 1000000; i++) 
		j=i; //am I silly or crazy? I feel boring and desperate. 
} 

void foo2() 
{ 
	int i; 
	for(i=0 ; i < 10; i++) 
		longa(); 
} 

void foo1() 
{ 
	int i; 
	for(i = 0; i< 100; i++) 
		longa(); 
} 
void cs(void)
{
	printf("a\n");
	sleep(1);
}
int main(void) 
{ 
	//foo1(); 
	//foo2();
	for (int i=0; i<20; i++) {
		cs();	
	}
	return 0;
}
