/*************************************************************************
	> File Name: my_client.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年03月08日 星期日 09时54分08秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <arap/inet.h>
int main(){
	char buf[1024];
	int num;
	int sockfd, n;
	struct sockaddr_in servaddr;

	num = read(STDIN_FILENO, buf, sizeof(buf));
	if(num<0){
		perror("error");
		exit(1);
	}
	printf("%s\n", buf);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(6666);

	connetc(sock)
	return 0;
}
