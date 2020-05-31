/*************************************************************************
	> File Name: inter.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月28日 星期四 20时12分19秒
 ************************************************************************/

#include<iostream>
using namespace std;

class inter{
public:
	inter(int n) :n_(n){}
	~inter(){}
	inter(const inter& A);
	inter& operator=(const inter& A);
	void getN() const{
		cout<<n_<<endl;
	}
	inter& operator++();
	inter operator++(int n);
	//friend inter& operator++(inter& A);
private:
	int n_;
};

inter& inter::operator++(){
	n_++;
	return *this;
}
inter inter::operator++(int n){
	inter tmp(n_);
	n_++;
	return tmp;
}
//inter& operator++(inter& A){
//	A.n_++;
//	return A;
//}
inter::inter(const inter& A){
	n_ = A.n_;
}
inter& inter::operator=(const inter& A){
	if(this == &A)
		return *this;
	else{
		n_ = A.n_;
		return *this;
	}
}

int main(){
	inter a(10);
	a.getN();
	inter b=a++;
	a.getN();
	b.getN();
}
