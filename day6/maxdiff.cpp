/*************************************************************************
	> File Name: maxdiff.cpp
	> Author: ma6174
	> Mail: ma6174@163.com
	> Created Time: 2020年05月18日 星期一 10时05分30秒
 ************************************************************************/

#include<iostream>
#include <vector>
#define max(a, b) a>b ? a:b
using namespace std;

int l1 = 0;
int vip(int array[], int len) {
	if (len < 2 || array == nullptr)
		return -1;
	int minv = array[0];
	int maxv = array[1] - array[0];
	for (int i = 0; i < len - 1; i++) {
		if (array[i] < minv)
			minv = array[i];
		maxv = max(maxv, array[i + 1] - minv);

	}
	cout << maxv << endl;
	return maxv;
}

typedef struct node {
	char data;
	struct node* left;
	struct node* right;
}Node, *Pnode;

Pnode createTree() {
	Pnode root = new Node;
	root->data = 'A';
	Pnode B = new Node;
	B->data = 'B';
	Pnode C = new Node;
	C->data = 'C';
	Pnode D = new Node;
	D->data = 'D';
	Pnode E = new Node;
	E->data = 'E';
	Pnode F = new Node;
	F->data = 'F';
	Pnode G = new Node;
	G->data = 'G';
	Pnode H = new Node;
	H->data = 'H';
	Pnode I = new Node;
	I->data = 'I';

	root->left = B;
	root->right = C;
	B->left = D;
	B->right = E;
	D->left = F;
	D->right = G;
	E->left = H;
	E->right = I;
	F->left = nullptr;
	F->right = nullptr;
	G->right = nullptr;
	G->left = nullptr;
	C->left = nullptr;
	C->right = nullptr;
	H->left = nullptr;
	H->right = nullptr;
	I->left = nullptr;
	I->right = nullptr;
	return root;
}
void first(Pnode root) {
	if (root==nullptr)
		return;
		cout << root->data << endl;
		l1++;
		first(root->left);
		first(root->right);
}
int findnode(Pnode root, Pnode &tmp, char &val){
	if(root==nullptr || tmp!=nullptr){
		return 0;
	}
	if(root->data == val){
		tmp = root;
		return 1;
	}
	return findnode(root->left, tmp, val)||findnode(root->right, tmp, val);

}

void middle(Pnode root) {
	if (root == nullptr)
		return;
		middle(root->left);
		cout << root->data << endl;
		middle(root->right);
}
int find(Pnode root, bool &flag, vector<char> &v, char &val){
	cout<<v.size()<<endl;
	if(root==nullptr || flag == 1){
		return 0;
	}
	if(root->data==val){
		flag =1;
		v.push_back(root->data);
		return 1;
	}
	v.push_back(root->data);

	int haspath = find(root->left, flag, v, val) || find(root->right, flag, v, val);
	if(!haspath)
		v.pop_back();
	return haspath;

}
int main() {
	vector<char> v;
	Pnode root= createTree();
	bool flag = 0;
	char val = 'E';
	Pnode tmp=nullptr;
	if(findnode(root, tmp, val))
	{
		first(tmp);
		cout<<l1<<endl;
	}
	//first(root);
	//cout << "---" << l1<<endl;
	//find(root, flag, v, val);
	//cout<<v.size()<<endl;
	//for(auto i=v.begin();i!=v.end();i++){
	//	cout<<*i<<" ";
	//}

	//middle(root);
	//system("pause");
	
	return 0;
}
