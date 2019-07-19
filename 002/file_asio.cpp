#include <string.h>
#include <stdlib.h>
#include "uv.h"

namespace file_asio {


static void on_open(uv_fs_t* req);
static void on_read(uv_fs_t* req);
static void on_write(uv_fs_t* req);
static void on_close(uv_fs_t* req);

static char *buff;
static size_t len;
static uv_buf_t uv_buf;
static uv_file fd; ///< Cross platform representation of a file handle.
static uv_loop_t *loop;
static uv_fs_t open_req;
static uv_fs_t read_req;
static uv_fs_t write_req;
static uv_fs_t close_req;

int init(size_t buff_len)
{
	len = buff_len;
	buff = (char *)malloc(len);
	if (nullptr == buff) {
		printf("init malloc error %s\n", strerror(errno));
		return -1;
	}
	uv_buf = uv_buf_init(buff, len);
	loop = uv_default_loop();

}

void start(void)
{
	uv_fs_open(loop, &open_req, "uv_file", O_RDWR | O_TRUNC |O_CREAT, S_IRWXU, on_open);
	uv_run(loop, UV_RUN_DEFAULT);
}

void on_open(uv_fs_t* req)
{
	if (req->result > 0) {
		fd = req->file; 
		uv_fs_write(loop, &write_req, fd, &uv_buf, 1, -1, on_write);
	}
	printf("on_open\n");	
}

void on_read(uv_fs_t* req)
{

}

void on_write(uv_fs_t* req)
{
	printf("on_write\n");
}

void on_close(uv_fs_t* req)
{

}

};
