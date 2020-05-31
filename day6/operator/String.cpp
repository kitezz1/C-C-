/*************************************************************************
	> File Name: String.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月28日 星期四 21时05分14秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;
class SS{
public:
	SS(){ data=nullptr; };
	SS(const char* data);
	SS(const SS& s);
	SS& operator=(const SS& s);
	void show() const{
		cout<<data<<endl;
	}
private:
	char *data;
};
SS::SS(const char* dd){
	int len = strlen(dd);
	data = new char[len+1];
	strcpy(data, dd);
	data[len] = '\0';
}
SS& SS::operator=(const SS& s){
	if(this == &s)
		return *this;
	delete[] data;
	data = nullptr;
	int len = strlen(s.data);
	data = new char[len+1];
	strcpy(data, s.data);
	data[len] = '\0';
	return *this;
}
SS::SS(const SS& s){
	int len = strlen(s.data);
	data = new char[len+1];
	strcpy(data, s.data);
	data[len] = '\0';
}
int main(){
	SS s;
	SS b("i love you");
	SS c(b);
	s = b;
	s.show();
	b.show();
	c.show();

	return 0;
}
