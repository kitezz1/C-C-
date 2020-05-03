#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
 int main(int argc, char *argv[]){ 
    //if(argc!=2){
      //printf("error usage %s ip\n",argv[0]); 
      //return 1;
    //} 
    int sockfd;
    int len; 
    struct sockaddr_in address; 
    int result; 
    unsigned char httpstring[100]; 
    sprintf(httpstring,"GET /a.png HTTP/1.1\r\n"
          "Host: %s\r\n"
          "Connection: Close\r\n\r\n",argv[1]); 
    char ch[1024]; 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr("121.199.72.226"); 
    address.sin_port = htons(5000); 
    len = sizeof(address);
    result = connect(sockfd,(struct sockaddr *)&address,len); 
    if(result == -1){ 
       perror("oops: client"); 
       return 1; 
    }
	memset(ch, 0, sizeof(ch));
    write(sockfd,httpstring,strlen(httpstring));
	int flag=1;
	int bytes=0;
	FILE* fp2 = fopen("out", "w");
    while((bytes=read(sockfd,ch,sizeof(ch)))){
		if(flag){
			char *p=strstr(ch, "\r\n\r\n");
			if(p!=NULL)
			{	
				p = p+4;
				fwrite(p, bytes-(p-ch), 1, fp2);
				flag = 0;
			}
			memset(ch, 0 ,1024);
		}else{
			fwrite(ch, bytes, 1, fp2);
			memset(ch, 0 ,1024);
		}

    }
	fclose(fp2);
    close(sockfd); 
    printf("\n"); 
    return 0; 
 }
