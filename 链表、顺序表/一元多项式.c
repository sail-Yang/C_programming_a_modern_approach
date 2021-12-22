/*计算机2003 杨帆 201205130 用单链表实现一元多项式加减乘法*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#define NameLen_Max 30		//字符串最大长度 
#define LEN sizeof(Polynomial)	//结构体字节数 

typedef int ElemType;

typedef struct polynomial
{
	ElemType ratio;		//系数 
	ElemType power;		//幂
	struct polynomial *next; 
}Polynomial;

typedef Polynomial *Poly;
typedef Polynomial *Item;


/*函数声明*/
Poly Create(int n);					//随机生成指定长度的一元多项式
void Print(Poly poly);				//打印多项式
void Print_Panel();					//打印面板 
int Get_Len(Poly poly);				//获取多项式长度 
void Sort(Poly poly);				//按照幂次升序排序 
void Merge_Poly(Poly poly);			//合并多项式中同幂次项
Item Get_Pre(Poly poly,Item item);	//获取该项前面一项	
Poly Add(Poly poly1,Poly poly2);	//poly2加poly1，将结果输出，不改变原来数据 
Poly Sub(Poly poly1,Poly poly2);	//poly2-poly1,将结果输出，不改变原来数据
Poly Multiply(Poly poly1,Poly poly2);//poly2*poly1,将结果输出，不改变原来数据
void Clear_Poly(Poly poly);			//销毁多项式
 
/*-----------主函数-----------*/
int main()
{
	Poly poly1,poly2,poly3;
	poly1 = Create(15);
	poly2 = Create(15);
	srand((unsigned int)time(NULL));
	char order;
	printf("\t此程序主要生成两个多项式（随机生成），然后可以对这两个多项式进行加、减、乘三种运算操作：\n\n\n");
	for(;;)
	{
		Print_Panel(); 
		order = getchar();
		
		switch(order)
		{
			case '1': Print(poly1);Print(poly2);break;
			case '2': poly3 = Add(poly1,poly2);Print(poly3);break;
			case '3': poly3 = Sub(poly1,poly2);Print(poly3);break;
			case '4': poly3 = Multiply(poly1,poly2);Print(poly3);break;
			default: return 0;break;
		}
		system("pause");
		system("cls");
		getchar();
	}
	return 0;
}
/*-----------END-----------*/

/*函数定义*/

/*创造一个多项式*/
Poly Create(int n)
{
	if(n<=0)
	{
		printf("Input too small!!!\n");
		return;
	}else
	{
		Poly poly;
		poly = (Poly)malloc(LEN);
		poly->next = NULL;
		Item item;
		int i=0;
		for(i=0;i<n;i++)
		{
			item = (Item)malloc(LEN);
			item->ratio = rand()%100-50;
			item->power = rand()%20-10; 
			item->next = poly->next;
			poly->next = item;
		}
		Sort(poly);
		Merge_Poly(poly);
		return poly; 
	}
}

/*获取多项式长度*/
int Get_Len(Poly poly)
{
	int len=0;
	Item item;
	item = poly->next;
	while(item!=NULL)
	{
		item = item->next;
		len++;
	}
	return len;
}


/*打印面板*/
void Print_Panel()
{
	printf(
		   "\t1、打印两个多项式\n"
		   "\t2、进行加法\n"
		   "\t3、进行减法\n"
		   "\t4、进行乘法\n"
		   "\t5、退出程序\n\n"
		   "请输入指令：");
 } 
/*打印多项式*/
void Print(Poly poly)
{
	int len,i;
	Item item;
	item = poly->next;
	len = Get_Len(poly);
	printf("此多项式共有%d项\n",len);
	printf("poly =");
	while(item!=NULL)
	{
		if(poly->next==item)
		{
			if(item->ratio>=0)
				printf(" %dx^%d",item->ratio,item->power);
			else
				printf(" - %dx^%d",-(item->ratio),item->power);
		}else
		{
			if(item->ratio>=0)
				printf(" + %dx^%d",item->ratio,item->power);
			else
				printf(" - %dx^%d",-(item->ratio),item->power);
		}
		
		item = item->next;
	}
	printf("\n\n");
	return;
}

/*获取输入结点的前一个结点*/
Item Get_Pre(Poly poly,Item item)
{
	Item item1;
	item1 = poly;
	while(item1->next!=item)
	{
		item1 = item1->next;
	}
	return item1;
}

