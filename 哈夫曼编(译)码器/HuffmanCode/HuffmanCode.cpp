#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int weight;
	char ch;
	int parent,lchild,rchild;//动态分配数组存储赫夫曼树
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;//动态分配数组存储赫夫曼编码表

HuffmanTree HT;
HuffmanCode HC;
int n=0;
int *we;
char *ch;

void select(HuffmanTree HT, int j, int &s1, int &s2);//选择parent为0且weight最小的两个结点,其序号分别为s1和s2
void Init();//功能I:从终端读入字符集大小为n,以及n个字符和n个权值,建立哈夫曼树
void Encoding(HuffmanCode &HC);//功能E:进行赫夫曼编码
void TreePrinting();//功能D:进行哈夫曼树的译码输出
void HuffmanCoding(HuffmanTree &HT,int n,char *ch,int *we);//初始化赫夫曼树各个结点的函数
void Free();//释放所有结点


//功能I:从终端读入字符集大小为n,以及n个字符和n个权值,建立哈夫曼树
void Init(){

	int i;
	printf("请输入字符集的个数：\n");
	scanf("%d",&n);
	while(n<2){
		printf("输入的个数必须至少大于或等于2，请重新输入");
		scanf("%d",&n);
	}
	ch = (char *)malloc(n*sizeof(char));
	printf("请输入所有字符:\n");
	getchar();//这里要读掉一个换行

	for(i=0;i<n;i++){
		scanf("%c",&ch[i]);
	}
	
	we=(int *)malloc(n*sizeof(int));
	printf("请输入对应的每个字符的权重:\n");
	for(i=0;i<n;++i)
		scanf("%d",&we[i]);
	HuffmanCoding(HT,n,ch,we);
	printf("成功建立哈夫曼树!\n");

}


//选择parent为0且weight最小的两个结点,其序号分别为s1和s2
void select(HuffmanTree HT, int j, int &s1, int &s2){
	int i;
	
	//找到第一个parent为0的结点,作为比较的基数
	for(i=1;i<=j;i++)
		if(HT[i].parent==0){
			s1 = i;
			break;
		}

	//找到parent为0且weight最小结点,其序号为s1
	for(;i<=j;i++){
		if((HT[i].parent==0)&&(HT[i].weight<HT[s1].weight))
			s1=i;
	}
	
	HT[s1].parent=1;//要注意防止同个结点被找到两次，临时置标记1

    //找到第一个parent为0的结点,作为比较的基数
	for(i=1;i<=j;i++){
		if(HT[i].parent==0){
			s2=i;
			break;
			}
	}

    //找到parent为0且weight第二小的结点,其序号为s2
	for(;i<=j;i++){
		if((HT[i].parent==0)&&(i!=s1)&&(HT[i].weight<HT[s2].weight)){
		    s2=i;
		}
	}
}


//初始化赫夫曼树各个结点的函数
void HuffmanCoding(HuffmanTree &HT,int n,char *ch,int *we){
	int m;
	m=2*n-1; //一棵n个叶子结点的哈夫曼树共有2n-1个结点
	int i,s1,s2;
	HT=(HTNode*)malloc((m+1)*sizeof(HTNode));
	

	HTNode *p;//声明一个指针p用于遍历

	//初始化哈夫曼树的叶子
	for(p=HT+1,i=1 ; i<=n ; ++p,++i,++we,++ch){
		p->ch = *ch;
		p->weight = *we;
		p->parent = p->lchild = p->rchild = 0;
	}
    
	//初始化哈夫曼树的所有非叶子结点
	for(; i<=m ; ++i,++p){
		p->ch = 0 ;
		p->weight =0;
		p->parent = p->lchild = p->rchild = 0;
	}

	//完善哈夫曼树，对所有的非叶子结点进行赋值
	for(i=n+1;i<=m;++i){
		select(HT,i-1,s1,s2);//初始要传入i-1=n的叶子结点，i++每次循环增加新的结点进HT
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}



//功能E:进行赫夫曼编码
void Encoding(HuffmanCode &HC){

	HC = (char**)malloc((n+1)*sizeof(char*));//分配n个字符编码的头指针向量
	char *cd;//分配求编码的工作空间
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1] = '\0';//每条编码的结束符
	int i,start,c,f;
	for(i=1;i<=n;++i){//逐个字符求哈夫曼编码
		start = n-1;//编码结束符位置
		for(c=i,f=HT[i].parent ; f!=0 ; c=f,f=HT[f].parent){//从叶子到根逆向求编码
			if(HT[f].lchild==c) cd[--start]='0';//左孩子“0”，逆向--start，从叶子结点开始
			else cd[--start]='1';//右孩子“1”，
		}
			HC[i] = (char *)malloc((n-start)*sizeof(char));//为第i个字符编码分配空间
			strcpy(HC[i],&cd[start]);//从cd复制编码串到HC
		}
		free(cd);
		printf("编码成功！");
}





//功能D:进行哈夫曼树的译码输出
void TreePrinting(){
	int i;
	for(i=1;i<2*n;i++){
		printf("%c%8d%8d%8d%8d\n",HT[i].ch,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
	printf("打印结束!\n");
}

void Free(){
	free(HT);
	free(HC);
	free(we);
	free(ch);
}

int main(){
	char choice;

	while(1){
		printf("*****上机实验3：哈夫曼编/译码器*****\n");
		printf("菜单功能栏\n");
		printf("I:初始化\n");
		printf("E:编码\n");
		printf("D:译码\n");
		printf("Q:退出\n");
		scanf("%c",&choice);
		
		switch(choice){
		    case 'I': Init(); break;
		    case 'E': Encoding(HC); break;
		    case 'D': TreePrinting(); break;
			case 'Q': Free();exit(1);
		    default:printf("输入错误!\n");
		}
		getchar();
	}
	return 0;
	}


