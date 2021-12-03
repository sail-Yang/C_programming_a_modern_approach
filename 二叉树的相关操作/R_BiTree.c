/*�����2003� �ݹ�ʵ�ֶ�����������ز���*/
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

/*��������*/
BiTNode *R_Create(BiTree T);	//�ݹ�ʵ�ֶ������Ĵ���
void R_PreOrder(BiTree T);		//�ݹ�ʵ��ǰ�����
void R_InOrder(BiTree T);		//�ݹ�ʵ���������
void R_LateOrder(BiTree T);		//�ݹ�ʵ�ֺ������
int Get_Depth(BiTree T);		//��ȡ���
void Get_Leaves(BiTree T,int *LeafCount);	//��ȡҶ����
void Get_Nodes(BiTree T,int *Nodes);		//��ȡ�����
void Swap(BiTree T);			//������������

/*--------------main--------------*/
int main()
{
	BiTree T = NULL;
	int leaves = 0,nodes = 0;

	T = R_Create(T);
	printf("\n�������:");
	R_PreOrder(T);
	printf("\n�������:");
	R_InOrder(T);
	printf("\n�������:");
	R_LateOrder(T);
	Get_Leaves(T,&leaves);
	Get_Nodes(T,&nodes);
	printf("\n�˶����������Ϊ:%d",Get_Depth(T));
	printf("\n�˶�������Ҷ����Ϊ:%d",leaves);
	printf("\n�˶������Ľ����Ϊ:%d",nodes);
	Swap(T);
	printf("\n��������������:");
	R_PreOrder(T);
	return 0;
}
/*--------------------------------*/
BiTNode *R_Create(BiTree T)
{
	int data;
	printf("���������ֵ��0��ʾ�޸��ӽ�㣩��");
	scanf("%d",&data);
	if(data == 0)
		return NULL;
	T = (BiTNode*)malloc(sizeof(BiTNode));
	T->data = data;
	T->lchild = R_Create(T->lchild);
	T->rchild = R_Create(T->rchild);
	return T;
}

void R_PreOrder(BiTree T)
{
	if(T == NULL)
		return;
	printf("%d ",T->data);
	R_PreOrder(T->lchild);
	R_PreOrder(T->rchild);
}

void R_InOrder(BiTree T)
{
	if(T == NULL)
		return;
	R_InOrder(T->lchild);
	printf("%d ",T->data);
	R_InOrder(T->rchild);
}

void R_LateOrder(BiTree T)
{
	if(T == NULL)
		return;
	R_LateOrder(T->lchild);
	R_LateOrder(T->rchild);
	printf("%d ",T->data);
}

int Get_Depth(BiTree T)
{
	if (T == NULL)
		return 0;
	else{
		if(Get_Depth(T->lchild)>Get_Depth(T->rchild))
			return (Get_Depth(T->lchild)+1);
		else
			return (Get_Depth(T->rchild)+1);
	}
}

void Get_Leaves(BiTree T,int *LeafCount)
{
	if(T)
	{
		if(T->lchild==NULL&&T->rchild == NULL)
			(*LeafCount)++;
		Get_Leaves(T->lchild,LeafCount);
		Get_Leaves(T->rchild,LeafCount);
	}
	return;
}

void Get_Nodes(BiTree T,int *Nodes)
{
	if(T)
	{
		(*Nodes)++;
		Get_Nodes(T->lchild,Nodes);
		Get_Nodes(T->rchild,Nodes);
	}
	return;
}

void Swap(BiTree T)
{
	BiTree Temp;
	if(T)
	{
		Temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = Temp;
		Swap(T->lchild);
		Swap(T->rchild);
	}
}