/*用冒泡排序，按照幂次升序排序*/
void Sort(Poly poly)
{
	int i,j,len;
	len = Get_Len(poly);
	Item item_next,item,pre_item;
	item = poly->next;
	for(i=0;i<len-1;i++)
	{
		j = len-i-1;
		while(item->next!=NULL&&j!=0)
		{
			j--;
			item_next = item->next;
			if(item->power > item_next->power)
			{
				pre_item = Get_Pre(poly,item);
				pre_item->next = item_next;
				item->next = item_next->next;
				item_next->next = item; 
			}else
			{
				item = item_next;
			}
		}
		item = poly->next;
	}
	return;
}


/*合并多项式中同幂次项,一定要先排序*/
void Merge_Poly(Poly poly)
{
	Item item1,item2;
	item1 = poly->next;
	item2 = item1->next;
	while(item1->next!=NULL)
	{
		while(item2->power == item1->power)
		{
			item1->ratio = item1->ratio  + item2->ratio;
			item1->next = item2->next;
			free(item2);
			item2 = item1->next;
			if(item2==NULL)
				return; 
		}
		item1 = item2;
		item2 = item2->next;
	}
	return;
}

Poly Add(Poly poly1,Poly poly2)
{
	Poly poly3;
	Item item1,item2,item3,item;
	item1 = poly1->next;
	item2 = poly2->next;
	poly3 = (Poly)malloc(sizeof(LEN));
	poly3->next = NULL;
	
	for(;;)
	{
		if(item1==NULL&&item2==NULL)
			break;
		else
		{
			item3 = (Item)malloc(sizeof(LEN));
			if(item1==NULL||item2==NULL)
			{
				if(item1==NULL)
				{
					item3->power = item2->power;
					item3->ratio = item2->ratio;
					item2 = item2->next;
				}else
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio;
					item1 = item1->next;
				}
			}else
			{
				if(item1->power>item2->power)
				{
					item3->power = item2->power;
					item3->ratio = item2->ratio;
					item2 = item2->next;
				}else if(item1->power<item2->power)
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio;
					item1 = item1->next;
				}else
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio+item2->ratio;
					item1 = item1->next;
					item2 = item2->next;
				}
			}
			item = item3;
			item->next = poly3->next;
			poly3->next = item;
		}
	}
	
	Sort(poly3);
	Merge_Poly(poly3);
	return poly3;
}

Poly Sub(Poly poly1,Poly poly2)
{
	Poly poly3;
	Item item1,item2,item3,item;
	item1 = poly1->next;
	item2 = poly2->next;
	poly3 = (Poly)malloc(sizeof(LEN));
	poly3->next = NULL;
	
	for(;;)
	{
		if(item1==NULL&&item2==NULL)
			break;
		else
		{
			item3 = (Item)malloc(sizeof(LEN));
			if(item1==NULL||item2==NULL)
			{
				if(item1==NULL)
				{
					item3->power = item2->power;
					item3->ratio = item2->ratio;
					item2 = item2->next;
				}else
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio;
					item1 = item1->next;
				}
			}else
			{
				if(item1->power>item2->power)
				{
					item3->power = item2->power;
					item3->ratio = item2->ratio;
					item2 = item2->next;
				}else if(item1->power<item2->power)
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio;
					item1 = item1->next;
				}else/*item1->power = item2->power*/
				{
					item3->power = item1->power;
					item3->ratio = item1->ratio-item2->ratio;
					item1 = item1->next;
					item2 = item2->next;
				}
			}
			item = item3;
			item->next = poly3->next;
			poly3->next = item;
		}
	}
	
	Sort(poly3);
	Merge_Poly(poly3);
	return poly3;
}

/*poly2*poly1,将结果输出，不改变原来数据*/
Poly Multiply(Poly poly1,Poly poly2)
{
	Poly poly3;
	Item item1,item2,item3,item;
	item1 = poly1->next;
	item2 = poly2->next;
	poly3 = (Poly)malloc(sizeof(LEN));
	poly3->next = NULL;
	while(item1!=NULL)
	{
		while(item2!=NULL)
		{
			if(item1->ratio==0||item2->ratio==0)
			{
			}
			else
			{
				item3 = (Item)malloc(sizeof(LEN));
				item3->ratio = item1->ratio*item2->ratio;
				item3->power = item1->power+item2->power;
				item = item3;
				item->next = poly3->next;
				poly3->next = item;
			}
			item2 = item2->next;
		}
		item1 = item1->next;
	}
	Sort(poly3);
	Merge_Poly(poly3);
	return poly3;
}

/*销毁多项式*/
void Clear_Poly(Poly poly)
{
	Item item1,item2;
	item1 = poly->next;
	while(item1!=NULL)
	{
		item2 = item1->next;
		free(item1);
		item1 = NULL;
	}
	free(poly);
	poly=NULL;
	return;
 } 

