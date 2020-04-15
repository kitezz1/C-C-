/*************************************************************************
	> File Name: client.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年03月09日 星期一 15时03分23秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <ctype.h>
//#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include "wrap.h"
int main(){
	
	struct sockaddr_in client;
	int cfd, lfd, n;
	char buf[1024];
	cfd = Socket(AF_INET, SOCK_STREAM, 0);
	client.sin_family = AF_INET;
	client.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);
	
	Connect(cfd, (struct sockaddr*)&client, sizeof(client));
	while(1){
	memset(buf, 0, sizeof(buf));
	Read(STDIN_FILENO, buf, sizeof(buf));
	Write(cfd, buf, strlen(buf));
	n = Read(cfd, buf, sizeof(buf));
	printf("\nbuf=%s \n", buf);
	}
	Close (cfd);

	return 0;
}
