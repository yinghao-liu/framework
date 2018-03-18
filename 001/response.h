/*
 * Copyright (C) 2018 francis_hao <francis_hao@126.com>
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
#ifndef _NDREQUEST_H_
#define _NDREQUEST_H_
#include <map>
#include <string>
#include <mqueue.h>
#include <stdint.h>
#include <pthread.h>
using std::map;
using std::string;

#pragma pack (1)
struct msg_head{
	uint8_t  sign[4];		// sign, e.g: HTTP
	uint16_t len;			// data len (do not contains this head)
	uint8_t  encrypt_type;  // encrypt typ(e.g: 0:none,1:xor,2:aes)
	uint8_t  keep_alive;	// if keep alive(1:keep alive)
};
#pragma pack ()
struct request_data{
	int fd;
	uint16_t len;
	uint8_t  encrypt_type;
	uint8_t  keep_alive;
	time_t modify;	/*last time of data modify*/
	string data;
};
class response{
public:
	int init(int pth_num=6);
	void add_to_epoll(int accefd);
	~response();
protected:
	int epoll_init(void);
	int pthread_init(int pth_num);
	int mq_init(void);
	static void *write_to_mq(void *arg);
	static void *read_from_mq(void *arg);
	void purge(void);
	int process_connection(int fd);
	int recv_head(request_data &req_head);
	int recv_body(request_data *req_body);
	int response_op(request_data *req_body);

private:
	int ep_fd;		// epoll fd, for waiting reading
	string mq_name;
	mqd_t mq_fd;
	map<int, request_data> conn;

	int pth_read_num;
	pthread_t *pth_read;
	pthread_t pth_write;
};

#endif
