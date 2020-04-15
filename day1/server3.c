/*************************************************************************
	> File Name: server3.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年03月08日 星期日 17时12分04秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
int main(){
	
	int lfd, cfd;
	struct sockaddr_in server,client;
	int n, i;
	char buf[1024];
	char str[1024];

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(6666);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (struct sockaddr*)&server, sizeof(server));
	listen(lfd, 128);
	printf("ready accept...\n");
	while(1){
		socklen_t client_len = sizeof(client);
		cfd = accept(lfd, (struct sockaddr*)&client, &client_len);
		n = read(cfd, buf, sizeof(buf));
		printf("\nn=%d", n);
		for(i=0; i<n; i++)
			buf[i] = toupper(buf[i]);
		write(cfd, buf, n);
	}

	return 0;
}
