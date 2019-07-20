#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "uv.h"
#include "file_asio.h"
using namespace std;
using namespace file_asio;


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

int tcp_init(uv_loop_t* loop)
{
	 uv_tcp_t handle;
	 uv_tcp_init(loop, &handle);

	
}

void general_io(void)
{
	int fd;
	fd = open("general_file", O_RDWR | O_TRUNC |O_CREAT, S_IRWXU);
	if (-1 == fd) {
		perror("open general_file");
		return;
	}
	for (int i=0; i<g_max_tick; i++) {
		//write(fd, "file test", sizeof (FILE_IO_TEST));
		write(fd, write_string, strlen(write_string));
	}
	close(fd);
}

void general_buffio(void)
{
	FILE *fd;
	fd = fopen("general_buff_file", "w");
	if (nullptr == fd) {
		perror("open general_file");
		return;
	}
	for (int i=0; i<g_max_tick; i++) {
	//for (int i=0; i<1; i++) {
		fwrite(write_string, strlen(write_string), 1, fd);
	}
	fclose(fd);
}

void uv_io(void)
{
	init();
	start();
}
int main(int argc, char *argv[])
{
	if (1 == atoi(argv[1])) {
		general_io();
	} else if (2 == atoi(argv[1])) {
		general_buffio();
	} else if (3 == atoi(argv[1])) {
		uv_io();
	}

	return 0;

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
	uv_idle_t idle_event;
	uv_idle_init(loop, &idle_event);
	uv_idle_start(&idle_event, idle_cb);

	uv_print_all_handles(loop, stdout);

	cout<<"before run"<<endl;
	uv_run(loop, UV_RUN_DEFAULT);
	//this will never run
	cout<<"after run"<<endl;
	return 0;
}
