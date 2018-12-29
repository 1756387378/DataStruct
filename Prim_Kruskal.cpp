#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define NUMVERTEX 50
#define NUMEDGE 50
#define MAXCOST 999									//表示不可达
typedef char VertexType;
typedef int EdgeType;

typedef struct MEdge
{
	int start;
	int end;
	int weight;
}Edge;

typedef struct MGraph
{
	VertexType vexs[NUMVERTEX];
	EdgeType edges[NUMVERTEX][NUMVERTEX];
	int sumvertex;
	int sumedge;
}Graph;

Edge ed[NUMEDGE];
Edge tree[NUMEDGE];

//函数原型
Graph *CreateGraph(Graph *G);
void Prim(Graph *G);
void Kruskal(Graph *G);
int Find(int father[], int v);

int main()
{
	Graph *G = NULL;
	G = CreateGraph(G);
	printf("---------------------------------\n");
	printf("Prim算法生成最小生成树：\n");
	Prim(G);
	printf("\n---------------------------------\n");
	printf("Kruskal算法生成最小生成树：\n");
	Kruskal(G);
	free(G);
	system("pause");
	return 0;
}

Graph *CreateGraph(Graph *G)
{
	int a, b;
	printf("请输入顶点个数和边的条数：");
	G = (Graph *)malloc(sizeof(Graph));
	scanf("%d%d", &G->sumvertex, &G->sumedge);
	for (int i = 0; i < G->sumvertex; i++)
	{
		getchar();
		printf("%d号顶点对应-->", i);
		scanf("%c", &(G->vexs[i]));
	}
	for (int i = 0; i < G->sumvertex; i++)
		for (int j = 0; j < G->sumvertex; j++)
		{
			if (i == j)
				G->edges[i][j] = G->edges[j][i] = 0;
			else
				G->edges[i][j] = MAXCOST;
		}
	for (int i = 0; i < G->sumedge; i++)
	{
		printf("请输入边<Vi,Vj>的顶点的序号:");
		scanf("%d %d", &a, &b);
		printf("请输入权值：");
		scanf("%d", &G->edges[a][b]);
		G->edges[b][a] = G->edges[a][b];
		ed[i].weight = G->edges[b][a];
		ed[i].start = a;
		ed[i].end = b;
	}
	printf("---------------------------------\n");
	printf("对应矩阵如下：\n");
	for (int i = 0; i < G->sumvertex; i++)
	{
		for (int j = 0; j < G->sumvertex; j++)
		{
			if (G->edges[i][j] == MAXCOST)
				printf("    ∞");
			else
				printf("%6d", G->edges[i][j]);
		}
		printf("\n");
	}
	return G;
}

void Prim(Graph *G)								//最小生成树存于数组tree中，对应的边值在cost中
{
	int flag[NUMVERTEX] = { 0 };				//标记点是否进入集合
	int k, temp, mincost, sumcost = 0;
	int tree[NUMVERTEX];
	int cost[NUMVERTEX];
	for (int i = 0; i < G->sumvertex; i++)
	{
		cost[i] = G->edges[0][i];				//从存储序号为0的顶点出发生成最小生成树
		tree[i] = 0;							//每个顶点到自身距离为零
	}
	flag[0] = 1;
	temp = 0;
	for (int i = 1; i < G->sumvertex; i++)		//N-1次循环，寻找当前最小权值的边
	{
		mincost = MAXCOST;
		for (int j = 1; j < G->sumvertex; j++)	//寻找最小权值
			if (flag[j] == 0 && cost[j] < mincost)
			{
				mincost = cost[j];
				k = j;							//记录最小边
			}
		flag[k] = 1;						    //k进入了U集合
		for (int j = 1; j < G->sumvertex; j++)	//更新权值
			if (flag[j] == 0 && G->edges[k][j] < cost[j])
			{
				cost[j] = G->edges[k][j];
				tree[j] = k;
			}
		for (int i = 0; i < G->sumvertex; i++)
			if (G->edges[i][k] == cost[k] && flag[i] == 1)
			{
				temp = i;
				break;
			}
		printf("%c-->%c %d\n", G->vexs[temp], G->vexs[k], cost[k]);
	}
	for (int i = 0; i < G->sumvertex; i++)
		sumcost += cost[i];
	printf("权值：%d", sumcost);
}

void Kruskal(Graph *G)
{
	int father[NUMVERTEX];
	int i, j, vStart, vEnd, sum = 0;
	Edge tw, ts, te;
	for (int i = 0; i < G->sumedge; i++)			//排序
	{
		for (int j = i + 1; j < G->sumedge; j++)
		{
			if (ed[i].weight > ed[j].weight)
			{
				tw.weight = ed[i].weight;
				ed[i].weight = ed[j].weight;
				ed[j].weight = tw.weight;

				ts.start = ed[i].start;
				ed[i].start = ed[j].start;
				ed[j].start = ts.start;

				te.end = ed[i].end;
				ed[i].end = ed[j].end;
				ed[j].end = te.end;
			}
		}
	}
	for (i = 0; i < G->sumvertex; i++)
		father[i] = -1;
	i = 0; j = 0;
	while (i < G->sumedge &&j < G->sumvertex - 1)
	{
		vStart = Find(father, ed[i].start);		//获取起点的终点序号
		vEnd = Find(father, ed[i].end);			//获取终点的终点序号
		if (vStart != vEnd)
		{
			father[vEnd] = vStart;
			tree[j] = ed[i];
			j++;
		}
		i++;
		for (int t = 0; t < G->sumvertex; t++)
			printf("%d  ", father[t]);
		printf("\n");
	}
	for (int i = 0; i < j; i++)
	{
		printf("%c-->%c  %d\n", G->vexs[tree[i].start], G->vexs[tree[i].end], tree[i].weight);
		sum += tree[i].weight;
	}
	printf("权值：%d\n", sum);
}

int Find(int father[], int v)					//寻找顶点V所在树的根结点
{
	int t;

	t = v;
	while (father[t] >= 0)
		t = father[t];
	return t;
}
