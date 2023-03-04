int param_and_return(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int x = 0;
	x = a+b+c+d+e+f+g+h;
	return x;
}

void test_param_and_return(void)
{
	int ret = 0;
	ret = param_and_return(1,2,3,4,5,6,7,8);
}

int main(void)
{
	test_param_and_return();
	return 0;
}
