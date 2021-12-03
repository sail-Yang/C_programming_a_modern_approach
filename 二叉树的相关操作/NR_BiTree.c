/*�����2003� �ǵݹ�ʵ�ֶ�����������ز���*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct stack
{
	char flag;
	BiTree node;
}FlagStack;

/*��������*/
BiTNode *NR_Create(BiTree T);	//�ǵݹ�ʵ�ֶ������Ĵ���
void NR_PreOrder(BiTree T);		//�ǵݹ�ʵ��ǰ�����
void NR_InOrder(BiTree T);		//�ǵݹ�ʵ���������
void NR_LateOrder(BiTree T);	//�ǵݹ�ʵ�ֺ������
void NR_LevelOrder(BiTree T);	//�ǵݹ�ʵ�ֲ�α���
int Get_Depth(BiTree T);		//��ȡ���
int Get_Leaves(BiTree T);		//��ȡҶ����
int Get_Nodes(BiTree T);		//��ȡ�����
void Swap(BiTree T);			//������������


int main()
{
	BiTree T = NULL;
	T = NR_Create(T);
	printf("\n�������:");
	NR_PreOrder(T);
	printf("\n�������:");
	NR_InOrder(T);
	printf("\n�������:");
	NR_LateOrder(T);
	printf("\n��α���:");
	NR_LevelOrder(T);
	printf("\n�˶����������Ϊ:%d",Get_Depth(T));
	printf("\n�˶�������Ҷ����Ϊ:%d",Get_Leaves(T));
	printf("\n�˶������Ľ����Ϊ:%d",Get_Nodes(T));
	Swap(T);
	printf("\n��������������:");
	NR_PreOrder(T);
	return 0;
}

BiTNode *NR_Create(BiTree T)
{
	BiTree Arr_node[MAX_NODES],node;
	int i,j,data;
	printf("���������λ��(i)����ֵ(data)(��ʽΪi,data):");
	scanf("%d,%d",&i,&data);
	while(i!=0)
	{
		node = (BiTNode*)malloc(sizeof(BiTNode));
		node->data = data;
		node->lchild = NULL;
		node->lchild = NULL;
		Arr_node[i] = node;
		if(i==1)
			T = node;
		else
		{
			j = i/2;
			if(i%2 == 0)
				Arr_node[j]->lchild = node;
			else
				Arr_node[j]->rchild = node;
		}
		printf("���������λ��(i)����ֵ(data)(��ʽΪi,data):");
		scanf("%d,%d",&i,&data);
	}
	return T;
}

void NR_PreOrder(BiTree T)
{
	BiTree Stack[MAX_NODES];
	int Top = 0;
	BiTree node = T;
	while(node || Top)
	{
		while(node!=NULL)
		{
			if(Top>=MAX_NODES)
			{
				printf("ERROR!!!");
				return;
			}else{
				Stack[Top++] = node;
				printf("%d ",node->data);
				node = node->lchild;
			}
		}
		node = Stack[--Top]->rchild;
	}
	return;
}

void NR_InOrder(BiTree T)
{
	BiTree Stack[MAX_NODES];
	int Top = 0;
	BiTree node = T;
	while(node || Top)
	{
		if(Top>=MAX_NODES)
		{
			printf("ERROR!!!");
			return;
		}else{
			if(node)
			{
				Stack[Top++] = node;
				node = node->lchild;
			}else{
				node = Stack[--Top];
				printf("%d ",node->data);
				node = node->rchild;
			}
		}
	}
	return;
}

void NR_LateOrder(BiTree T)
{
	FlagStack Stack[MAX_NODES];
	int Top = 0;
	char flag;
	BiTree node = T;
	while(node || Top)
	{
		if(node)
		{
			Stack[Top].node = node;
			Stack[Top++].flag = 'N';
			node = node->lchild;
		}else{
			node = Stack[--Top].node;
			flag = Stack[Top].flag;
			if(flag=='N')
			{
				Stack[Top].node = node;
				Stack[Top++].flag = 'Y';
				node = Stack[Top-1].node->rchild;
			}else{
				printf("%d ",node->data);
				node = NULL;
			}
		}
	}
	return;
}

void NR_LevelOrder(BiTree T)
{
	BiTree Queue[MAX_NODES];
	int rear = 0,front = -1;
	BiTree node = T;
	Queue[rear] = T;
	while(rear!=front)
	{
		printf("%d ",Queue[++front]->data);
		if(Queue[front]->lchild)
			Queue[++rear] = Queue[front]->lchild;
		if(Queue[front]->rchild)
			Queue[++rear] = Queue[front]->rchild;
	}
	return;
}
int Get_Nodes(BiTree T)
{
	int AllNodes = 0;
	BiTree Queue[MAX_NODES];
	int rear = 0,front = -1;
	BiTree node = T;
	Queue[rear] = T;
	while(rear!=front)
	{
		front++;
		AllNodes++;
		if(Queue[front]->lchild)
			Queue[++rear] = Queue[front]->lchild;
		if(Queue[front]->rchild)
			Queue[++rear] = Queue[front]->rchild;
	}
	return AllNodes;
}

int Get_Leaves(BiTree T)
{
	int AllLeaves = 0;
	BiTree Queue[MAX_NODES];
	int rear = 0,front = -1;
	BiTree node = T;
	Queue[rear] = T;
	while(rear!=front)
	{
		front++;
		if(Queue[front]->lchild==NULL&&Queue[front]->rchild==NULL)
		{
			AllLeaves++;
			continue;
		}
		if(Queue[front]->lchild)
			Queue[++rear] = Queue[front]->lchild;
		if(Queue[front]->rchild)
			Queue[++rear] = Queue[front]->rchild;
	}
	return AllLeaves;
}

int Get_Depth(BiTree T)
{
	int Max_Depth = 0,Level = 1,rear = 0,front = -1,last = 0;
	BiTree Queue[MAX_NODES];
	BiTree node = T;
	Queue[rear] = T;
	while(rear!=front)
	{
		front++;
		if(Queue[front]->lchild)
			Queue[++rear] = Queue[front]->lchild;
		if(Queue[front]->rchild)
			Queue[++rear] = Queue[front]->rchild;
		if(front==last)
		{
			Max_Depth++;
			last = rear;
		}
	}
	return Max_Depth;
}

void Swap(BiTree T)
{
	BiTree node = T,temp;
	int Top = 0;
	BiTree Stack[MAX_NODES];
	if(T)
		Stack[Top++] = T;

	while(Top)
	{
		if(Top>=MAX_NODES)
		{
			printf("ERROR!!!");
			return;
		}else{
			node = Stack[--Top];
			temp = node->lchild;
			node->lchild = node->rchild;
			node->rchild = temp;
			if(node->lchild)
				Stack[Top++] = node->lchild;
			if(node->rchild)
				Stack[Top++] = node->rchild;
		}
	}
    return;
}