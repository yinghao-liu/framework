#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

void get_tcp_socket_info(int tcp_sock)
{
	struct tcp_info info;
	int len=sizeof(info);
	int ret = 0;
	ret = getsockopt(tcp_sock, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
	printf("info.state:%u\n", info.tcpi_state);
}
int listen_port(uint16_t port)
{
	int server_sock;
	struct sockaddr_in local_addr;

	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	//local_addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "127.0.0.1", &local_addr.sin_addr);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock) {
		return -1;
	}
	get_tcp_socket_info(server_sock);
	int keepalive = 1;		//turn on keepalive
	int keepidle  = 10;		//if there is no data in this time, send detection package
	int keepintvl = 5;		//interval between two detection package
	int keepcount = 3;		//detection behavior no more than this count

	setsockopt(server_sock, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(keepintvl));
	setsockopt(server_sock, SOL_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount));

	if (-1 == bind(server_sock, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		close(server_sock);
		return -1;
	}
	get_tcp_socket_info(server_sock);

	if (-1 == listen(server_sock, 10)){
		close(server_sock);
		return -1;
	}
	get_tcp_socket_info(server_sock);
	return server_sock;
}
int main()
{
	listen_port(1033);
	return 0;
}
