#ifndef _CycleLinklist_
#define _CycleLinklist_

//定义结点(人)的结构
typedef struct LNode{
	int key;//每个人持有的密码
	int num;//每个人的编号
	struct LNode *next;//指向下一个结点
}LNode, *CycleLinklist;

//创建空的单向循环链表
void InitList(CycleLinklist &L){
	L = (LNode*)malloc(sizeof(LNode));//申请头结点
	if(!L) exit(1);//异常退出
	L->key=0;
	L->num=0;
	L->next=L;//空表判定
}

//根据用户输入数据n创建单向循环链表
void CreateCycleLinklist(int n,CycleLinklist &L){
	CycleLinklist p,q;

	q = L;//使用q来暂时保存L指向的头结点的指针

	printf("请输入每个人手中的密码:\n");
	for(int i=1;i <= n;i++){
		p=(LNode*)malloc(sizeof(LNode));//申请结点
		if(!p) exit(1);
		scanf("%d",&p->key);
		p->num=i;
		L->next=p;
		L=p;
	}

	L->next=q->next;//尾指针指向第一个结点
	/*这里要注意，由于我定义的的单向循环链表是带头结点的，为了方便之后遍历链表找到
	  报数为m的结点，并且防止计数的时候把头结点也算进去，所以这里要把尾指针指向第一
	  个结点，而不是头结点*/
	free(q);
}


/*个人调试代码心得:这个函数我一开始代码一直输出错误，经过debug调试时发现，m值一直是20，原因是没有将传入参数设置为&m，
  导致m的作用域在函数内，应该进行&变量返回变量值*/




//定位报到m值的人
CycleLinklist Locate_m(int &m,CycleLinklist &p){
	CycleLinklist q;
	for(int j=1;j<m;j++) p=p->next;
		q=p->next;//此时定位到报到m值的人q
	    m=q->key;//必须要取到密码,更新m值,以便再进行下一次循环
	    return q;
	}


//删除定位的报到m值的人
void Delete_m(CycleLinklist &L,CycleLinklist p,CycleLinklist q){
	p->next=q->next;//p是定位到m的人的前一个,q是要删除的人
	free(q);
}

#endif