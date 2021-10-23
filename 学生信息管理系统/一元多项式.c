/*�����2003 � 201205130 �õ�����ʵ��һԪ����ʽ�Ӽ��˷�*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#define NameLen_Max 30		//�ַ�����󳤶� 
#define LEN sizeof(Polynomial)	//�ṹ���ֽ��� 

typedef int ElemType;

typedef struct polynomial
{
	ElemType ratio;		//ϵ�� 
	ElemType power;		//��
	struct polynomial *next; 
}Polynomial;

typedef Polynomial *Poly;
typedef Polynomial *Item;


/*��������*/
Poly Create(int n);					//�������ָ�����ȵ�һԪ����ʽ
void Print(Poly poly);				//��ӡ����ʽ
void Print_Panel();					//��ӡ��� 
int Get_Len(Poly poly);				//��ȡ����ʽ���� 
void Sort(Poly poly);				//�����ݴ��������� 
void Merge_Poly(Poly poly);			//�ϲ�����ʽ��ͬ�ݴ���
Item Get_Pre(Poly poly,Item item);	//��ȡ����ǰ��һ��	
Poly Add(Poly poly1,Poly poly2);	//poly2��poly1���������������ı�ԭ������ 
Poly Sub(Poly poly1,Poly poly2);	//poly2-poly1,�������������ı�ԭ������
Poly Multiply(Poly poly1,Poly poly2);//poly2*poly1,�������������ı�ԭ������
void Clear_Poly(Poly poly);			//���ٶ���ʽ
 
/*-----------������-----------*/
int main()
{
	Poly poly1,poly2,poly3;
	poly1 = Create(15);
	poly2 = Create(15);
	srand((unsigned int)time(NULL));
	char order;
	printf("\t�˳�����Ҫ������������ʽ��������ɣ���Ȼ����Զ�����������ʽ���мӡ��������������������\n\n\n");
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

/*��������*/

/*����һ������ʽ*/
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

/*��ȡ����ʽ����*/
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


/*��ӡ���*/
void Print_Panel()
{
	printf(
		   "\t1����ӡ��������ʽ\n"
		   "\t2�����мӷ�\n"
		   "\t3�����м���\n"
		   "\t4�����г˷�\n"
		   "\t5���˳�����\n\n"
		   "������ָ�");
 } 
/*��ӡ����ʽ*/
void Print(Poly poly)
{
	int len,i;
	Item item;
	item = poly->next;
	len = Get_Len(poly);
	printf("�˶���ʽ����%d��\n",len);
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

/*��ȡ�������ǰһ�����*/
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

/*��ð�����򣬰����ݴ���������*/
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


/*�ϲ�����ʽ��ͬ�ݴ���,һ��Ҫ������*/
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

/*poly2*poly1,�������������ı�ԭ������*/
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

/*���ٶ���ʽ*/
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

