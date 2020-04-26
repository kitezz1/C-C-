/*************************************************************************
	> File Name: server.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月25日 星期六 15时30分17秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "wrap.h"
#include <sys/epoll.h>
#include <fcntl.h>
int main (int argc, char const *argv[])
{
	int lfd = tcp4bind(5000, NULL);
	Listen(lfd, 128);
	int epfd = epoll_create(1);
	if(epfd < 0){
		perr_exit("create error");
	}
	return 0;
}
