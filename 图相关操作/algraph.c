#include <stdio.h >
#include <stdlib.h>
#define MAXVERTEX 30
#define VertexType char

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	int weight;
}ArcNode;
typedef struct VNode
{
	VertexType data;
	int indegree;
	ArcNode *firstarc;
}VNode,AdjList[MAXVERTEX];
typedef struct 
{
	AdjList vertices;
	int vexnum,arcnum;
}AlGraph;
typedef struct
{
	int stack[MAXVERTEX];
	int top;
}Stack;

void CreateDG(AlGraph *G_ptr);
void TopoSort(AlGraph G);

int main()
{
	AlGraph G;
	CreateDG(&G);
	TopoSort(G);
	return 0;
}

void CreateDG(AlGraph *G_ptr)
{
	printf("����ͼ�Ĵ���:\n");
	printf("������ͼ�Ķ������ͻ���(vexnum,arcnum)��");
	scanf("%d,%d",&G_ptr->vexnum,&G_ptr->arcnum);
	int i,j,k,vnum = G_ptr->vexnum,anum = G_ptr->arcnum,weight;
	ArcNode *p;
	printf("�����붥����Ϣ(��ABCDE):");
	getchar();
	for(i=0;i<vnum;i++)
	{
		scanf("%c",&G_ptr->vertices[i].data);
		G_ptr->vertices[i].firstarc = NULL;
		G_ptr->vertices[i].indegree = 0;
	}
	printf("������ÿ���ߵ���㣬�յ㣨start,end��:\n");
	for(k=0;k<G_ptr->arcnum;k++)
	{
		scanf("%d,%d",&i,&j);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = G_ptr->vertices[i].firstarc;
		G_ptr->vertices[i].firstarc = p;
		G_ptr->vertices[j].indegree++;
	}
}

void TopoSort(AlGraph G)
{
	printf("����������Ϊ:");
	Stack S;
	ArcNode *p;
	S.top = 0;
	int i,j,count=0;
	for(i=0;i<G.vexnum;i++)
		if(!G.vertices[i].indegree)
			S.stack[S.top++] = i;
	while(S.top)
	{
		i = S.stack[--S.top];
		printf("%c ",G.vertices[i].data);
		count++;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			j = p->adjvex;
			if(!(--G.vertices[j].indegree))
				S.stack[S.top++] = j;
		}
	}
	if(count < G.vexnum)
		printf("���д��ڻ�\n");
}


