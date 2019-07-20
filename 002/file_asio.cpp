#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "file_asio.h"
#include "uv.h"

namespace file_asio {


static void on_open(uv_fs_t* req);
static void on_read(uv_fs_t* req);
static void on_write(uv_fs_t* req);
static void on_close(uv_fs_t* req);

static char buff[25];
static size_t len;
static uv_buf_t uv_buf;
static uv_file fd; ///< Cross platform representation of a file handle.
static uv_loop_t *loop;
static uv_fs_t open_req;
static uv_fs_t read_req;
static uv_fs_t write_req;
static uv_fs_t close_req;
static int write_tick = 0;

int init(size_t buff_len)
{
	strncpy(buff, write_string, sizeof (buff));
	uv_buf = uv_buf_init(buff, len);
	loop = uv_default_loop();
}

void on_open(uv_fs_t* req)
{
	if (req->result > 0) {
		fd = req->result; 
		uv_buf.base = buff;
		uv_buf.len = strlen(write_string);
		uv_fs_write(loop, &write_req, fd, &uv_buf, 1, -1, on_write);
	}
	//printf("on_open\n");	
}

void on_read(uv_fs_t* req)
{

}

void on_write(uv_fs_t* req)
{
	write_tick++;
	if (write_tick >= g_max_tick) {
		uv_fs_close(loop, &close_req, fd, nullptr);
		return;
	}
	uv_fs_write(loop, &write_req, fd, &uv_buf, 1, -1, on_write);
}

void on_close(uv_fs_t* req)
{

}

void start(void)
{
	uv_fs_open(loop, &open_req, "uv_file", O_RDWR | O_TRUNC |O_CREAT, S_IRWXU, on_open);
	uv_run(loop, UV_RUN_DEFAULT);
}

};
