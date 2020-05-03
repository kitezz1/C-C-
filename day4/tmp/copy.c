/*************************************************************************
	> File Name: copy.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年04月28日 星期二 15时35分28秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
int func_copyfile(char *pSrc, char *pDest)
{
	FILE *fp1 = NULL; //指向源文件
	FILE *fp2 = NULL; //指向目的文件
	char byBuff[10] = {0}; //缓存
	int fileBytes = 0; //文件大小

	if((pSrc == NULL) || (pDest == NULL))
	{
		return 0;
	}
	
	if((fp1 = fopen(pSrc, "r")) != NULL)
	{
		if((fp2 = fopen(pDest, "w")) != NULL)
		{
			while((fileBytes = fread(byBuff, 1, sizeof(byBuff), fp1)) > 0)
			{
				fwrite(byBuff, fileBytes, 1, fp2);
				memset(byBuff, 0, sizeof(byBuff));
			}
			
			fclose(fp1);
			fclose(fp2);
			
			return 1;
		}
	}
	
	return -1;
}

int main(){
	char *f1="a.png";
	char *f2 = "b.png";

	func_copyfile(f1, f2);
}
