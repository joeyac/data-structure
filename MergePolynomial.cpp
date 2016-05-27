/*
* Filename:    MergePolynomial.cpp
* Created:     2016年05月27日 20时58分00秒 星期五
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
typedef pair<int,int> P;
typedef long long ll;

struct node{
	double coefficient; //系数
	double power;//幂
	node *next;
};
//Function Declaration

//按幂的自然序建立链表
node *build(node *rt,double co,double po){
	node *res=new node;
	if(rt==NULL){
		res->coefficient=co;
		res->power=po;
		res->next=NULL;
	}else{
		node *cur=rt;
		node *pre=NULL;
		while (cur!=NULL && po>=cur->power) //一直找到一个小于的位置
		{
			pre=cur;
			cur=cur->next;
		}
		if(pre==NULL){ //表头
			res->coefficient=co;
			res->power=po;
			res->next=rt;
		}else{
			if(po==pre->power){ //相等直接累加系数
				pre->coefficient=pre->coefficient+co;
				res=rt;
			}else{
				node *tmp=new node;
				tmp->coefficient=co;
				tmp->power=po;
				tmp->next=cur;
				pre->next=tmp;
				res=rt;
			}
		}
	}
	return res;
}

//合并两个链表
node *MergePolynomial(node *n1,node *n2){
	if(n1==NULL)return n2;
	if(n2==NULL)return n1;
	node *res=new node;
	if(n1->power < n2->power){
		res=n1;
		res->next=MergePolynomial(n1->next,n2);
	}else if(n1->power == n2->power){
		double a=n1->coefficient,b=n2->coefficient;
		if(a+b==0){
			res=MergePolynomial(n1->next,n2->next);
		}else{
			res=n1;
			res->coefficient=a+b;
			res->next=MergePolynomial(n1->next,n2->next);
		}
	}else{
		res=n2;
		res->next=MergePolynomial(n2->next,n1);
	}
	return res;
}
//输出链表
void print(node *root){
	node *cur=root;
	while (cur!=NULL)
	{
		double a=cur->coefficient;
		double b=cur->power;
		cout<<"系数："<<a<<" 指数："<<b<<endl;
		cur=cur->next;
	}
}

//Main Program
int main()
{
	double a,b;
	int tag;
	while (1)
	{
		node *rt1=NULL,*rt2=NULL;
		cout<<"按提示输入两个一元多项式"<<endl;
		cout<<"输入第一个多项式的系数a和指数b，以空格分隔，0 0停止"<<endl;
		
		while (scanf("%lf%lf",&a,&b)&&a&&b)
		{
			
			rt1=build(rt1,a,b);
		}
		
		cout<<"输入第二个多项式的系数a和指数b，以空格分隔，0 0停止"<<endl;
		
		while (scanf("%lf%lf",&a,&b)&&a&&b)
		{
			rt2=build(rt2,a,b);
		}
		node *ans=MergePolynomial(rt1,rt2);
		print(ans);
		cout<<"输入1继续，其他退出"<<endl;
		cin>>tag;
		if(tag!=1)break;
	}
	return 0;
}

