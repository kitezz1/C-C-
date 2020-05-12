/*************************************************************************
	> File Name: signal.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月12日 星期二 21时39分44秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Single{
private:
	Single();
	~Single();
	Single(const Single &);
	Single& operator=(const Single &);
public:
	static Single& getInstance(){
		static Single instance;
		return instance;
	}
};
int main(){
	return 0;
}
