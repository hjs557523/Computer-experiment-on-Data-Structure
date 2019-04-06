#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxSite 100
#define infinite 10000

//定义存放路径权值的结构体
typedef struct{
	int path;
}ArcCell,AdjMatrix[maxSite][maxSite];


//定义景点结构体
typedef struct {
	char placeName[15];//景点名称
	int placeNo;//景点编号
	char placeInfo[100];//存放景点信息
}place;

//定义校园地图
typedef struct{
	place placeArray[maxSite];//景点数组
	AdjMatrix pathArray;//路径数组
	int placeNum;//景点数量
	int pathNum;//路径总数量
}Graph;

//初始化校园地图
Graph InitGraph(){
	Graph G;
	int i,j;
	G.placeNum = 10;
	G.pathNum = 12;
	for(i=0;i<G.placeNum;i++)
		G.placeArray[i].placeNo = i;//对景点进行编号;
	strcpy(G.placeArray[0].placeName,"杭电正大门");
	strcpy(G.placeArray[0].placeInfo,"大学校门,雄伟壮观!");
	strcpy(G.placeArray[1].placeName,"行政楼");
	strcpy(G.placeArray[1].placeInfo,"学校领导的行政办公中心!");
	strcpy(G.placeArray[2].placeName,"计算机学院");
	strcpy(G.placeArray[2].placeInfo,"开启程序人生,成就美好未来!");
	strcpy(G.placeArray[3].placeName,"电子信息学院");
	strcpy(G.placeArray[3].placeInfo,"发展中国芯片产业!");
	strcpy(G.placeArray[4].placeName,"问鼎广场");
	strcpy(G.placeArray[4].placeInfo,"形似三炷香...具体原因不便解释!");
	strcpy(G.placeArray[5].placeName,"图书馆");
	strcpy(G.placeArray[5].placeInfo,"藏书丰富,学霸聚居地!");
	strcpy(G.placeArray[6].placeName,"学生活动中心");
	strcpy(G.placeArray[6].placeInfo,"学生活动场所,活动丰富精彩!");
	strcpy(G.placeArray[7].placeName,"食堂");
	strcpy(G.placeArray[7].placeInfo,"解决学生和教职工一日三餐的场所!");
	strcpy(G.placeArray[8].placeName,"27号楼");
	strcpy(G.placeArray[8].placeInfo,"作者本人所在的宿舍楼!");
	strcpy(G.placeArray[9].placeName,"32号楼");
	strcpy(G.placeArray[9].placeInfo,"女生宿舍楼,俗称公主楼!");

	for(i=0;i<G.placeNum;i++)
		for(j=0;j<G.pathNum;j++){
			G.pathArray[i][j].path = infinite;//先将每个结点间的路径初始化为无穷大
		}
		G.pathArray[0][1].path = 200;//正大门和行政楼相差200m
		G.pathArray[0][2].path = 500;//正大门和计算机学院相差500m
		G.pathArray[0][4].path = 600;//正大门和问鼎广场相差600m
		G.pathArray[1][3].path = 200;//行政楼和电子信息学院相差200m
		G.pathArray[2][5].path = 150;//计算机学院和图书馆相差150m
		G.pathArray[3][5].path = 100;//电子信息学院和图书馆相差100m
		G.pathArray[4][5].path = 100;//问鼎广场和图书馆相差100m
		G.pathArray[5][6].path = 300;//图书馆和学生活动中心相差300m
		G.pathArray[5][8].path = 500;//图书馆和27号楼相差500m
		G.pathArray[6][7].path = 50;//学生活动中心和食堂相差50m
		G.pathArray[6][8].path = 50;//学生活动中心和27号楼相差50m
		G.pathArray[8][9].path = 100;//27号楼和32号楼相差100m

		for(i=0;i<G.placeNum;i++)//无向图相反方向路径长度相同
			for(j=0;j<G.placeNum;j++)
				G.pathArray[j][i].path=G.pathArray[i][j].path;
			return G;
}

