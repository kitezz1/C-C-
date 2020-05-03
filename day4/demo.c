/*************************************************************************
	> File Name: demo.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月26日 星期日 20时29分03秒
 ************************************************************************/

#include<stdio.h>
#include <event.h>
int main(){
	const char **methods = event_get_supported_methods();
	struct event_base *base = event_base_new();
	int i = 0;
	for(i=0; methods[i]; i++)
		printf("%s \n", methods[i]);

	printf("%s \n", event_base_get_method(base));

	return 0;
}
