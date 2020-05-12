/*************************************************************************
	> File Name: copy.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月12日 星期二 21时34分50秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

class MyString{
public:
	MyString(char* str);
	~ MyString();
	MyString(const MyString &str){ data = str.data; };
	MyString & operator= (const MyString &str);
public:
	char *data;
};
MyString & MyString:: operator= (const MyString &str){
	if (this == &str)
		return *this;
	delete [] data;
	data = nullptr;
	data = new char[strlen(str.data)+1];
	strcpy(data, str.data);
	return *this;
}

int main(){
	return 0;
}