//最短路径查询
void Floyd(Graph *G){
	int v,u,w,k,j,t;
	int flag = 1;//用于标记输入数据是否正确，若输入数据符合要求，则将flag置为0

    int D[10][10],S[10][10];//D[10][10]存放顶点与顶点之间的直接路径

	for(v=0;v<G->placeNum;v++){
		for(w=0;w<G->placeNum;w++){
			D[v][w]=G->pathArray[v][w].path;//将初始路径数据存放在数组D[v][w]中
			S[v][w]=w;//初始化中间顶点
			//for(u=0;u<G->placeNum;u++)
			//	p[v][w][u] = 0;//该三维数组用于存放两景点之间是否有直接路径，若有则标记为1，无则标记为0
			//if(D[v][w]<infinite){
			//	p[v][w][v] = 1;
			//	p[v][w][w] = 1;
		}
	}

	//u为中间点
	for(u=0;u<G->placeNum;++u){
		//v为起点
		for(v=0;v<G->placeNum;++v)
			//w为终点
			for(w=0;w<G->placeNum;w++){
				if(D[v][u]+D[u][w]<D[v][w]){
					D[v][w]=D[v][u]+D[u][w];//更新最小路径
					S[v][w]=S[v][u];//更新最小路径中间顶点，第一个中间点
					//for(i=0;i<G->placeNum;i++)
					//	p[v][w][i] = p[v][u][i]||p[u][w][i];//获取两个景点之间最短路径所经过的所有景点编号
				}
			}
		
	}
	while(flag){
		printf("请输入出发地的编号:\n");
		scanf("%d",&k);
		printf("请输入目的地的编号:\n");
		scanf("%d",&j);
		if(k<0||k>=G->placeNum||j<0||j>=G->placeNum){
			printf("您输入的地点编号在本地图内没有相关记录,请重新输入!\n");
		}
		else if(k==j){
			printf("出发地和目的地相同,请重新输入!\n");
		}else{
			flag=0;//输入数据合法
			printf("从出发地到目的地的最佳(短)路径为:\n%s",G->placeArray[k].placeName);
			t=S[k][j];
			while(t!=j){
				printf("-->%s",G->placeArray[t].placeName);
				t=S[t][j];
			}
			printf("-->%s\n",G->placeArray[j].placeName);
			printf("总路线长为:%dm\n",D[k][j]);
		}
	}
}


//循环操作界面
void Interface(Graph *G)
{
	int i;
	printf("************杭州电子科技大学校园导游系统************\n");
	printf("\n");
	printf("校园景点信息如下\n");
	for(i=0;i<G->placeNum;i++){
		printf("编号:%4d 名称:%s\n",G->placeArray[i].placeNo,G->placeArray[i].placeName);
	}

	printf("\n");
	printf("*********************功能选择***********************\n");
	printf("查找两景点间的最短路径请输入1\n");
	printf("\n");
	printf("查看景点相关信息请输入2\n");
	printf("\n");
	printf("退出导游系统请输入3\n");
}

//查询景点信息
void SearchInfo(Graph *G){
	int k,flag=1;
	printf("请输入要查询的景点编号\n");
	while(flag){
		scanf("%d",&k);
		if(k<0||k>=G->placeNum){
			printf("景点编号不存在!请重新输入景点编号:\n");
		}else{
			flag=0;
		}
	}
	printf("该景点的相关信息如下:\n");
	printf("\n");
	printf("编号:%4d  名称:%s   简介:%s\n",G->placeArray[k].placeNo,G->placeArray[k].placeName,G->placeArray[k].placeInfo);
	printf("\n");
	printf("\n");
	printf("\n");
}





void main(){
	int c;
	Graph G = InitGraph();
	Interface(&G);
	scanf("%d",&c);
	while(c!=3){
		switch(c){
		case 1:Floyd(&G);Interface(&G);break;
		case 2:SearchInfo(&G);Interface(&G);break;
		case 3:exit(0);break;
		default:break;
		}
		scanf("%d",&c);
	}
}