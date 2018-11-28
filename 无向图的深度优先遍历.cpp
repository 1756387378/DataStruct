#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 101

int flag[MAX_VERTEX];
int front;
int rear;
int queue[MAX_VERTEX];

typedef int VertexType;
typedef struct node
{
	int adjvex;
	struct node *next;
}EdgeNode;

typedef struct vnode
{
	VertexType vertex;
	EdgeNode *firstedge;
}VertexNode;

typedef struct Graph
{
	VertexNode AdjList[MAX_VERTEX];
	int N, E;
}Graph, *GraphAdjList;

GraphAdjList CreateALGraph();
void DFS(GraphAdjList &G, int i);
void DFSTraverseAL(GraphAdjList &G);
void Visited(GraphAdjList &G, int i);

int main()
{
	GraphAdjList G = NULL;
	G = CreateALGraph();
	DFSTraverseAL(G);
	printf("\n");
	return 0;
}

GraphAdjList CreateALGraph()
{
	int i, j, k, count;
	EdgeNode *sNew, *sTemp, *sPre;
	GraphAdjList G = NULL;
	G = (GraphAdjList)malloc(sizeof(Graph));
	scanf("%d %d", &G->N, &G->E);
	for (i = 1; i <= G->N; i++)
	{
		G->AdjList[i].vertex = i;
		G->AdjList[i].firstedge = NULL;
	}
	for (k = 0; k < G->E; k++)
	{
		scanf("%d %d", &i, &j);
		sNew = (EdgeNode *)malloc(sizeof(EdgeNode));
		sNew->adjvex = j;
		sNew->next = NULL;
		sPre = sTemp = G->AdjList[i].firstedge;
		if (G->AdjList[i].firstedge == NULL)
			G->AdjList[i].firstedge = sNew;
		else
		{
			count = 1;
			while (1)
			{
				if (sTemp->adjvex <= j)
				{
					if (count == 1)
					{
						G->AdjList[i].firstedge = sNew;
						sNew->next = sTemp;
						break;
					}
					else
					{
						sPre->next = sNew;
						sNew->next = sTemp;
						break;
					}
				}
				else if (sTemp->next == NULL)
				{
					sTemp->next = sNew;
					break;
				}
				count++;
				sPre = sTemp;
				sTemp = sTemp->next;
			}
		}

		sNew = (EdgeNode *)malloc(sizeof(EdgeNode));
		sNew->adjvex = i;
		sNew->next = NULL;
		sPre = sTemp = G->AdjList[j].firstedge;
		if (G->AdjList[j].firstedge == NULL)
			G->AdjList[j].firstedge = sNew;
		else
		{
			count = 1;
			while (1)
			{
				if (sTemp->adjvex <= i)
				{
					if (count == 1)
					{
						G->AdjList[j].firstedge = sNew;
						sNew->next = sTemp;
						break;
					}
					else
					{
						sPre->next = sNew;
						sNew->next = sTemp;
						break;
					}
				}
				else if (sTemp->next == NULL)
				{
					sTemp->next = sNew;
					break;
				}
				count++;
				sPre = sTemp;
				sTemp = sTemp->next;
			}
		}
	}
	return G;
}

void DFSTraverseAL(GraphAdjList &G)
{
	for (int i = 1; i <= MAX_VERTEX; i++)
		flag[i] = 0;
	for (int i = 1; i <= G->N; i++)
	{
		if (!flag[i])
			DFS(G, i);
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

void Visited(GraphAdjList &G, int i)
{
	printf("%d ", G->AdjList[i].vertex);
}



/*
Sample Input
6 7
1 2
2 4
3 4
1 3
4 6
3 5
5 4

Sample Output
1 3 5 4 6 2
*/
