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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/file.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "response.h"
#include "log.h"
using namespace std;

#define LISTEN_PORT		2333
#define LISTEN_QUEUE	24
/********************version***************************/
inline void show_version(void)
{
	    /*VERSION is a macro, defined in Makefile*/
	    printf("%s\n",VERSION);
}

/******************listen**************************/
int listen_port(uint16_t port)
{
	int server_sock;
	struct sockaddr_in local_addr;

	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);    
	local_addr.sin_addr.s_addr = INADDR_ANY;

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock) {
		log(ERROR, "socket: %s\n",strerror(errno));
		return -1;
	}
	int keepalive = 1;		//turn on keepalive
	int keepidle  = 10;		//if there is no data in this time, send detection package
	int keepintvl = 5;		//interval between two detection package
	int keepcount = 3;		//detection behavior no more than this count

	setsockopt(server_sock, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(keepintvl));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount));

	if (-1 == bind(server_sock, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		log(ERROR, "bind: %s\n",strerror(errno));
		close(server_sock);
		return -1;
	}
	if (-1 == listen(server_sock, LISTEN_QUEUE)){
		log(ERROR, "listen: %s\n",strerror(errno));
		close(server_sock);
		return -1;
	}
	return server_sock;
}
void check_exclusive(void)
{
	string path("/tmp/");	
	path += NAME;
	int fd=-1;
	fd = open(path.c_str(), O_CREAT|O_RDONLY, S_IRWXU);
	if (-1 == fd){
		log(ERROR, "check exclusive open file %s: %s\n", path.c_str(), strerror(errno));
		exit(-1);
	}
	if (-1 == flock(fd, LOCK_EX|LOCK_NB)){
		log(ERROR, "flock: %s\n",strerror(errno));
		exit(-1);
	}
}
void help(void)
{
	printf("-h : show help infomation\n");
	printf("-d : 4-debug 3-info 2-warn 1-error 0-fatal. the bigger the more, and 0(fatal) is the default\n");
	printf("-v : show version)\n");
}



int main(int argc, char *argv[])
{
	int c;
	while ((c=getopt(argc, argv, "vd:h")) != -1){
		switch(c){
			case 'v':
				show_version();
				return 0;
			case 'd':
				log_init((level_t)atoi(optarg));
				break;
			case 'h':
			default:
				help();
				return 0;
		}
	}

	check_exclusive();

	int sockfd;
	int accefd;
	sockfd = listen_port(LISTEN_PORT);
	if (-1 == sockfd){
		log(ERROR, "socket creat failed,will exit\n");
		return -1;
	}
	
	response resp;
	if (resp.init()){
		return -1;
	}

	signal(SIGPIPE, SIG_IGN);//ignore sigpipe
	while (1){
		accefd = accept(sockfd, NULL, NULL);
		if (-1 == accefd){
			log(ERROR, "accept: %s\n",strerror(errno));
			sleep(2);
			continue;
		}
		resp.add_to_epoll(accefd);
	}
	return 0;
}
