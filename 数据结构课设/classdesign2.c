#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STRSIZE 200
#define MAX_CODESIZE 100
/*�ṹ������*/
typedef struct Node
{
	struct Node *parent,*lchild,*rchild;
	int weight;
	int flag;
}Node,*HfmTree;

typedef struct HC
{
	char character;		//�ַ�
	int fequency;		//�ַ���Ƶ��
	char code[MAX_CODESIZE];//���ַ���Ӧ�Ĺ���������
}HC;

typedef struct list
{
	HC *HCList;
	int Len;
}List,*ListPtr;

typedef struct leaf
{
	Node *node;
	struct leaf *next;
}leaf,*Leaves;

typedef struct stack
{
	Node *node;
	int flag;
}Stack;


/*��������*/
List GetFrequency(char *str);								//��ȡ�����ַ����ĸ��ַ�Ƶ��
void PrintFrequency(List L);						//��ӡ���ַ���Ƶ��
HfmTree CreateHuffmanTree(List L);					//�����������
Node *GetMinLeaf(Leaves *LeafList_ptr);				//��ȡ��СȨֵ��Ҷ�ӣ����Ҵ�Ҷ���б���ɾ���˽ڵ�
void InsertNewLeaf(Leaves *LeafList_ptr,Node *root);//��Ҷ���б��в����µ�Ҷ�ӽڵ㣬ȨֵΪ��С�����ĺ�
void ClearLeaves(Leaves *LeafList_ptr);				//�ͷ�Ҷ���б�
leaf *GetPreNode(Leaves LeafList,leaf *p);	//��ȡҶ���б���һ������ǰһ�����
void GetHC(HfmTree T,ListPtr L_ptr);		//��ȡHfm����(HC)
int InVisited(int weight,int *visited,int vlen);
void Decode(HfmTree T,List L);
void PrintHc(List L,char *str);

int main()
{
	char str[MAX_STRSIZE];
	List L = GetFrequency(str);PrintFrequency(L);
	HfmTree T = CreateHuffmanTree(L);
	GetHC(T,&L);
	PrintHc(L,str);
	char order;
	do
	{
		Decode(T,L);
		printf("\n�Ƿ�Ҫ�������룿(y/n)");
		order = getchar();
		fflush(stdin);
	}while(order=='y'||order=='Y');
	return 0;
}

