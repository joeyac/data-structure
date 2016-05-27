/*
* Filename:    cal.cpp
* Created:     2016年05月27日 06时32分37秒 星期五
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

map<string,int> op_rank;

//Function Declaration

//手写string分割函数，strtok是针对char[]的，不太好用
vector<string> split(string str,string pattern=" "){
	vector<string> res;
	str+=pattern;//扩展字符串方便操作
	int pos,len=str.length();
	for (int i = 0; i < len; i += 1)
	{
		pos=str.find(pattern,i);
		if(pos<len){
			string s=str.substr(i,pos-i);
			res.push_back(s);
			i=pos+pattern.length()-1;
		}
	}
	return res;
}

//初始化函数
void init(){
	op_rank["*"]=3;
	op_rank["/"]=3;
	op_rank["+"]=2;
	op_rank["-"]=2;
	op_rank["("]=1;
	op_rank[")"]=1;
}

//判断是不是运算符或者括号
bool IsOperator(string token){
	if(token.length()!=1)return false;
	if(op_rank.find(token)==op_rank.end())return false;
	return true;
}
//计算后缀表达式的值

double doMath(double num1,double num2,string op){
	if(op=="+")return num1+num2;
	else if(op=="-")return num1-num2;
	else if(op=="*")return num1*num2;
	else return num1/num2;
}

double PosFixCal(vector<string> PosFix){
	int size=PosFix.size();
	double Num,Num1,Num2,result;
	stack<double> OperatorNum;
	for (int i = 0; i < size; i += 1)
	{
		string token=PosFix[i];
		if(!IsOperator(token)){
			sscanf(token.c_str(),"%lf",&Num);
			OperatorNum.push(Num);
		}else{
			Num2=OperatorNum.top();OperatorNum.pop();
			Num1=OperatorNum.top();OperatorNum.pop();
			result=doMath(Num1,Num2,token);
			OperatorNum.push(result);
		}
	}
	result=OperatorNum.top();OperatorNum.pop();
	return result;
	return 0;
}

//返回一个vector<string> 后缀表达式
vector<string> InFix_To_PosFix(string s){ //将中缀表达式转换为后缀表达式
	vector<string> InfixList=split(s);
	vector<string> PosfixList;
	stack<string> OpStack;
	int num=InfixList.size();
	for (int i = 0; i < num; i += 1)
	{
		string token=InfixList[i];
		if(IsOperator(token)){
			if(token=="("){
				OpStack.push(token);
			}
			else if(token==")"){
				string topToken=OpStack.top();OpStack.pop();
				while (topToken!="(")
				{
					PosfixList.push_back(topToken);
					topToken=OpStack.top();OpStack.pop();
				}
			}
			else{ //    +-*/
				while (!OpStack.empty()&&op_rank[OpStack.top()]>=op_rank[token])
				{
					PosfixList.push_back(OpStack.top());
					OpStack.pop();
				}
				OpStack.push(token);
			}
		}
		//数字
		else{
			PosfixList.push_back(token);
		}
	}
	while (!OpStack.empty())
	{
		PosfixList.push_back(OpStack.top());
		OpStack.pop();
	}
	return PosfixList;
}

//计算函数
double solve(string s){ 
	vector<string> Posfix=InFix_To_PosFix(s);
//	for (unsigned int i = 0; i < Posfix.size(); i += 1)
//	{
//		cout<<Posfix[i]<<endl;
//	}
	return PosFixCal(Posfix);
}

//Main Program
int main()
{
	freopen("data/data.in","r",stdin);
	
	//初始化
	init();
	string s;
	
	//保证输入合法，一行一个算式，程序内部不再做检查
	while (getline(cin,s))
	{
		if(s=="")break;
// 数字和运算符括号之间用空格分隔
//exp:	( 3 + 4 ) * 5 - 3 * 2
//		( 2.67 + 4 ) * 5 - 3 * 2
//		( 3 + 4 ) * 5 - ( -3 ) * 2
		cout<<s<<"="<<solve(s)<<endl;
	}
	return 0;
}

