/*************************************************************************
	> File Name: quick.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月14日 星期四 11时25分45秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;
class quick{
	public:
		quick(){};
		~quick(){};
		int sort(int array[], int s, int e);
		void q(int array[], int s, int e);
		int find(int array[], int s, int e, int v);
		bool hasPath(const char* mat, int length, const char* str);
		bool hasPath(const char* mat, int cols, int rows, const char* str);
		void findMax(int array[], int cols);
};

bool maxcore(int array[], int cols, int i, int* length, int mval){
	cout<<"cols="<<cols<<" i="<<i<<" length="<<*length<<endl;
	if(*length<=0){
		*length = array[i];
		return false;
	}
	bool haspath = false;
	if (i<cols){
		*length = *length+array[i];
		int tmp = *length;
		haspath = maxcore(array, cols, i+1, &tmp, mval);

		cout<<"haspath="<<haspath<<" length="<<tmp<<endl;
		if(!haspath)
			*length = *length - array[i];
	}
	return haspath;
	
	
}
void quick::findMax(int array[], int cols){
	if(array==nullptr || cols<0)
		return;
	int mval = -1000000;
	int length = 0;
	for(int i=0; i<cols; i++){
		//length = 0;
		if(maxcore(array, cols, i, &length, mval))
		{
			length = 0;
		}
		mval = max(length, mval);
		cout<<mval<<"++"<<endl;
	}
	cout<<mval<<endl;
}
bool pathCore(const char* mat, int cols, int rows, int col, int row, const char* str, int length, bool* visit){
	if(str[length]=='\0')
		return true;
	bool hasPath = false;
	if(col<cols && row<rows && col>=0 && row>=0 && mat[cols*row+col]==str[length] && !visit[cols*row+col])
	{
		length++;
		visit[cols*row+col]=true;
		hasPath = pathCore(mat, cols, rows, col-1, row, str, length, visit) ||
				  pathCore(mat, cols, rows, col+1, row, str, length, visit) ||
		          pathCore(mat, cols, rows, col, row-1, str, length, visit) ||
				  pathCore(mat, cols, rows, col, row+1, str, length, visit);
		if(!hasPath){
			length--;
			visit[cols*row+col]=false;
		}
	}
	return hasPath;
}
bool core(const char* mat, int cols, int i, int length, const char* str){
	if(str[length]=='\0')
		return true;
	bool haspath=0;
	if(i<cols && mat[i]==str[length]){
		length++;
		haspath = core(mat, cols, i+1, length, str);
		if(!haspath)
			length--;
	}
	return haspath;
}
bool quick::hasPath(const char* mat, int cols, const char* str){
	if(mat==nullptr || cols<0 || str==nullptr)
		return false;
	int length = 0;
	for(int i=0; i< cols; i++){
		return core(mat, cols, i, length, str);
	}
	return false;
}
bool quick::hasPath(const char* mat, int cols, int rows, const char* str){
	if(mat==nullptr || cols<0 || rows<0 || str==nullptr)
		return false;
	
	int length=0;
	bool *visit = new bool[cols*rows];
	memset(visit, cols*rows, 0);
	for(int row=0; row<rows; row++){
		for(int col=0; col<cols; col++){
			if(pathCore(mat, cols, rows, col, row, str, length, visit))
				return true;
		}
	}
	delete[] visit;
	return false;
}

int quick::sort(int array[], int s, int e){
	int i = s;
	int j = e;
	int x = array[s];
	while(i<j){
		while(i<j && array[j] > x)
			j--;
		if(i < j){
			array[i] = array[j];
			i++;
		}
		while(i<j && array[i] < x)
			i++;
		if(i < j){
			array[j] = array[i];
			j--;
		}
	}
	array[i] = x;
	return i;
}
void quick::q(int array[], int s, int e){
	if(s<e){
		int i = sort(array, s, e);
		q(array, s, i-1);
		q(array, i+1, e);
	}
}
int quick::find(int array[], int s, int e, int v){
	if(s<=e)
	{
		int m = (s+e)/2;
		if (array[m]==v)
			return m;
		if(array[m]>v)
			return find(array, s, m-1, v);
		if(array[m]<v)
			return find(array, m+1, e, v);
	}
	else return -1;
}
int num(int n){
	unsigned int flag = 1;
	int count = 0;
	while(flag){
		if(n & flag)
			count++;
		flag = flag<<1;
	}
	return count;
}
int main(){
	quick q;
	const char* mat="abtgcfcsjdeh\0";
	const char* str="jd\0";
	//cout<<q.hasPath(mat, 12, str)<<endl;
	//cout<<num(10)<<endl;
	int array[]={1, -2, 3, 10, -4, 7, 2,-5};
	q.findMax(array, 8);
	return 0;
}


