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
int find_two(int array[], int &star, int &end, int val){
	if(array==nullptr || star <0 || end <0 || star > end)
		return 0;

	while(star < end){
		cout<<star<<" "<< end <<endl;
		if(array[star]+array[end]==val)
			return 1;
		if(array[star]+array[end]>val){
			end = end-1;
			continue;
		}
		if(array[star]+array[end]<val){
			star = star+1;
			continue;
		}
	}
	return 0;
	
}
void find_2(int star, int end, int val){
	
	if(star<0 || end < 0 || star >=end)
		return;
	int i=0;
	int tmp=0;
	while(star<=(val/2))
	{
		cout<<star<<" -"<<end<<endl;
		tmp=0;
		for(i=star;i<=end;i++)
			tmp = tmp+i;
		if(tmp == val && star!=end){
			for(i=star;i<=end;i++)
				cout<<i<<" ";
			cout<<endl;
			star = star +1;
			continue;
		}
		if(tmp<val){
			end = end+1;
			continue;
		}
		if(tmp>val){
			star = star +1;
			continue;
		}
			
	}
}
void reverse(char*s, char*e){
	if(s==nullptr || e==nullptr)
		return;
	char t;
	while(s<e){
		t =*s;
		*s = *e;
		*e = t;
		s++;
		e--;
	}
}
void rr(const char* str){
	if(str == nullptr)
		return;
	char *t = new char[strlen(str)+1];
	strcpy(t, str);
	t[strlen(str)] = '\0';

	reverse(t, t+strlen(str)-1);
	cout<<t<<endl;
	char * s=t;
	char * end = nullptr;
	for(int i=0;i<strlen(t);i++){
		end = t+i;
		if(t[i]==' ')
		{
			reverse(s, end-1);
			s = end+1;
		}
	}
	//reverse(s, end);
	cout<<t<<endl;
}

int main(){
	const char* str = "i am a student\0";
	int array[] = {1,2,4,7,11,15};
	int star = 0;
	int end = 5;
	//find_2(1, 2, 15);
	rr(str);
}

