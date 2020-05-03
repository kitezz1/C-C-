/*************************************************************************
	> File Name: test.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月26日 星期日 23时20分29秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main()
{
	char *url = "/request.html?user=shengkai&pd=123456&st=";
	printf("url=%s\n", url);
	char user[128]="";
	
	char pd[128]="";
	sscanf(url, "%*[^=]=%[^&] %*[^=]=%[^&]", user, pd);
	printf("user=------%s\n", user);

	//sscanf(url, "%*[^&]&%[^&]", pd);
	
	//sscanf(pd, "%*[^=]=%[^&]", pd);
	printf("pd=------%s\n", pd);
	return 0;
}
