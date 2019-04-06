#include <stdio.h>
#include <stdlib.h>
#include "CycleLinklist.h"

void main(){
	CycleLinklist L,p,q;
	int m,n;
	L=NULL;
	InitList(L);//构造只有头结点的空链表
	printf("请输入您设置的约瑟夫环初始密码值:\n");
	scanf("%d",&m);//初始密码
	printf("请输入您设置的约瑟夫环参与人数:\n");
	scanf("%d",&n);//总人数
	CreateCycleLinklist(n,L);//根据人数建立一个约瑟夫环
	p=L;
	printf("出局者的顺序编号如下:\n");
	for(int i=1;i<=n;i++){
		q=Locate_m(m,p);//每一轮在p链表中找到报数为m的人,并更新m值,指向该人的指针为q
		printf("%d\n",q->num);//输出报数为m的人的序号
		Delete_m(L,p,q);//在p链表中删除报数为m的人
	}


}