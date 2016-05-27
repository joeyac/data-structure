/*
* Filename:    MergeLinkedList.cpp
* Created:     2016年05月27日 20时44分26秒 星期五
* Author:      JIngwei Xu [mail:xu_jingwei@outlook.com]
*
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<vector>
using namespace std;
typedef long long ll;


struct node{
	int val;
	node *next;
};
//Function Declaration
node *MergeLinkedList(node *n1,node *n2){
	if(n1==NULL)return n2; //自然序
	if(n2==NULL)return n1;
	node *result=new node;
	if(n1->val < n2->val){
		result=n1;
		result->next=MergeLinkedList(n1->next,n2);
	}else{
		result=n2;
		result->next=MergeLinkedList(n2->next,n1);
	}
	return result;
}

//Main Program
int main()
{
	
	
	return 0;
}

