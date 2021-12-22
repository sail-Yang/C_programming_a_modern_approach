/*���ڽӾ��󴴽�ͼ����PRIM�㷨�Ϳ�³˹�����㷨ʵ����С������*/
#include <stdio.h>
#include <stdlib.h>
#define MAXVERTEX 30
#define INFINITY INT_MAX
#define VertexType char


/*�ڽӾ���*/
typedef struct
{
	VertexType vexs[MAXVERTEX];
	int arcs[MAXVERTEX][MAXVERTEX];
	int vexnum,arcnum;	//��ǰ�������ͻ���
}Graph;

/*����BFS�Ķ���*/
typedef struct
{
	int queue[MAXVERTEX];
	int rear,front,len;
}Queue;

typedef struct 
{
	int adjvex;
	int lowcost;
}Edge;

void CreateUDG(Graph *G_ptr);	//����һ������ͼ
void CreateUDN(Graph *G_ptr);	//����һ��������
void PrintUDG(Graph G);
/*description:DFS�㷨���*/
void DFSAL(Graph G,int i,int visited[MAXVERTEX]);
void DFSTraverse(Graph G);
/*description:BFS�㷨���*/
void BFSAL(Graph G,int i,int visited[MAXVERTEX]);
void BFSTraverse(Graph G);
void InitQueue(Queue *Q_ptr);
void EnQueue(Queue *Q_ptr,int i);
void DeQueue(Queue *Q_ptr,int *p);
/*description:����С������*/
void Prim_MinSpanTree(Graph G,int u);
int Get_MinVex(Graph G,Edge closedge[MAXVERTEX]);


int main()
{ 
	int i,j,u;
	Graph G1,G2;
	CreateUDG(&G1);
	CreateUDN(&G2);
	DFSTraverse(G1);
	printf("\n");
	BFSTraverse(G1);
	printf("\n������������С��������ʼ�����:");
	scanf("%d",&u);
	Prim_MinSpanTree(G2,u-1);
	return 0;
}

void CreateUDG(Graph *G_ptr)
{
	printf("����ͼ�Ĵ���:\n");
	printf("������ͼ�Ķ������ͻ���(vexnum,arcnum)��");
	scanf("%d,%d",&G_ptr->vexnum,&G_ptr->arcnum);
	int i,j,k,vnum = G_ptr->vexnum,anum = G_ptr->arcnum;
	printf("�����붥����Ϣ(��ABCDE):");
	getchar();
	for(i=0;i<vnum;i++)
		scanf("%c",&G_ptr->vexs[i]);
	for(i=0;i<vnum;i++)
		for(j=0;j<vnum;j++)
			G_ptr->arcs[i][j]=0;
	printf("������ÿ���ߵ���㣬�յ㣨start,end��:\n");
	for(k=0;k<anum;k++)
	{
		scanf("%d,%d",&i,&j);
		if(i<0||i>=vnum||j<0||j>=vnum)
			printf("�����������������:\n");
		else
		{
			G_ptr->arcs[i][j]=1;
			G_ptr->arcs[j][i]=1;
		}
	}
}

void CreateUDN(Graph *G_ptr)
{
	printf("�������Ĵ���:\n");
	printf("������ͼ�Ķ������ͻ���(vexnum,arcnum)��");
	scanf("%d,%d",&G_ptr->vexnum,&G_ptr->arcnum);
	int i,j,k,vnum = G_ptr->vexnum,anum = G_ptr->arcnum,weight;
	printf("�����붥����Ϣ(��ABCDE):");
	getchar();
	for(i=0;i<vnum;i++)
		scanf("%c",&G_ptr->vexs[i]);
	for(i=0;i<vnum;i++)
		for(j=0;j<vnum;j++)
			G_ptr->arcs[i][j]=INFINITY;
	printf("������ÿ���ߵ���㣬�յ㣬Ȩֵ��start,end,weight��:\n");
	for(k=0;k<anum;k++)
	{
		scanf("%d,%d,%d",&i,&j,&weight);
		if(i<0||i>=vnum||j<0||j>=vnum)
			printf("�����������������:\n");
		else
		{
			G_ptr->arcs[i][j]=weight;
			G_ptr->arcs[j][i]=weight;
		}
	}
}

void PrintUDG(Graph G)
{
	int i,j,k;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(G.arcs[i][j]!=0)
				printf("(%c,%c) ",G.vexs[i],G.vexs[j]);
		}
	}
}

void DFSAL(Graph G,int i,int visited[MAXVERTEX])
{
	int j;
	printf("%c ",G.vexs[i]);
	visited[i] = 1;
	for(j=0;j<G.vexnum;j++)
		if(!visited[j]&&G.arcs[i][j]==1)
			DFSAL(G,j,visited);

}

void DFSTraverse(Graph G)
{
	int i,visited[MAXVERTEX];
	printf("��������������Ϊ:");
	for(i=0;i<G.vexnum;i++)
		visited[i]=0;
	DFSAL(G,0,visited);
}


void BFSTraverse(Graph G)
{
	printf("��������������Ϊ:");
	int i,j,visited[MAXVERTEX];
	for(i=0;i<G.vexnum;i++)
		visited[i]=0;
	Queue Q;
	InitQueue(&Q);
	EnQueue(&Q,0);
	visited[0]=1;
	while(Q.len!=0)
	{
		DeQueue(&Q,&i);
		printf("%c ",G.vexs[i]);
		for(j=0;j<G.vexnum;j++)
		{
			if(G.arcs[i][j]==1&&!visited[j])
			{
				visited[j]=1;
				EnQueue(&Q,j);
			}	
		}
	}
}

void InitQueue(Queue *Q_ptr)
{
	Q_ptr->len = 0;
	Q_ptr->front = 0;
	Q_ptr->rear = 0;
}
void EnQueue(Queue *Q_ptr,int i)
{
	if(Q_ptr->len<MAXVERTEX)
	{
		Q_ptr->queue[Q_ptr->rear] = i;
		Q_ptr->rear = (Q_ptr->rear+1)%MAXVERTEX;
		Q_ptr->len++;
	}else
		printf("����������\n");
}
void DeQueue(Queue *Q_ptr,int *p)
{
	if(Q_ptr->len>0)
	{
		*p = Q_ptr->queue[Q_ptr->front];
		Q_ptr->front = (Q_ptr->front+1)%MAXVERTEX;
		Q_ptr->len--;
	}else
		printf("�����ǿյģ�\n");
}

void Prim_MinSpanTree(Graph G,int u)
{
	Edge closedge[MAXVERTEX];
	int i,j,k;
	for(i=0;i<G.vexnum;i++)
	{
		if(i!=u)
		{
			closedge[i].adjvex=u;
			closedge[i].lowcost = G.arcs[u][i];
		}
	}
	closedge[u].lowcost=0;
	for(i=1;i<G.vexnum;i++)
	{
		k=Get_MinVex(G,closedge);
		printf("(%c,%c) ",G.vexs[closedge[k].adjvex],G.vexs[k]);
		closedge[k].lowcost=0;
		for(j=0;j<G.vexnum;j++)
		{
			if(G.arcs[k][j]<closedge[j].lowcost)
			{
				closedge[j].adjvex=k;
				closedge[j].lowcost=G.arcs[k][j];
			}
		}
	}
}

int Get_MinVex(Graph G,Edge closedge[MAXVERTEX])
{
	int i,index,lowedge=INFINITY;
	for(i=0;i<G.vexnum;i++)
	{
		if(closedge[i].lowcost&&closedge[i].lowcost<lowedge)
		{
			lowedge = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}