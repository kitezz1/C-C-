/*************************************************************************
	> File Name: num.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月15日 星期五 16时56分33秒
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <set>
using namespace std;
int f(const char* str){
	int* counts = new int[strlen(str)];
	int count = 0;
	for(int i =0; i<strlen(str); i++){
		if(i==0)
			count = 1;
		else
			count = counts[i-1];
		if(i>0){
			int d = (str[i-1]-'0')*10+str[i]-'0';
			cout<<"d="<<d<<endl;
			if(d>=10 && d<=25){
				if(i>=2)
					count = count + counts[i-2];
				else
					count = count + 1;
			}
		}
		counts[i] = count;
	}
	return counts[strlen(str)-1];
}
int s(const char* str){
	if(str==nullptr)
		return 0;
	int max=0, star=0, end=0;
	set<char> mm;
	for(int i=0;i<strlen(str);i++){
		for(int j=i; j<strlen(str);j++){
			if(mm.find(str[j])==mm.end()){
				mm.insert(str[j]);
				if(max<1)
					max = 1;
			}
			else{
				mm.clear();
				if(j-i>=max){
					max = j-i;
					star = i;
					end = j;
				}
				break;
			}
		}
	}
	cout <<"star= "<<star<<" end="<<end<<endl;
	return max;
}
int len(const char* str){
	int l=0,r=0,max_=0;
	set<char> mm;
	while(r!=strlen(str)){
		if(mm.find(str[r])==mm.end()){
			mm.insert(str[r++]);
			max_ = max(max_, r-l);
		}
		else
			mm.erase(str[l++]);

	}
	return max_;
}
int main(){
	const char* str = "aaaaaa\0";
	cout<<len(str)<<endl;
}

