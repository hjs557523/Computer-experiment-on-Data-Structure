#include <stdio.h>       
#include <malloc.h> 
#include <stdlib.h> 
#define MaxSize 100
#define OVERFLOW 1



//定义车辆结点信息
typedef struct CarNode
{
	char AD;//车辆到达或离去的信息
	int NO;//汽车车牌号
	int time;//到达或离去的时刻
}CarNode;



//定义一个顺序栈作为停车场
typedef struct SqStack	
{ 
	struct CarNode	data[MaxSize];//结构数组存放所有车辆结点信息
	int top;//栈顶指针(实际为数组下标值)
	int num;//该顺序栈的当前存车数量
}SqStack;



//队列结点定义
typedef struct QNode
{
	struct CarNode data;//车辆结点信息域
	QNode *next;//指向下一个车辆结点的指针域
}QNode;



//定义一个链式队列作为便道
typedef struct LinkQueue
{
	QNode *front;//队头指针
	QNode *rear;//队尾指针
	int num;//队列车辆数量
}LinkQueue;



//创建一个空的停车场,即创建初始化一个空栈
SqStack *Init_SqStack()
{
		SqStack *s;//声明一个指向顺序栈的指针s
		s=(SqStack*)malloc(sizeof(SqStack));//通过指针s分配地址
		if(!s) exit(OVERFLOW);
	    s->top=0;//栈顶指针的初始值为0，并作为栈空标记
		s->num=0;//栈的当前存放车辆数量为0
		return s;//返回指向一个已初始化的空顺序栈的指针s
}



//创建一个空的便道,即创建初始化一个空队列
LinkQueue *Init_LinkQueue()      
{
		LinkQueue *q;//声明一个指向队列的指针q
	    QNode *p;//声明一个指向队列结点的指针p，并将p作为头指针
     	q=(LinkQueue*)malloc(sizeof(LinkQueue));//通过指针q分配地址
		if(!q) exit(OVERFLOW);//分配失败
    	p=(QNode*)malloc(sizeof(QNode));//通过指针p分配地址,并将p作为头指针
		if(!p) exit(OVERFLOW);//分配失败
		q->front=q->rear=p;//队头指针和队尾指针一起指向头结点p,作为队空标记
		q->front->next=NULL;//头结点next域为空
		q->num=0;//队列当前车辆数量为空
		return q;//返回指向一个已初始化的空队列的指针q
}



//顺序栈栈空判断
int IsEmpty_SqStack(SqStack *s)
{
	if(s->top ==0)
		return 1;//栈空返回1
	else
		return 0;//栈非空返回0
}



//顺序栈栈满判断
int  IsFull_SqStack(SqStack *s,int n)	
{
	if(s->top==n)//假设输入栈最大容量为n，当下标top到达n时，判定栈满，即可存放[0,n-1]个车辆结点信息
		return 1;//栈满返回1
	else
		return 0;//栈不满返回0
}



//链队列队空判断
int IsEmpty_LinkQueue(LinkQueue *q)		
{
	if(q->front==q->rear)
		return 1;//队空返回1
	else 
		return 0;//队非空返回0
}



//插入车辆信息结点到队列q中
void In_LinkQueue(LinkQueue *q,struct CarNode s)
{
		QNode *p;//声明一个指向队列结点的指针p
		p=(QNode*)malloc(sizeof(QNode));//分配地址
		if(!p) exit(OVERFLOW);//分配失败
		p->data=s;//车辆信息赋给结点p的data域
		q->num++;//队列q长度+1

		p->next=NULL;//队尾插入的结点p的next域为空
		q->rear->next=p;//将结点p插入队尾
		q->rear=p;//队尾指针后移
}



//车辆进入停车场(入栈)
void Push_SqStack(SqStack *p,struct CarNode s)  
{
	p->data[p->top]=s;//在原先top“指针”指向的位置上插入新进车辆结点
	p->top++;//下标top+1，即指向新进车辆结点的上一个位置
	p->num++;//栈p长度+1
}



