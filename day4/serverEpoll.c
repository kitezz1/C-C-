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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "wrap.h"

#define SERV_PORT 12345 
#define OPEN_MAX 1000
char *get_mine_type(char *name){
	char *dot;
	dot = strrchr(name, '.');

	if(dot == (char *)0)
		return "text/plain; charset=utf-8";
	if(strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
		return "text/html; charset=utf-8";

	if(strcmp(dot, ".jpg")==0)
		return "image/jpeg";
	
	if(strcmp(dot, ".png")==0)
		return "image/png";
	
	return "text/plain; charset=utf-8";
}

void send_header(int cfd, int code, char *info, char *filetype, int length){
	//状态行
	char buf[4096*4]="";
	int len = 0;
	len = sprintf(buf, "HTTP/1.1 %d %s\r\n", code, info);
	send(cfd, buf, len, 0);
	//消息头
	len = sprintf(buf, "Content-Type:%s\r\n", filetype);
	send(cfd, buf, len, 0);

	if(length>0)
	{
		len = sprintf(buf, "Content-Length:%d\r\n", length);
		send(cfd, buf, len, 0);
	}
	//空行
	send(cfd, "\r\n", 2, 0);

}



void send_str(int cfd, char *str, int close_flag, struct epoll_event *ev, int epfd){
	
	write(cfd, str, strlen(str));
	
	if(close_flag == 1){
		epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, ev);
		close(cfd);
	}
}
void send_file(int cfd, char *filepath, int close_flag, struct epoll_event *ev, int epfd){
	int fd = open(filepath, O_RDONLY);
	if(fd < 0){
		perror("open error\n");
		return ;
	}
	char buf[1024]="";
	while(1){
		int count = read(fd, buf, sizeof(buf));
		if(count <= 0){
			break;
		}
		write(cfd, buf, count);
	}
	close(fd);
	if(close_flag == 1){
		epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, ev);
		close(cfd);
	}
}

void request_http(char* msg, struct epoll_event *ev, int epfd){
	//printf("--------------------------------\n");
	printf("[%s]", msg);
	//printf("--------------------------------\n");
	int cfd = ev->data.fd;

	char method[256];
	char content[256];
	char user[256];
	char pd[256];
	//GET /abc HTTP/1.1
	sscanf(msg, "%[^ ] %[^ ?]", method, content);
	//printf("[%s] [%s]", method, content);

	if( strcasecmp(method, "get") == 0){
		char *strfile = content+1;
		struct stat s;
		if(stat(strfile, &s)==-1)
		{
			printf("文件不存在\n");
			//发送错误信息头部
			send_header(cfd, 404, "NOT FOUNT", get_mine_type("*.html"), 0);
			//发送error.html
			send_file(cfd, "error.html", 1, ev, epfd);
		}
		else {
			//普通文件
			if(S_ISREG(s.st_mode)){

				sscanf(msg, "%*[^=]=%[^&] %*[^=]=%[^&]", user, pd);
				if(strlen(user)!=0 && strlen(pd)!=0)
				{
					printf("\n user=%s\n", user);
					printf("pd=%s\n", pd);
				}
				printf("普通文件\n");
				send_header(cfd, 200, "OK", get_mine_type(strfile), s.st_size);
				//发送文件
				send_file(cfd, strfile, 1, ev, epfd);
				
			}else if(S_ISDIR(s.st_mode)){//目录
					//发送信息头部
					//发送列表 组包
			}	
		}
	}
	if( strcasecmp(method, "post") == 0){
			char * s_find = (strstr(msg, "\r\n\r\n"))+4;
			sscanf(s_find, "%*[^=]=%[^&] %*[^=]=%[^&]", user, pd);
			if(strlen(user)!=0 && strlen(pd)!=0)
			{
				printf("\nuser=%s\n", user);
				printf("pd=%s\n", pd);
			}
			printf("\n普通文件\n");
			send_header(cfd, 200, "OK", get_mine_type(".txt"), -1);
			send_str(cfd, "i am test\n", 1, ev, epfd);
	}
}

int main(){

	//切换工作目录
	char *curdir = getenv("PWD");
	char mydir[256]="";
	strcpy(mydir, curdir);
	strcat(mydir, "/data");
	chdir(mydir);
	int i, lfd, cfd, sockfd;
	int n, num = 0;
	ssize_t nready, efd, res;
	char buf[1024*100], str[INET_ADDRSTRLEN];
	socklen_t clilen;

	struct sockaddr_in cliAddr, serverAddr;
	struct epoll_event tep, ep[OPEN_MAX];
	lfd = tcp4bind(SERV_PORT, NULL);
	//lfd = Socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	//setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
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
				memset(buf, sizeof(buf), 0);
				sockfd = ep[i].data.fd;
				n = Read(sockfd, buf, 1024*100);
				printf("\n--%d--\n", n);
				if (n == 0){
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					Close(sockfd);
				} else{
					//for (i =0; i<n; i++)
						//buf[i] = toupper(buf[i]);
					//Write(STDOUT_FILENO, buf, n);
					//Writen(sockfd, buf, n);
				request_http(buf, &ep[i], efd);
				}
			}
		}
	}


	return 0;
}
