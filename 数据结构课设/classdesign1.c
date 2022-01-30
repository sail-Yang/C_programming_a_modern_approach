#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVERTEX 10
#define VertexType char
#define INFINITY 32767.0
#define MAXSIZE  100

/*�ṹ������*/
/*------�ڽӾ���------*/
typedef struct
{
	VertexType vexs[MAXVERTEX];				//��Ŷ�����ϢV
	double arcs[MAXVERTEX][MAXVERTEX];		//��Ź�ϵ����E
	int vexnum,arcnum;						//��ǰ�������ͻ���
}MGraph;
/*--------�ڽӱ�-------*/
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	double weight;
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
/*---��С��������ؽṹ��---*/
typedef struct 
{
	int adjvex;
	double lowcost;
}PEdge;
typedef struct
{
	int begin;
	int end;
	double weight;
}KEdge;
typedef struct
{
	int stack[MAXVERTEX];
	int top;
}Stack;
/*------��������--------*/
void MCreateUDN(MGraph *G_ptr,char filename[MAXSIZE]);	//����������
void ACreateDN(AlGraph *G_ptr,char filename[MAXSIZE]);	//����DAG��
void Menu();
//Prim�㷨
void Prim_MinSpanTree(MGraph G,int u);
int Get_MinVex(MGraph G,PEdge closedge[MAXVERTEX]);
//Kruskal�㷨
void Kruskal_MinSpanTree(MGraph G);
void OperationEdge(MGraph G, KEdge *edges);
int Find(int *parent,int f);
//�����������ڶԱ߼���������
void QuickSort(KEdge *edges ,int l,int h);
int Partition(KEdge *edges,int l,int h);
//Dijkstra�㷨����С·��
void Dijkstra(MGraph G,int source);	
//DAG���
void TopoSort(AlGraph G);
int TopoOrder(AlGraph G,Stack *T_ptr,double *ve);
void CriticalPath(AlGraph G);
/*-----main-----*/
int main()
{
	/*��������ˮ�ܵ�*/
	MGraph MG1,MG2,MG3;
	AlGraph AG1,AG2,AG3;
	MCreateUDN(&MG1,"udn1.txt");
	MCreateUDN(&MG2,"udn2.txt");
	MCreateUDN(&MG3,"udn3.txt");
	ACreateDN(&AG1,"dag1.txt");
	ACreateDN(&AG2,"dag2.txt");
	ACreateDN(&AG3,"dag3.txt");
	char order;
	do{
		Menu();
		order = getchar();
		fflush(stdin);
		system("cls");
		switch(order)
		{
			case '1': printf("��Prim�㷨��������ˮ�ܵ����跽��:\n");printf("��������1��");Prim_MinSpanTree(MG1,1);printf("��������2��");Prim_MinSpanTree(MG2,1);printf("��������3��");Prim_MinSpanTree(MG3,1);system("pause");break;
			case '2': printf("��Kruskal�㷨��������ˮ�ܵ����跽��:\n");printf("��������1��");Kruskal_MinSpanTree(MG1);printf("��������2��");Kruskal_MinSpanTree(MG2);printf("��������3��");Kruskal_MinSpanTree(MG3);system("pause");break;
			case '3': printf("����A���������������������ľ���:\n");printf("��������1��\n");Dijkstra(MG1,1);printf("��������2��\n");Dijkstra(MG2,1);printf("��������3��\n");Dijkstra(MG3,1);system("pause");break;
			case '4': printf("�����������к͹ؼ�·��:\n");printf("��������1��\n");TopoSort(AG1);CriticalPath(AG1);printf("��������2��\n");TopoSort(AG2);CriticalPath(AG2);printf("��������3��\n");TopoSort(AG3);CriticalPath(AG3);system("pause");system("cls");break;
			default: printf("���������");return 0;
		}
		system("cls");
	}while(1);
	return 0;
}
/*------end-----*/