/*��������*/
List GetFrequency(char *str)
{
	List L;L.Len=0;
	printf("������Ҫ���й�����������ַ�����");
	gets(str);
	int i,j = 0,Len = strlen(str),ascii[128]={0},ascii_code;
	/*ͳ�Ƴ��ֵ��ַ���Ƶ��*/
	for(i=0;i<Len;i++)
	{
		ascii_code = (int) str[i];
		ascii[ascii_code]++;
	}
	/*���L�ĳ���*/
	for(i=0;i<128;i++)
	{
		if(ascii[i]!=0)
			L.Len++;
	}
	L.HCList = (HC*)malloc(L.Len*sizeof(HC));
	for(i=0;i<L.Len;i++)
	{
		while(ascii[j]==0) j++;//��λ����0��ascii��
		L.HCList[i].fequency = ascii[j];L.HCList[i].character = (char) j;
		j++;
	}
	return L;
}
void PrintFrequency(List L)
{	/*������ ���� ���� �ȩ� �� ��*/
	int i;
	printf("\n�������������������Щ�����������������\n");printf("��  �ַ�  ��  Ƶ��  ��\n");
	for(i=0;i<L.Len;i++)
	{
		printf("�������������������੤����������������\n");
		printf("��   %c    ��   %02d   ��\n",L.HCList[i].character,L.HCList[i].fequency);
	}
	printf("�������������������ة�����������������\n");
}
HfmTree CreateHuffmanTree(List L)
{
	HfmTree T;Node *minNode1,*minNode2,*root;int i;
	Leaves LeafList = (Leaves)malloc(sizeof(leaf));leaf *p = LeafList,*q;
	/*��ʼ��Ҷ�ӽ����б�*/
	for(i=0;i<L.Len;i++)
	{
		q = (Leaves)malloc(sizeof(leaf));
		q->node = (Node*)malloc(sizeof(Node));
		q->node->weight = L.HCList[i].fequency;
		q->node->lchild = NULL;q->node->rchild = NULL;
		p->next = q;
		p = q;
	}
	p->next = NULL;
	/*��ʼ������������*/
	if(LeafList->next == NULL)
		return NULL;
	while(LeafList->next->next!=NULL)
	{
		minNode1 = GetMinLeaf(&LeafList);
		minNode2 = GetMinLeaf(&LeafList);
		root = (Node*)malloc(sizeof(Node));
		root->weight = minNode1->weight+minNode2->weight;
		if(minNode1->weight<=minNode2->weight)
		{
			root->lchild = minNode1;
			root->rchild = minNode2;
		}else
		{
			root->lchild = minNode2;
			root->rchild = minNode1;
		}
		root->flag = 0;
		minNode1->parent = root;minNode2->parent = root;
		InsertNewLeaf(&LeafList,root);
	}
	/*���һ��������root*/
	T = (HfmTree)malloc(sizeof(Node));
	T->lchild = LeafList->next->node->lchild;
	T->rchild = LeafList->next->node->rchild;
	T->parent = NULL;
	T->weight = LeafList->next->node->weight;
	T->flag = 0;
	/*���Ҷ���б�*/
	ClearLeaves(&LeafList);
	return T;
}
Node *GetMinLeaf(Leaves *LeafList_ptr)
{
	Leaves p = (*LeafList_ptr)->next;leaf *q,*minNode=p,*pre_minNode;
	int minweight = p->node->weight;
	p = p->next;
	while(p!=NULL)
	{
		if(p->node->weight<minweight)
		{
			minNode = p;minweight = p->node->weight;
		}
		p = p->next;
	}
	pre_minNode = GetPreNode(*LeafList_ptr,minNode);
	pre_minNode->next = minNode->next;
	Node *HfmNode = (Node*)malloc(sizeof(Node));
	HfmNode->lchild = minNode->node->lchild;
	HfmNode->rchild = minNode->node->rchild;
	HfmNode->weight = minNode->node->weight;
	HfmNode->flag = 0;
	free(minNode);
	return HfmNode;
}
leaf *GetPreNode(Leaves LeafList,leaf *p)
{
	leaf *pre_p = LeafList;
	while(pre_p->next!=p)
		pre_p = pre_p->next;
	return pre_p;
}
void InsertNewLeaf(Leaves *LeafList_ptr,Node *root)
{
	leaf *p = (*LeafList_ptr),*new_node;
	new_node = (leaf*)malloc(sizeof(leaf));
	new_node->node = root;
	new_node->next = p->next;
	p->next = new_node;
}
void ClearLeaves(Leaves *LeafList_ptr)
{
	leaf *p = (*LeafList_ptr),*q;
	while(p!=NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
}
void GetHC(HfmTree T,ListPtr L_ptr)
{
	Node *p = T;
	Stack s[100];int top = -1,strlen=0;
	int visited[MAX_STRSIZE] = {0},vlen=0;	//��¼�Ѿ������ʹ���Ҷ�ӽ��
	int i,weight;
	if(T->lchild==NULL&&T->lchild==NULL){
		strcpy(L_ptr->HCList[i].code,"0");return;
	}
	for(i=0;i<L_ptr->Len;i++)
	{
		p = T;top = -1;strlen=0;
		strcpy(L_ptr->HCList[i].code,"\0");
		weight = L_ptr->HCList[i].fequency;
		while(1)
		{
			if(p->lchild==NULL&&p->rchild==NULL){
				if(p->weight==weight&&p->flag==0){
					if(!InVisited(weight,visited,vlen))
						visited[vlen++] = weight;
					p->flag = 1;
					break;
				}else{
					if(s[top].flag==0){	
						p = s[top].node->rchild;
						L_ptr->HCList[i].code[strlen-1] = '\0';
						strcat(L_ptr->HCList[i].code,"1");
						s[top].flag=1;
					}else
					{
						L_ptr->HCList[i].code[--strlen] = '\0';
						while(s[top].flag==1)
						{
							L_ptr->HCList[i].code[--strlen] = '\0';
							top--;
						}
						p = s[top].node->rchild;
						s[top].flag = 1;
						strcat(L_ptr->HCList[i].code,"1");
						strlen++;
					}
				}
			}else{
				s[++top].node = p;
				s[top].flag = 0;
				strcat(L_ptr->HCList[i].code,"0");
				strlen++;
				p = p->lchild;
			}
		}
	}
	
	printf("\n�������������������Щ�����������������������������\n");printf("��  �ַ�  ��  ����������  ��\n");
	for(i=0;i<L_ptr->Len;i++)
	{
		printf("�������������������੤����������������������������\n");
		printf("��   %c    ��   %-8s   ��\n",L_ptr->HCList[i].character,L_ptr->HCList[i].code);
	}
	printf("�������������������ة�����������������������������\n");
}

int InVisited(int weight,int *visited,int vlen)
{
	int i;
	for(i=0;i<vlen;i++)
	{
		if(visited[i]==weight)
			return 1;
	}
	return 0;
}
void Decode(HfmTree T,List L)
{
	char str[MAX_STRSIZE],result[MAX_STRSIZE] = {'\0'},path[MAX_STRSIZE]={'\0'};int i=0,j=0;
	Node *p = T;
	printf("\n���������������:");
	gets(str);
	while(i<=strlen(str))
	{
		if(p->lchild==NULL&&p->rchild==NULL){
			j=0;
			while(strcmp(path,L.HCList[j].code)!=0)
				j++;
			result[strlen(result)] = L.HCList[j].character;
			strcpy(path,"\0");
			p = T;
		}else
		{
			if(str[i]=='0'){
				strcat(path,"0");
				p = p->lchild;
			}else if(str[i]=='1'){
				strcat(path,"1");
				p = p->rchild;
			}else if(str[i]=='\0'){
				break;
			}else{
				printf("\n��������ֻ�ܰ���1��0��\n");
				return;
			}
			i++;
		}
	}
	if(strcmp(path,"\0")==0) printf("ȫ��ƥ�䣡%s������Ϊ:%s\n",str,result);
	else printf("���벻�ɹ�,ֻ�в���ƥ�䣡%s�Ĳ���ƥ����Ϊ��%s\n",str,result);
}

void PrintHc(List L,char *str)
{
	int i,j;
	printf("\n���ַ����Ĺ���������Ϊ��");
	for(i=0;i<strlen(str);i++)
		for(j=0;j<L.Len;j++)
			if(str[i]==L.HCList[j].character)
				printf("%s",L.HCList[j].code);
}