#include <iostream>
using namespace std;
template <typename T>

cout<<"cc"<<endl;
const T& max_m(const T& a, const T& b){
	return a>b ? a : b;
}
int main(){
	int a=1;
	int b=2;
	cout<<max_m(a, b)<<endl;
	return 0;
}

