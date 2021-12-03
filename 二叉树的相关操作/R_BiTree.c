/*计算机2003杨帆 递归实现二叉树及其相关操作*/
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

/*函数声明*/
BiTNode *R_Create(BiTree T);	//递归实现二叉树的创建
void R_PreOrder(BiTree T);		//递归实现前序遍历
void R_InOrder(BiTree T);		//递归实现中序遍历
void R_LateOrder(BiTree T);		//递归实现后序遍历
int Get_Depth(BiTree T);		//获取深度
void Get_Leaves(BiTree T,int *LeafCount);	//获取叶子数
void Get_Nodes(BiTree T,int *Nodes);		//获取结点数
void Swap(BiTree T);			//交换左右子树

/*--------------main--------------*/
int main()
{
	BiTree T = NULL;
	int leaves = 0,nodes = 0;

	T = R_Create(T);
	printf("\n先序遍历:");
	R_PreOrder(T);
	printf("\n中序遍历:");
	R_InOrder(T);
	printf("\n后序遍历:");
	R_LateOrder(T);
	Get_Leaves(T,&leaves);
	Get_Nodes(T,&nodes);
	printf("\n此二叉树的深度为:%d",Get_Depth(T));
	printf("\n此二叉树的叶子数为:%d",leaves);
	printf("\n此二叉树的结点数为:%d",nodes);
	Swap(T);
	printf("\n交换后的先序遍历:");
	R_PreOrder(T);
	return 0;
}
/*--------------------------------*/
BiTNode *R_Create(BiTree T)
{
	int data;
	printf("请输入结点的值（0表示无该子结点）：");
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