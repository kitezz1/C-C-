/*************************************************************************
	> File Name: serverEpoll.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月20日 星期一 20时15分07秒
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
#define SERV_PORT 5000 
#define OPEN_MAX 1000

int main(){

	int i, lfd, cfd, sockfd;
	int n, num = 0;
	ssize_t nready, efd, res;
	char buf[1024], str[INET_ADDRSTRLEN];
	socklen_t clilen;

	struct sockaddr_in cliAddr, serverAddr;
	struct epoll_event tep, ep[OPEN_MAX];
	lfd = tcp4bind(SERV_PORT, NULL);
	//lfd = Socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	//bzero(&serverAddr, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddr.sin_port = htons(SERV_PORT);

	//Bind(lfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	Listen(lfd, 20);

	efd = epoll_create(OPEN_MAX);
	if (efd == -1)
		perr_exit("epoll_create error");

	tep.events = EPOLLIN; tep.data.fd = lfd;
	res = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &tep);
	if (res == -1)
		perr_exit("epoll_ctl error");

	for(; ;){
		nready = epoll_wait(efd, ep, OPEN_MAX, -1);
		if(nready == -1)
			perror("epoll_wait error");
		
		for(i=0; i<nready; i++){
			if(!(ep[i].events & EPOLLIN))
				continue;
			
			if(ep[i].data.fd == lfd){
				clilen = sizeof(cliAddr);
				cfd = Accept(lfd, (struct sockaddr*)&cliAddr, &clilen);
				//printf("cfd %d --client %d\n", cfd, ++num);
				printf("receive from %s at port %d\n",
						inet_ntop(AF_INET, &cliAddr.sin_addr, str, sizeof(str)),
						ntohs(cliAddr.sin_port));
				tep.events = EPOLLIN; tep.data.fd = cfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &tep);
				if (res == -1)
					perr_exit("epoll_ctl error");
			} else {
				sockfd = ep[i].data.fd;
				n = Read(sockfd, buf, 1024);
				if (n == 0){
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					Close(sockfd);
				} else{
					for (i =0; i<n; i++)
						buf[i] = toupper(buf[i]);
					Write(STDOUT_FILENO, buf, n);
					//Writen(sockfd, buf, n);
				}
			}
		}
	}


	return 0;
}
