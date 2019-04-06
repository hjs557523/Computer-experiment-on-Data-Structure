#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
#define MAX_VEXTEX_NUM 20
#define M 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//弧结点结构类型
typedef struct ArcNode{
	int adjvex;//该弧指向的顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
}ArcNode;

//邻接表头结点类型
typedef struct VNode{
	int data;//顶点信息
	ArcNode *firstarc;//指向第一条依附于该点的弧的指针
}VNode,AdjList[MAX_VEXTEX_NUM];

typedef struct{
	AdjList vertices;//一维数组存储头结点
	int vexnum;//当前图的顶点数
	int arcnum;//当前图的弧数
}ALGraph

void CreateGraph(ALGraph *G){//创建一个图的邻接表
	int m,n,i,j;
	ArcNode *p;
	printf()
}