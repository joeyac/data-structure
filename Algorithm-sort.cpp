/*
* Filename:    sort-algorithm.cpp
* Created:     2016年05月26日 21时37分58秒 星期五
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


void print(int *a,int n){
	for (int i = 0; i <n; i += 1){
		if(i==n-1)cout<<a[i]<<endl;
		else cout<<a[i]<<" ";
	}
}
//Function Declaration
void InsertSort(int *a,int n){  //直接插入排序//类比摸牌//时间复杂度：O（n^2）.稳定
	for (int j = 1; j < n; j += 1)
	{
		if(a[j]<a[j-1]){
			int key=a[j];
			int i=j-1;
			a[j]=a[j-1];
			while (key<a[i])
			{
				a[i+1]=a[i];
				i--;
				if(i==-1)break;
			}
			a[i+1]=key;
		}
	}
	print(a,n);
}

void SelectSort(int *a,int n){  //直接选择排序//时间复杂度：O（n^2）.不稳定
	//在要排序的一组数中，选出最小（或者最大）的一个数与第1个位置的数交换；然后在剩下的数当中再找最小（或者最大）的与第2个位置的数交换，依次类推，直到第n-1个元素（倒数第二个数）和第n个元素（最后一个数）比较为止。
	int key,tmp;
	for (int i = 0; i < n; i += 1)
	{
		key=i;
		//选出最小的
		for (int j = i+1; j < n; j += 1)
		{
			if(a[key]>a[j])key=j;
		}
		if(key!=i){
			tmp=a[key];a[key]=a[i];a[i]=tmp;
		}
	}
	print(a,n);
}


//Main Program
int main()
{
	const int NUM=10;
	int a[NUM];
	for (int i = 0; i < NUM; i += 1){
		a[i]=random(100);
		if(i==NUM-1)cout<<a[i]<<endl;
		else cout<<a[i]<<" ";
	}
	SelectSort(a,NUM);
	
	
	return 0;
}

