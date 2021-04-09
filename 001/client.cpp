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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>

using namespace std;
#define SIGN	"HTTP"
#define PORT	2333
#pragma pack (1)
struct msg_head{
	uint8_t  sign[4];		// sign, e.g: HTTP
	uint16_t len;			// data len (do not contains this head)
	uint8_t  encrypt_type;  // encrypt typ(e.g: 0:none,1:xor,2:aes)
	uint8_t  keep_alive;	// if keep alive(1:keep alive)
};
#pragma pack ()

template<typename input_iter>
void xor_encrypt(input_iter first, input_iter last, string &key)
{
	size_t key_len=key.length();
	size_t index=0;
	for (input_iter iter=first; iter!=last; iter++,index++){
		if (index >= key_len){
			index = 0;
		}
		*iter ^= key[index];
	}
}
int send_data()
{

	msg_head head;
	memcpy(&head.sign, SIGN, 4);
	head.encrypt_type = 0;
	head.keep_alive = 1;
	
	int client_sock;
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == client_sock) {
		perror("socket");
		return -1;
	}
	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(PORT);    
	inet_aton("127.0.0.1", &local_addr.sin_addr);

	int len = 0;
	char *str=NULL;	
	msg_head head_rcv;
	char buff[100]={0};
	struct pollfd fds;
	connect(client_sock, (struct sockaddr*)&local_addr, sizeof (local_addr));
	for (int tick=0; tick<100; tick++){
		printf("input what should send:\n");
		scanf("%ms", &str);	
		head.len = htons(strlen(str));
		memset(&fds, 0, sizeof (fds));
		fds.fd = client_sock;
		fds.events = POLLOUT | POLLRDHUP;
		printf("POLLOUT: %x, POLLRDHUP:%x\n", POLLOUT, POLLRDHUP);
        int ret = poll(&fds, 1, 20);
		printf("poll ret:%d, fd:%d, retvent:%x\n", ret, fds.fd, fds.revents);

		len = send(client_sock, &head, sizeof (head), 0);
		printf("1send len:%d\n", len);

		memset(&fds, 0, sizeof (fds));
		fds.fd = client_sock;
		fds.events = POLLOUT | POLLRDHUP;
        ret = poll(&fds, 1, 20);
		printf("poll ret:%d, fd:%d, retvent:%x\n", ret, fds.fd, fds.revents);

		//send(client_sock, str, head.len, 0);
		len = send(client_sock, str, strlen(str), 0);
		printf("2send len:%d\n", len);
		if (NULL != str){
			free(str);
		}
		recv(client_sock, &head_rcv, sizeof (head_rcv), 0);
		head_rcv.len = ntohs(head_rcv.len);
		recv(client_sock, buff, head_rcv.len, 0);
		printf("recved: %s\n", buff);
		memset(buff, 0, head_rcv.len);
	}
	close(client_sock);
	return 0;
}
int main(void)
{
	send_data();
	return 0;
}









