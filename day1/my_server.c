/*************************************************************************
	> File Name: my_server.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年03月08日 星期日 10时32分46秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERV_PORT 6666
int main(){

	struct sockaddr_in servaddr, cliaddr;
	socklen_t cliaddr_len;

	int listenfd, connfd;
	char buf[1024];
	char str[1024];
	int i, n;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 20);
	printf("Accepting connetcs ..\n");

	while(1){
		cliaddr_len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*)&cliaddr,  &cliaddr_len);
		n = read(connfd, buf, sizeof(buf));
		printf("reaceive from %s at port %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
				ntohs(cliaddr.sin_port)
				);
		for (i = 0; i<n; i++)
			buf[i] = toupper(buf[i]);
		write(connfd, buf, n);
		close(connfd);
		}
	return 0;
}
