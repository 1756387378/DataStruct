#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX_VERTEX 50

//定义全局变量
int flag[MAX_VERTEX];										//判断是否访问标志
int front;													//队列头指针
int rear;													//队列尾指针
int queue[MAX_VERTEX];										//声明队列

typedef char VertexType;
typedef struct node											//邻接点结构体
{
	int adjvex;												//该邻接点在顶点数组中的下标 
	struct node *next;										//指向下一邻接点（或边）的指针域
}EdgeNode;													//边节点

typedef struct vnode										//顶点结构体
{
	VertexType vertex;										//顶点域
	EdgeNode *firstedge;									//第一条边的指针
}VertexNode;												//顶点节点

typedef struct Graph										//图结构体
{
	VertexNode AdjList[MAX_VERTEX];							//顶点数组
	int N, E;												//N，E是图的顶点个数和边的个数
}Graph, *GraphAdjList;										//图节点

//函数原型
void Menu(GraphAdjList &G);
GraphAdjList CreateALGraph();
void DFS(GraphAdjList &G, int i);
void DFSTraverseAL(GraphAdjList &G);
void BFS(GraphAdjList &G, int i);
void BFSTraverse(GraphAdjList &G);
void Visited(GraphAdjList &G, int i);

int main()
{
	GraphAdjList G = NULL;
	Menu(G);
	return 0;
}

//主菜单
void Menu(GraphAdjList &G)
{
	char op;
	printf("\t\t0.创建无向图\n");
	printf("\t\t1.深度优先搜索\n");
	printf("\t\t2.广度优先搜索\n");
	printf("\t\t3.退出\n");
	op = getchar();
	switch (op)
	{
	case '0':
		G = CreateALGraph();
		getchar();
		break;
	case '1':
		printf("深度优先搜索结果：");
		DFSTraverseAL(G);
		getchar();											//抛弃回车键
		putchar(10);
		break;
	case '2':
		printf("广度优先搜索结果：");
		BFSTraverse(G);
		getchar();											//抛弃回车键
		putchar(10);
		break;
	case '3':
		exit(0);
		break;
	default:
		while (getchar() != '\n')							//抛弃多余输入
			continue;
		printf("您的输入无效，请重新输入\n");
		break;
	}
	Menu(G);
}

//建立无向图的邻接表存储
GraphAdjList CreateALGraph()
{
	int i, j, k;
	EdgeNode *sNew, *sTemp;									//声明指向新分配空间、临时指针
	GraphAdjList G = NULL;
	G = (GraphAdjList)malloc(sizeof(Graph));
	printf("请输入顶点的个数：");
	scanf("%d", &G->N);
	printf("\n请输入边的条数：");
	scanf("%d", &G->E);
	for (i = 0; i < G->N; i++)								//建立有N个顶点的顶点表
	{
		printf("\n请输入第%d个顶点:", i + 1);
		getchar();											//抛弃回车键
		scanf("%c", &(G->AdjList[i].vertex));				//读入顶点信息
		G->AdjList[i].firstedge = NULL;						//顶点的边表头指针设为空
	}
	for (k = 0; k < G->E; k++)								//建立边表
	{
		printf("请输入边<Vi,Vj>的顶点的序号:");
		scanf("%d%d", &i, &j);

		//读入边<Vi,Vj>的顶点的序号
		//尾插法
		sNew = (EdgeNode *)malloc(sizeof(EdgeNode));		//插入到Vi邻接表中
		sNew->adjvex = j;									//邻接点序号为j
		sTemp = G->AdjList[i].firstedge;					//临时指针获取头指针位置
		if (G->AdjList[i].firstedge == NULL)				//第一个邻接点
		{
			sNew->next = NULL;
			G->AdjList[i].firstedge = sNew;
		}
		else												//非第一个邻接点
		{
			while (sTemp->next != NULL)						//循环移动，直至链尾
				sTemp = sTemp->next;
			sNew->next = NULL;								//尾指针指向空
			sTemp->next = sNew;								//插入到Vi邻接表中
		}

		//同时为邻接点建立连接
		sNew = (EdgeNode *)malloc(sizeof(EdgeNode));
		sNew->adjvex = i;									//邻接点序号为j
		sTemp = G->AdjList[j].firstedge;					//临时指针获取头指针位置
		if (G->AdjList[j].firstedge == NULL)				//第一个邻接点
		{
			sNew->next = NULL;
			G->AdjList[j].firstedge = sNew;
		}
		else												//非第一个邻接点
		{
			while (sTemp->next != NULL)						//循环移动，直至链尾
				sTemp = sTemp->next;
			sNew->next = NULL;								//尾指针指向空
			sTemp->next = sNew;								//插入到Vj的邻接表中
		}


		//头插法
		//sNew = (EdgeNode *)malloc(sizeof(EdgeNode));		//生成新的邻节点s
		//sNew->adjvex = j;									//邻接点序号为j
		//sNew->next = G->AdjList[i].firstedge;				//插入到Vi邻接表中
		//G->AdjList[i].firstedge = sNew;

		//sNew = (EdgeNode *)malloc(sizeof(EdgeNode));		//生成新的邻节点s
		//sNew->adjvex = i;									//邻接点序号为i
		//sNew->next = G->AdjList[j].firstedge;				//插入到Vj的邻接表中
		//G->AdjList[j].firstedge = sNew;
	}
	return G;
}

//深度优先搜索
void DFSTraverseAL(GraphAdjList &G)
{
	for (int i = 0; i < MAX_VERTEX; i++)
		flag[i] = 0;										//初始化为零
	//注意：如果使用flag[MAX_VERTEX] = { 0 }
	//则无法重复使用数据，并且一个数组只能这样初始化一次
	for (int i = 0; i < G->N; i++)
	{
		if (!flag[i])										//未访问过该顶点
			DFS(G, i);										//递归
	}
}

void DFS(GraphAdjList &G, int i)
{
	EdgeNode *p;
	Visited(G, i);
	flag[i] = 1;
	p = G->AdjList[i].firstedge;
	while (p)
	{
		if (!flag[p->adjvex])
			DFS(G, p->adjvex);
		p = p->next;
	}
}

//广度优先搜索
void BFSTraverse(GraphAdjList &G)
{
	front = 0;
	rear = 0;
	for (int i = 0; i < MAX_VERTEX; i++)
		flag[i] = 0;										//初始化为零
	for (int i = 0; i < G->N; i++)
	{
		if (!flag[i])
			BFS(G, i);
	}
}

void BFS(GraphAdjList &G, int i)
{
	EdgeNode *p;
	Visited(G, i);
	flag[i] = 1;
	queue[rear++] = i;										//入队
	while (front != rear)
	{
		p = G->AdjList[queue[front++]].firstedge;			//出队并访问该顶点
		while (p != NULL)
		{
			if (!flag[p->adjvex])							//未访问过该点
			{
				flag[p->adjvex] = 1;						//标记为已访问
				Visited(G, p->adjvex);						//输出当前顶点
				queue[rear++] = p->adjvex;					//将当前顶点的邻接点入队
			}
			p = p->next;									//指向下一邻接点
		}
	}
}

//输出该顶点数据
void Visited(GraphAdjList &G, int i)
{
	printf("%c ", G->AdjList[i].vertex);
}
