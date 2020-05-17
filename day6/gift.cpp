/*************************************************************************
	> File Name: gift.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月16日 星期六 10时10分41秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

int findcore(int array[], int cols, int rows, int col, int row, int sum){
	if(row==rows-1 && col ==cols-1)
		return array[row*cols+col];
	if(row<rows && col<cols)
		return max(findcore(array, cols, rows, col+1, row, sum), findcore(array, cols, rows, col, row+1, sum)) + array[row*cols+col];
	if(row >= rows || col >= cols)
		return -100000;
		
}
int find(int array[], int cols, int rows){
	if (array==nullptr || cols <0 || rows<0)
		return 0;
	int sum=0;

	return findcore(array, cols, rows, 0, 0, sum);
}
void findmax(int array[], int len, int i, int *sum, int *_max){
	if(i==len){
		*_max = max(*sum, *_max);
		return;
	}
	if(*sum<=0){
		*sum = array[i];
		_max = max(_max, sum);
		findmax(array, len, i+1, sum, _max);
	}
	else{
		*sum = *sum +array[i];
		*_max = max(*_max, *sum);
		findmax(array, len, i+1, sum, _max);
	}
}
void first(const char* str){
	if(str == nullptr)
		return;
	int array[256];
	memset(array, 256, 0);
	for(int i=0; i<strlen(str); i++){
		array[str[i]]++;
	}
	for(int i=0; i<strlen(str); i++){
		if(array[str[i]]==1)
		{
			cout<<str[i]<<endl;
			return;
		}
	}
}
int findIndex(int array[], int star, int end, int x){
	if (star == end && array[star] != x)
		return -1;
	int middle = (star + end)/2;
	cout<<"m="<<middle<<endl;
	if (array[middle] == x)
		return middle;
	if(array[middle]>x)
		return findIndex(array, star, middle-1, x);
	if(array[middle]<x)
		return findIndex(array, middle+1, end, x);
}
int find_star(int array[], int index){
	int flag=0, i;
	for(i=index;i>=0;i--){
		if(array[i]!=array[index]){
			flag=1;
			break;
		}
	}
	if(flag)
		return i+1;
	else
		return 0;

}
int find_end(int array[], int index, int length){
	int flag=0, i;
	for(i=index;i<=length;i++){
		if(array[i]!=array[index]){
			flag = 1;
			break;
		}
	}
	if(flag)
		return i-1;
	else
		return length;
}
int main(){
	int array[] = {1, 10, 3, 8 ,12, 2, 9, 6, 5, 7, 4 ,11, 3, 7, 16, 5};
	int array2[] = {1, 2, 3,3,3,3, 4, 5};
	int array3[] = {};
	const char* str = "abaccdeff\0";
	//int sum = 0;
	//int _max = -100000;
	//findmax(array2, 8, 0, &sum, &_max);
	//cout<<_max<<endl;
	int index = findIndex(array2, 0, 7, 3);
	cout<<index<<endl;
	cout<<find_end(array2, index, 7)-find_star(array2, index)+1<<endl;

}

