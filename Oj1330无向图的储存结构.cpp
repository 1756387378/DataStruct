#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 300

int front;
int rear;
int matrix[MAX_VERTEX][MAX_VERTEX] = { 0 };

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
void List(GraphAdjList &G, int i);
void AdjacencyList(GraphAdjList &G);
void Visited(GraphAdjList &G, int i);
void Matrix(GraphAdjList &G);

int main()
{
	GraphAdjList G = NULL;
	G = CreateALGraph();
	Matrix(G);
	printf("\n");
	AdjacencyList(G);
	return 0;
}

GraphAdjList CreateALGraph()
{
	int i, j, k, count;
	EdgeNode *sNew, *sTemp, *sPre;
	GraphAdjList G = NULL;
	G = (GraphAdjList)malloc(sizeof(Graph));
	scanf("%d %d", &G->N, &G->E);
	for (i = 0; i < G->N; i++)
	{
		G->AdjList[i].vertex = i;
		G->AdjList[i].firstedge = NULL;
	}
	for (k = 0; k < G->E; k++)
	{
		scanf("%d %d", &i, &j);
		matrix[i][j] = 1;
		matrix[j][i] = 1;

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
				if (sTemp->adjvex >= j)
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
				if (sTemp->adjvex >= i)
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

void Matrix(GraphAdjList &G)
{
	for (int i = 0; i < G->N; i++)
	{
		for (int j = 0; j < G->N; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

void AdjacencyList(GraphAdjList &G)
{
	for (int i = 0; i < G->N; i++)
	{
		printf("%d ", i);
		List(G, i);
		printf("\n");
	}
}

void List(GraphAdjList &G, int i)
{
	EdgeNode *p;
	p = G->AdjList[i].firstedge;
	while (p != NULL)
	{
		Visited(G, p->adjvex);
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
0 1
1 5
0 4
2 5
1 4
2 3
3 5

Sample Output
0 1 0 0 1 0 
1 0 0 0 1 1 
0 0 0 1 0 1 
0 0 1 0 0 1 
1 1 0 0 0 0 
0 1 1 1 0 0 

0 1 4 
1 0 4 5 
2 3 5 
3 2 5 
4 0 1 
5 1 2 3 
*/
