#include <iostream>
#include "uv.h"
using namespace std;
int counter = 0;
void timer_cb(uv_timer_t* handle)
{
	cout<<"this is from libuv timer"<<endl;
}

void idle_cb(uv_idle_t* handle)
{

	//printf("in wait_for_a_while\n");
	counter++;
	if (counter >= 12)
		uv_idle_stop(handle);
}

void fs_event_cb(uv_fs_event_t* handle, const char* filename, int events, int status)
{
	printf("%s:%d,%d\n", filename, events, status);
}
int main(void)
{
	uv_loop_t *loop;
	loop = uv_default_loop();

	// timer event
	//uv_timer_t timer_event;
	//uv_timer_init(loop, &timer_event);
	//timeout and repeat are in milliseconds
	//uv_timer_start(&timer_event, timer_cb, 5000, 2000);

	// fs event
	uv_fs_event_t fs_event;
	uv_fs_event_init(loop, &fs_event);
	uv_fs_event_start(&fs_event, fs_event_cb, "test_file", UV_FS_EVENT_WATCH_ENTRY);

	// idle event
	//uv_idle_t idle_event;
	//uv_idle_init(loop, &idle_event);
	//uv_idle_start(&idle_event, idle_cb);

	cout<<"before run"<<endl;
	uv_run(loop, UV_RUN_DEFAULT);
	//this will never run
	cout<<"after run"<<endl;
	return 0;
}
