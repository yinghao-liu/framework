#include <iostream>
#include "uv.h"
using namespace std;

void uv_timercb(uv_timer_t* handle)
{
	cout<<"this is from libuv timer"<<endl;
}

int main(void)
{
	uv_loop_t *timer_loop=uv_default_loop();
	uv_timer_t timer_req;
	uv_timer_init(timer_loop, &timer_req);
	//timeout and repeat are in milliseconds
	uv_timer_start(&timer_req, uv_timercb, 5000, 2000);
	cout<<"before run"<<endl;
	uv_run(timer_loop, UV_RUN_DEFAULT);
	//this will never run
	cout<<"after run"<<endl;
	return 0;
}
