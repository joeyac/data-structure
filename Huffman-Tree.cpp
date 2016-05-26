/*
* Filename:    Huffman-Tree.cpp
* Created:     2016年05月26日 19时47分56秒 星期五
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
#define random(x) (rand()%x) //随机整数
using namespace std;
typedef long long ll;
//二叉树//表示节点的结构体
struct node{
	int val;  //每个节点的权值
	string s;  //每个节点代表的字符（串）
	node *lson,*rson;  //左右子树
};
typedef pair<int,node*> P;//first是当前树根节点的权值，second是当前树根节点的指针
priority_queue<P,vector<P>,greater<P> > que;//从队列中按权值从小到大取出树的指针

//Function Declaration

//初始化
node *add(int x,char y){
		node *p=new node;
		p->val=x;
		p->s=y;
		p->lson=p->rson=NULL;
		return p;
}

//合并
node *unite(node *p,node *q){
	if(p->val>q->val)swap(*p,*q);
	node *rt=new node;
	rt->val=p->val+q->val;
	rt->s=p->s+q->s;  //注意
	rt->lson=p;
	rt->rson=q;
	return rt;
}

//以0和1编码，递归寻找叶子节点并返回字符的编码
//存入结构体方便排序输出
struct OUT_DATA{
	string s;
	int weight;
	string code;
}out[100];
bool cmp1(OUT_DATA o1,OUT_DATA o2){  //按照字母的字典序排序
	return o1.s<o2.s;
}
bool cmp2(OUT_DATA o1,OUT_DATA o2){  //按照权值自然序排序
	return o1.weight<o2.weight;
}
bool cmp3(OUT_DATA o1,OUT_DATA o2){  //按照编码字典序排序
	return o1.code<o2.code;
}

int pos;
void huffman(node *p,string pre_string){
	string tmp=p->s;
	if(tmp.length()==1){
		out[pos].s=tmp;
		out[pos].weight=p->val;
		out[pos].code=pre_string;
		pos++;
		return;
	}else{
		huffman(p->lson,pre_string+"0");
		huffman(p->rson,pre_string+"1");
	}
}
void print(node *p,int tag){
	pos=0;
	huffman(p,"");
	if(tag==1)sort(out,out+pos,cmp1);
	else if(tag==2)sort(out,out+pos,cmp2);
	else sort(out,out+pos,cmp3);
	
	for (int i = 0; i < pos; i += 1)
	{
		cout<<out[i].s<<" : "<<" Weight="<<out[i].weight<<" Code="<<out[i].code<<endl;
	}
}

//Main Program
int main()
{

	node *root[26]={NULL};
	//随机生成26个大写英文字母及权值对
	//若包含n个字符，那么从n个叶子节点执行n-1次合并操作可以构造出最终的树
	//共产生n-1个新的节点
	
//	srand((int)time(0));//初始化随机数生成器
//	for (int i = 0; i < 26; i += 1)
//	{
//		char tmp='A'+i;
//		int num=random(10000);
//		root[i]=add(num,tmp);
//		que.push(P(num,root[i]));
//	}
	
	root[0]=add(5,'f');
	que.push(P(5,root[0]));
	
	root[1]=add(9,'e');
	que.push(P(9,root[1]));
	
	root[2]=add(12,'c');
	que.push(P(12,root[2]));
	
	root[3]=add(13,'b');
	que.push(P(13,root[3]));
	
	root[4]=add(16,'d');
	que.push(P(16,root[4]));
	
	root[5]=add(45,'a');
	que.push(P(45,root[5]));
	
	//solve
	while (que.size()!=1) //或者for循环n-1次
	{
		P p1=que.top();que.pop();
		P p2=que.top();que.pop();
		int value=p1.first+p2.first;
		node *rt=unite(p1.second,p2.second);
		que.push(P(value,rt));
	}
	
	//输出
//	huffman(que.top().second,"");
	print(que.top().second,1);
	cout<<endl;
	print(que.top().second,2);
	cout<<endl;
	print(que.top().second,3);
	return 0;
}