//车辆退出停车场(出栈)
int Pop_SqStack(SqStack *s,struct CarNode c)
{
	SqStack *p;//声明一个顺序栈作为临时停车场
	int t;//停车总时间
    p=Init_SqStack();//初始化临时停车场

	s->top--;//先将top指针指向最新进入的车辆结点

	while(s->data[s->top].NO !=c.NO)//若找不到车牌号为P.NO的车，
	{
	    Push_SqStack(p,s->data[s->top]);//暂时移入临时停车场
		s->top--;//top指针下移
		s->num--;//车辆数量-1
	}

	/*
	  假设以最新进入停车场的车辆的到达时间作为当前时间，则退车车辆停车时间的大致计算如下: 
	  停车总时间: t=退车车辆的离去时间-退车车辆的到达时间
	*/


	t=c.time - s->data[s->top].time;//计算停车时间
	s->num--;//停车场车辆数-1

	/*停车场top指针当前指在退车车辆的位置*/


	while(IsEmpty_SqStack(p)==0)//临时停车场非空
	{
		Push_SqStack(s,p->data[--p->top]);
		p->num--;//临时停车场车辆数量-1
	}
	return t;//返回停车时间
}


//车辆出链队列便道
struct CarNode Out_LinkQueue(LinkQueue *q)   //出队
{
		QNode *p;
		p=q->front->next;//先保存下出链队列的车辆结点
		q->front->next=p->next;
		q->num --;

		//特别注意当队列只有一个元素时要防止free后队尾指针丢失
		if(	q->front->next==NULL)//这里队列只有一个数据元素时，数据元素被删掉后队尾指针的处理
			q->rear=q->front;
		return p->data;//返回出队列的车辆信息
		free(p);
}


/*主流程算法定义如下*/
int main()
{

	SqStack *park;//声明一个停车场
	LinkQueue *path;//声明一个便道
	struct CarNode car;//声明待处理车辆
	int n,t;//n为自定义的停车场最大容量，t为停车总时间

	park=Init_SqStack();//初始化停车场
	path=Init_LinkQueue(); //初始化便道
    printf("上机实验2: 停车场管理系统\n");
	printf("\n");
	printf("请输入停车场可存放汽车的最大容量:\n");
	scanf("%d",&n);
	printf("请输入车辆信息,包括汽车“到达”或者“离去”信息(用A/D表示),汽车牌照号码,以及到达或离去的时刻,如: A,1,5:\n");
    scanf("%c,%d,%d",&car.AD,&car.NO,&car.time);
	while(car.AD!='E')
	{
	   if(car.AD=='A' )//车辆到达处理
	   {								
				 if(IsFull_SqStack(park,n)==1)  //停车场满
				 {
					In_LinkQueue(path,car);   //进入便道进行等待
				    printf("该汽车在便道上的第%d个停车位置\n",path->num);
					printf("\n");
					printf("请继续输入车辆信息\n");
				 }
				 else
				 {
					 Push_SqStack(park,car);		//进入停车场
					printf("该汽车在停车场内的第%d个位置\n",park->num);
					printf("\n");
					printf("请继续输入车辆信息\n");
				 }
	   }
			   
	   if(car.AD=='D' )	//车辆从停车场离开处理
	   {
                t=Pop_SqStack(park,car);//出栈
				printf("这辆车在停车场的停留时间为%d,需要支付停车费共计%d元\n",t,10*t);//
				printf("\n");
				printf("请继续输入车辆信息\n");
			    if(IsEmpty_LinkQueue(path)==0)   //出停车场后，便道有车辆排队则需要进栈
			      Push_SqStack(park,Out_LinkQueue(path));	  
	   }
		scanf("%c,%d,%d",&car.AD,&car.NO,&car.time);//继续输入车辆信息		
	}
	
	printf("输入结束\n");
	return 1;
}
