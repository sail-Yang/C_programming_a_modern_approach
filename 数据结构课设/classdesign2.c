#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STRSIZE 200
#define MAX_CODESIZE 100
/*结构体声明*/
typedef struct Node
{
	struct Node *parent,*lchild,*rchild;
	int weight;
	int flag;
}Node,*HfmTree;

typedef struct HC
{
	char character;		//字符
	int fequency;		//字符的频度
	char code[MAX_CODESIZE];//该字符对应的哈夫曼编码
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


/*函数声明*/
List GetFrequency(char *str);								//获取输入字符串的各字符频度
void PrintFrequency(List L);						//打印各字符的频度
HfmTree CreateHuffmanTree(List L);					//构造哈夫曼树
Node *GetMinLeaf(Leaves *LeafList_ptr);				//获取最小权值的叶子，并且从叶子列表中删除此节点
void InsertNewLeaf(Leaves *LeafList_ptr,Node *root);//往叶子列表中插入新的叶子节点，权值为最小两个的和
void ClearLeaves(Leaves *LeafList_ptr);				//释放叶子列表
leaf *GetPreNode(Leaves LeafList,leaf *p);	//获取叶子列表中一个结点的前一个结点
void GetHC(HfmTree T,ListPtr L_ptr);		//获取Hfm编码(HC)
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
		printf("\n是否要继续译码？(y/n)");
		order = getchar();
		fflush(stdin);
	}while(order=='y'||order=='Y');
	return 0;
}

/*函数定义*/
List GetFrequency(char *str)
{
	List L;L.Len=0;
	printf("请输入要进行哈夫曼编码的字符串：");
	gets(str);
	int i,j = 0,Len = strlen(str),ascii[128]={0},ascii_code;
	/*统计出现的字符的频度*/
	for(i=0;i<Len;i++)
	{
		ascii_code = (int) str[i];
		ascii[ascii_code]++;
	}
	/*获得L的长度*/
	for(i=0;i<128;i++)
	{
		if(ascii[i]!=0)
			L.Len++;
	}
	L.HCList = (HC*)malloc(L.Len*sizeof(HC));
	for(i=0;i<L.Len;i++)
	{
		while(ascii[j]==0) j++;//定位不是0的ascii码
		L.HCList[i].fequency = ascii[j];L.HCList[i].character = (char) j;
		j++;
	}
	return L;
}
void PrintFrequency(List L)
{	/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
	int i;
	printf("\n┌────────┬────────┐\n");printf("│  字符  │  频度  │\n");
	for(i=0;i<L.Len;i++)
	{
		printf("├────────┼────────┤\n");
		printf("│   %c    │   %02d   │\n",L.HCList[i].character,L.HCList[i].fequency);
	}
	printf("└────────┴────────┘\n");
}
HfmTree CreateHuffmanTree(List L)
{
	HfmTree T;Node *minNode1,*minNode2,*root;int i;
	Leaves LeafList = (Leaves)malloc(sizeof(leaf));leaf *p = LeafList,*q;
	/*初始化叶子结点的列表*/
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
	/*开始构建哈夫曼树*/
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
	/*最后一个结点就是root*/
	T = (HfmTree)malloc(sizeof(Node));
	T->lchild = LeafList->next->node->lchild;
	T->rchild = LeafList->next->node->rchild;
	T->parent = NULL;
	T->weight = LeafList->next->node->weight;
	T->flag = 0;
	/*清空叶子列表*/
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
	int visited[MAX_STRSIZE] = {0},vlen=0;	//记录已经被访问过的叶子结点
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
	
	printf("\n┌────────┬──────────────┐\n");printf("│  字符  │  哈夫曼编码  │\n");
	for(i=0;i<L_ptr->Len;i++)
	{
		printf("├────────┼──────────────┤\n");
		printf("│   %c    │   %-8s   │\n",L_ptr->HCList[i].character,L_ptr->HCList[i].code);
	}
	printf("└────────┴──────────────┘\n");
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
	printf("\n请输入哈夫曼编码:");
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
				printf("\n输入数据只能包含1和0！\n");
				return;
			}
			i++;
		}
	}
	if(strcmp(path,"\0")==0) printf("全部匹配！%s的译码为:%s\n",str,result);
	else printf("译码不成功,只有部分匹配！%s的部分匹配结果为：%s\n",str,result);
}

void PrintHc(List L,char *str)
{
	int i,j;
	printf("\n此字符串的哈夫曼编码为：");
	for(i=0;i<strlen(str);i++)
		for(j=0;j<L.Len;j++)
			if(str[i]==L.HCList[j].character)
				printf("%s",L.HCList[j].code);
}