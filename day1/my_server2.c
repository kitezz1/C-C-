/*************************************************************************
  > File Name: my_server2.c
  > Author: ma6174
  > Mail: ma6174@163.com 
  > Created Time: 2020年03月08日 星期日 16时40分20秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(){
	int lfd,cfd;
	struct sockaddr_in servaddr,clinaddr;
	socklen_t serv_len;
	int n, i;
	char buf[1024];
	char str[1024];
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(lfd, 128);
	printf("Accept connections ...\n");

	while(1){
		serv_len = sizeof(clinaddr);
		cfd = accept(lfd, (struct sockaddr*)&clinaddr, &serv_len);
		printf("cline ip = %s port=%d\n", inet_ntop(AF_INET, &clinaddr.sin_addr, str, sizeof(str)), ntohs(clinaddr.sin_port));
		while(1){
			n = read(cfd, buf, sizeof(buf));
			if(n == 0)
				break;
			printf("n=%d\n", n);
			for(i=0; i<n; i++)
				buf[i] = toupper(buf[i]);
			write(cfd, buf, n);
		}
		close(cfd);
	}
	return 0;
}
