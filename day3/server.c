/*************************************************************************
	> File Name: server.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月07日 星期二 10时13分52秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 8000
#define OPEN_MAX 5000

int main(){

	int i, lfd, cfd, sockfd;
	int n, num = 0;
	ssize_t nready, efd, res;
	char buf[MAXLINE], str[INET_ADDRSTRLEN];
	socklen_t clilen;

	struct sockaddr_in cliaddr, servaddr;
	struct epoll_event tep, ep[OPEN_MAX];

	lfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(lfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	Listen(lfd, 20);

	efd = epoll_create(OPEN_MAX);
	if (efd == -1)
		perr_exit("epoll_create error\n");

	tep.events = EPOLLIN; tep.data.fd = lfd;
	res = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &tep);
	if (res == -1)
		perr_exit("epoll_ctl error");

	for( ; ; ){
		nready = epoll_wait(efd, ep, OPEN_MAX, -1);
		if (nready == -1)
			perr_exit("epoll_wait error");

		for (i = 0; i<nready; i++){
			if (!(ep[i].events & EPOLLIN))
				continue;

			if (ep[i].data.fd == lfd){
				clilen = sizeof(cliaddr);
				cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
				printf("receive from %s at port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
				printf("cfd %d --- client %d\n", cfd, ++num);

				tep.events = EPOLLIN; tep.data.fd = cfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &tep);
				if (res == -1)
					perr_exit("epoll_ctl error");
			} else {
				sockfd = ep[i].data.fd;
				n = Read(sockfd, buf, MAXLINE);
				if (n == 0) {
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1)
						perr_exit("epoll_ctl error");
					Close(sockfd);
					printf("client[%d] closed connection\n", sockfd);
				} else if (n < 0) {
					perror("read n < 0 error: ");
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					Close(sockfd);
				} else {
					for (i = 0; i<n ;i++)
						buf[i] = toupper(buf[i]);
					Write(STDOUT_FILENO, buf, n);
					Writen(sockfd, buf, n);
				}
			}
		}

	}

	return 0;

}
