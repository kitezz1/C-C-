/*> File Name: server.c
  > Author: ma6174
  > Mail: ma6174@163.com 
  > Created Time: 2020年03月09日 星期一 10时55分05秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "wrap.h"

#include <pthread.h>
void* process(void* arg){
			int n, i;
			int cfd = (int)arg;
			printf("I am child %lu\n", pthread_self());
			char buf[1024];
			n = Read(cfd, buf, sizeof(buf));
			for(i=0; i<n; i++)
				buf[i] = toupper(buf[i]);
			Write(cfd, buf, n);
			close(cfd);
}
int main()
{
	struct sockaddr_in server,cline;
	int cfd, lfd;
	socklen_t cline_len;
	char buf[1024];
	char str[1024];
	int i, n;
	pid_t pid;

	lfd = Socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(6666);

	Bind(lfd, (struct sockaddr*)&server, sizeof(server));
	Listen(lfd, 128);
	printf("read to server...\n");

	while(1){
		cline_len = sizeof(cline);
		cfd = Accept(lfd, (struct sockaddr*)&cline, &cline_len);
		printf("ip=%s:%d\n", inet_ntop(AF_INET, &cline.sin_addr, str, sizeof(str)), ntohs(cline.sin_port));
		pthread_t tid;
		pthread_create(&tid, NULL, process, (void*)cfd);
		pthread_detach(tid);
		}
	return 0;
}