/*��������*/
void Menu()
{
	printf("**************Menu****************\n\n\n");
	printf("   1.��Prim�㷨��������ˮ�ܵ����跽��\n\n");
	printf("   2.��Kruskal�㷨��������ˮ�ܵ����跽��\n\n");
	printf("   3.����A���������������������ľ���\n\n");
	printf("   4.�����������к͹ؼ�·��\n\n");
	printf("   5.�������˳�����\n\n");
	printf("**************Menu****************\n\n");
	printf("������ָ��:");
}
void MCreateUDN(MGraph *G_ptr,char filename[MAXSIZE])
{
	/*��1��ʼ�洢*/
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d,%d",&G_ptr->vexnum,&G_ptr->arcnum);
	char space;fscanf(fp,"%c",&space);//ȥ��'\n'
	int i,j,k,vnum = G_ptr->vexnum,anum = G_ptr->arcnum;double weight;
	/*��ʼ��*/
	for(i=1;i<=vnum;i++) fscanf(fp,"%c",&G_ptr->vexs[i]);
	for(i=1;i<=vnum;i++)
		for(j=1;j<=vnum;j++)
			G_ptr->arcs[i][j]=INFINITY;
	for(k=1;k<=anum;k++)
	{
		fscanf(fp,"%d,%d,%lf",&i,&j,&weight);
		G_ptr->arcs[i][j]=weight;
		G_ptr->arcs[j][i]=weight;
	}
}
void ACreateDN(AlGraph *G_ptr,char filename[MAXSIZE])
{
	FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d,%d",&G_ptr->vexnum,&G_ptr->arcnum);
	char space;fscanf(fp,"%c",&space);
	int i,j,k,vnum = G_ptr->vexnum,anum = G_ptr->arcnum;ArcNode *p;double weight;
	for(i=1;i<=vnum;i++)
	{
		fscanf(fp,"%c",&G_ptr->vertices[i].data);
		G_ptr->vertices[i].firstarc = NULL;
		G_ptr->vertices[i].indegree = 0;
	}
	for(k=1;k<=G_ptr->arcnum;k++)
	{
		
		fscanf(fp,"%d,%d,%lf",&i,&j,&weight);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;p->weight = weight;
		p->nextarc = G_ptr->vertices[i].firstarc;
		G_ptr->vertices[i].firstarc = p;
		G_ptr->vertices[j].indegree++;
	}
	fclose(fp);
}
void Prim_MinSpanTree(MGraph G,int u)
{
	PEdge closedge[MAXVERTEX];int i,j,k;
	for(i=1;i<=G.vexnum;i++)
	{
		if(i!=u)
		{
			closedge[i].adjvex=u;
			closedge[i].lowcost = G.arcs[u][i];
		}
	}
	closedge[u].lowcost=0;
	for(i=2;i<=G.vexnum;i++)
	{
		k=Get_MinVex(G,closedge);
		printf("(%c,%c) ",G.vexs[closedge[k].adjvex],G.vexs[k]);
		closedge[k].lowcost=0;
		for(j=1;j<=G.vexnum;j++)
		{
			if(G.arcs[k][j]<closedge[j].lowcost)
			{
				closedge[j].adjvex=k;
				closedge[j].lowcost=G.arcs[k][j];
			}
		}
	}
	printf("\n");
}
int Get_MinVex(MGraph G,PEdge closedge[MAXVERTEX])
{
	int i,index;
	double lowedge=INFINITY;
	for(i=1;i<=G.vexnum;i++)
	{
		if(closedge[i].lowcost&&closedge[i].lowcost<lowedge)
		{
			lowedge = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}
void OperationEdge(MGraph G, KEdge* edges)
{
	int i,j,k=1;
	//����ͼ�Գƣ�ֻ��ת��һ�뼴��
	for (i = 1; i <= G.vexnum; i++)
	{
		for (j = i+1; j <= G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arcs[i][j];
				k++;
			}
		}
	}
	QuickSort(edges,1,G.arcnum);
}
void QuickSort(KEdge *edges,int l,int h)
{
	int k;
	if(l<h)
	{
		k = Partition(edges,l,h);
		QuickSort(edges,l,k-1);
		QuickSort(edges,k+1,h);
	}
}
int Partition(KEdge *edges,int l,int h)
{
	int i=l,j=h;edges[0] = edges[i];
	while(i<j)
	{
		while(i<j&&edges[j].weight>=edges[0].weight) j--;
		edges[i] = edges[j];
		while(i<j&&edges[i].weight<=edges[0].weight) i++;
		edges[j] = edges[i];
	}
	edges[i] = edges[0];
	return i;
}
void Kruskal_MinSpanTree(MGraph G)
{
	int i,n,m;KEdge edges[MAXSIZE]; int parent[MAXSIZE];  
	OperationEdge(G,edges);
	for (i = 1; i <= G.vexnum; i++)
		parent[i] = 0;
	for (i = 1;i <= G.arcnum;i++)
	{//ѭ��ÿһ����
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if (n!=m)  //û�гɻ�
		{
			parent[n] = m;
			printf("(%c,%c) ",G.vexs[edges[i].begin],G.vexs[edges[i].end]);
		}
	}
	printf("\n");
}
int Find(int *parent,int f)
{
	while(parent[f] > 0)
		f = parent[f]; 
	return f;
}
void Dijkstra(MGraph G,int source)
{
	int i,j,min_node;
	int *Final = (int*)malloc(sizeof(int)*(G.vexnum+1));
	double *Dist = (double*)malloc(sizeof(double)*(G.vexnum+1)),min_path;
	for(j=1;j<=G.vexnum;j++)
	{
		Dist[j] = G.arcs[source][j];
		Final[j] = 0;	
	}
	Final[source] = 1;	//Դ�㵽Դ������·��ȷ��
	Dist[source] = 0;	//Դ�㵽Դ������·��Ϊ0
	for(i=2;i<=G.vexnum;i++)
	{
		min_path = INFINITY;
		for(j=1;j<=G.vexnum;j++)
			if(!Final[j]&&Dist[j]<min_path)
			{
				min_node = j;
				min_path = Dist[j];
			}
		Final[min_node] = 1;//��source����ĵ�Min_node���ӵ�Final����
		for(j=1;j<=G.vexnum;j++)
			if(!Final[j]&&(min_path+G.arcs[min_node][j]<Dist[j]))
				Dist[j] = min_path+G.arcs[min_node][j];
	}
	for(i=1;i<=G.vexnum;i++)
	{
		if(i!=source)
			printf("(%c��%c:%.2lf km) ",G.vexs[source],G.vexs[i],Dist[i]);
	}
	printf("\n");
}
void TopoSort(AlGraph G)
{
	printf("����������Ϊ:\t");
	Stack S;
	ArcNode *p;
	S.top = 0;
	int i,j,count=0;
	for(i=1;i<=G.vexnum;i++)
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
	printf("\n");
	if(count < G.vexnum)
		printf("���д��ڻ�\n");
}
int TopoOrder(AlGraph G,Stack *T_ptr,double *ve)
{
	Stack S;S.top = 0;
	ArcNode *p;
	int i,j,count=0;
	for(i=1;i<=G.vexnum;i++)
		if(!G.vertices[i].indegree)
			S.stack[S.top++] = i;
	T_ptr->top = 0;
	for(i=1;i<=G.vexnum;i++)
		ve[i] = 0;
	while(S.top)
	{
		i = S.stack[--S.top];
		T_ptr->stack[T_ptr->top++] = i;
		count++;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			j = p->adjvex;
			if(--G.vertices[j].indegree==0)
				S.stack[S.top++] = j;
			if((ve[i]+p->weight)>ve[j])
				ve[j] = ve[i]+p->weight;
		}
	}
	if(count < G.vexnum)
		return 0;
	else 
		return 1;
}
void CriticalPath(AlGraph G)
{
	printf("�ؼ�·�����Ϊ��");
	int i,j;char tag;
	double *ve = (double*)malloc(sizeof(double)*(G.vexnum+1)),dut,ee,el;
	double *vl = (double*)malloc(sizeof(double)*(G.vexnum+1));
	Stack T;
	ArcNode *p;
	if(!TopoOrder(G,&T,ve)){
		printf("�л���");
		return;
	}
	for(i=1;i<=G.vexnum;i++)
		vl[i] = ve[G.vexnum];
	while(T.top)
	{
		for(i=T.stack[--T.top],p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			j = p->adjvex;
			dut = p->weight;
			if(vl[j]-dut<vl[i])
				vl[i]=vl[j]-dut;
		}
	}
	for(i=1;i<=G.vexnum;i++)
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			j = p->adjvex;
			dut = p->weight;
			ee = ve[i];el = vl[j]-dut;
			/*tag = (ee==el)?'*':' ';*/
			if(ee==el)
				printf("(%c��%c) ",G.vertices[i].data,G.vertices[j].data);
			/*printf("  %d\t%d\t%.2lf\t%.2lf\t%.2lf\t%c\n",i,j,dut,ee,el,tag);*/
		}
	printf("\n\n");
}