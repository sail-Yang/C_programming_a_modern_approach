/*�����2003 201205130 � ��һ��˫�����*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h> 
#define NameLen_Max 30		//�ַ�����󳤶� 
#define LEN sizeof(Student)	//�ṹ���ֽ��� 

/*�ṹ���Լ�typedef����*/
typedef double Score;		//���� 
typedef int Number;

/*Student�������*/
typedef struct student
{
	Number num;
	char name[NameLen_Max+1];
	Score math;
	Score chinese;
	Score english;
	Score polity;
	Score cs;
	Score sum;
	Score ave;
	struct student *Prior;
	struct student *Next;
}Student;

typedef Student *LinkList;
typedef Student *Stu;
/*��������*/
LinkList Create();					//�������ݣ�������Ϣ��
void Print_Panel();					//��ӡ������� 
void Print_No_Rank(LinkList L);		//��ӡ��Ϣ�������� 
void Print_Rank(LinkList L);		//��ӡ��Ϣ�������� 
int Get_Len(LinkList L);			//��ȡѧ���������������� 
void Search(LinkList L); 			//��ѧ�Ų���
void Insert(LinkList L);			//ͷ�巨 
void Sort_Num(LinkList L);			//����ѧ�ţ����� ��ð������ 
void Sort_Sum(LinkList L);			//�����ܷ֣�����ð������ 
void Delete(LinkList L);			//ɾ��ָ��ѧ�ŵ�ѧ�� 
void Ave_Class(LinkList L);			//���ƽ���� 

/*-----------������-----------*/
int main()
{
	LinkList L;
	char order;
	/*������Ϣ��*/ 
	L = Create();
	/*����*/ 
	do{
		Print_Panel();
		order = getchar();
		
		switch(order){
			case '1': 	Search(L);break;
			case '2': 	Insert(L);Sort_Num(L);Print_No_Rank(L);break;
			case '3':	Delete(L);break;
			case '4':	Print_No_Rank(L);break;
			case '5':	Ave_Class(L);break;
			case '6':	Sort_Sum(L);Print_Rank(L);break;
			default:	printf("\n�����˳�\n");return 0;
		}
		system("pause");
		system("cls");
		fflush(stdin);
		
	}while(1); 
	return 0;
}
/*-----------END-----------*/

/*��������*/
/*�������ݣ�txt�ļ���ʽ:ѧ��,����,��ѧ�����ģ�Ӣ�����*/
LinkList Create()
{
	LinkList L;
	L = (LinkList)malloc(LEN);
	Stu p1,p2;
	FILE *fp1;
	L->Prior = NULL;
	int n = 0 ;
	//���ļ����������� 
	fp1 = fopen("data.txt","r");		//�����ļ�·�� ,rΪֻ�� 
	p1 = (Stu)malloc(LEN);
	fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p1->num,p1->name,&p1->math,&p1->chinese,&p1->english,&p1->polity,&p1->cs);
	p1->sum = p1->math+p1->chinese+p1->english+p1->polity+p1->cs;
	p1->ave = p1->sum/5;
	L->Next = p1;
	p1->Prior = L;
	p1->Next = NULL;
	
	do
	{
		p2 = (Stu)malloc(LEN);
		fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p2->num,p2->name,&p2->math,&p2->chinese,&p2->english,&p2->polity,&p2->cs);
		if(p2->num != 0)
		{
			p2->sum = p2->math+p2->chinese+p2->english+p2->polity+p2->cs;
			p2->ave = p2->sum/5;
			p2->Next = NULL;
			p2->Prior = p1;
			p1->Next = p2;
			p1 = p2;
		}else
		{
			break;
		}
	}while(1);
	free(p2);
	p2 = NULL;
    fclose(fp1);
    return L;
}

/*��ӡ�������*/
void Print_Panel()
{
	printf("\t1.��ѯ��Ϣ\n"
  		   "\t2.������ѧ��\n"
  		   "\t3.ɾ��ѧ��\n"
  	       "\t4.���ÿ��ѧ�����ֺܷ�ƽ����\n"
  	       "\t5.ÿ�ſε�ƽ����\n"
  	       "\t6.���ܷ��������\n"
  	       "\t7.�˳�ϵͳ\n"
  	       "\t�����빦��ѡ��(1..7)  ");
}

/*��ӡ��Ϣ��������*/
/*������ ���� ���� �ȩ� �� ��*/
void Print_No_Rank(LinkList L)
{
	int len=0;
	Stu p = L->Next;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(L);
  	printf("\n�˱��й���%d����¼:\n",len);
  	
  	if (p!=NULL){	
		printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
		printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");       	
       		printf("��        ��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       	}while (p!=NULL);
    	printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");  
  	}
  	fclose(fp);
}

void Print_Rank(LinkList L)
{
	int len=0,rank=1;		//rankΪ���� 
	Stu p = L->Next;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(L);
  	printf("\n�˱��й���%d����¼:\n",len);
  	
  	if (p!=NULL){	
		printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
		printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");       	
       		printf("��%-8d��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",rank,p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       		rank++;
       	}while (p!=NULL);
    	printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");  
  	}
  	fclose(fp);
}

/*��ȡѧ������*/
int Get_Len(LinkList L)
{
	int len = 0;
	Stu p = L->Next;
	while(p != NULL){
		p = p->Next;
		len++;
	}
	return len;
}

/*��ѧ�Ų���*/
void Search(LinkList L)
{
	Stu p;
	int rank=1,number;
	printf("\t������������ҵ�ѧ����ѧ��:   ");
	scanf("%d",&number);
	p = L->Next;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��        ��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\tû�ҵ���ѧ����\n\n");
}

/*ͷ�巨,����һ����ѧ������Ϣ��Ȼ��ѧ��˳�����*/
void Insert(LinkList L)
{
	Stu p,new_p;
	int i=0;
	p = L->Next;
	/*�����½��*/
	new_p = (Stu)malloc(LEN);
	if(new_p == NULL)
	{
		printf("Segment Fault\n");
		exit(0);
	}
	printf("\t������ѧ������Ϣ����ʽΪѧ��,����,��ѧ,����,Ӣ��,����,�������Ӣ�Ķ��ţ���");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&new_p->num,new_p->name,&new_p->math,&new_p->chinese,&new_p->english,&new_p->polity,&new_p->cs);
	new_p->sum = new_p->math+new_p->chinese+new_p->english+new_p->polity+new_p->cs;
	new_p->ave = new_p->sum/5;
	/*����*/
	L->Next = new_p;
	new_p->Prior = L;
	new_p->Next = p;
	p->Prior = new_p;
 }
 
/*����ѧ��*/
void Sort_Num(LinkList L)
{
	Stu p,p_next,prior_p;
	p = L->Next;
	int i,j,len;
	len = Get_Len(L);
	for(i=0;i<len-1;i++)
	{
		j = len - i -1;
		while(p->Next!=NULL && j!=0)
		{
			j--;
			p_next = p->Next;
			prior_p = p->Prior;
			if(p->num > p_next->num)
			{
				prior_p->Next = p_next;
				p_next->Prior = prior_p;
				p->Next = p_next->Next;
				p->Prior = p_next;
				if(p_next->Next != NULL)
				{
					p_next->Next->Prior = p;
				}
				p_next->Next = p;
				
			}else
			{
				p=p_next;
			}
		}
		p = L->Next;
	}
	
}

/*�����ܷ�*/
void Sort_Sum(LinkList L)
{
	Stu p,p_next,prior_p;
	p = L->Next;
	int i,j,len;
	len = Get_Len(L);
	for(i=0;i<len-1;i++)
	{
		j = len - i -1;
		while(p->Next!=NULL && j!=0)
		{
			j--;
			p_next = p->Next;
			prior_p = p->Prior;
			if(p->sum < p_next->sum)
			{
				prior_p->Next = p_next;
				p_next->Prior = prior_p;
				p->Next = p_next->Next;
				p->Prior = p_next;
				if(p_next->Next != NULL)
				{
					p_next->Next->Prior = p;
				}
				p_next->Next = p;
				
			}else
			{
				p=p_next;
			}
		}
		p = L->Next;
	}
	
}

/*ɾ��ָ��λ�õ�ѧ��*/
void Delete(LinkList L)
{
	Stu p;
	int rank=1,number;
	printf("\t����������ɾ����ѧ����ѧ��:   ");
	scanf("%d",&number);
	p = L->Next;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			p->Prior->Next = p->Next;
			p->Next->Prior = p->Prior;
			free(p);
			p = NULL; 
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\tû�ҵ���ѧ����\n\n");
}

/*��ȡÿ�ſγ̵�ƽ����*/
/*������ ���� ���� �ȩ� �� ��*/
void Ave_Class(LinkList L)
{
	int len;
	len = Get_Len(L);
	len = (double)len;
	Stu p;
	p = L->Next;
	double Math=0,Chinese=0,English=0,Polity=0,Cs=0;
	while(p!=NULL)
	{
		Math += p->math;
		Chinese += p->chinese;
		English += p->english;
		Polity += p->polity;
		Cs += p->cs;
		p = p->Next;
	}
	printf("\n\t\t   ����ƽ���ֱ�\n");
	printf("\t�������������������������������Щ�����������������������������\n");
	printf("\t��      ��Ŀ    ��     ƽ����   ��\n"); 
	printf("\t�������������������������������੤����������������������������\n"); 
	printf("\t��      ��ѧ    ��      %3.1lf    ��\n",Math/len); 
	printf("\t�������������������������������੤����������������������������\n");
	printf("\t��      ����    ��      %3.1lf    ��\n",Chinese/len); 
	printf("\t�������������������������������੤����������������������������\n");
	printf("\t��      Ӣ��    ��      %3.1lf    ��\n",English/len); 
	printf("\t�������������������������������੤����������������������������\n");
	printf("\t��      ����    ��      %3.1lf    ��\n",Polity/len); 
	printf("\t�������������������������������੤����������������������������\n");
	printf("\t��     �����   ��      %3.1lf    ��\n",Cs/len); 
	printf("\t�������������������������������ة�����������������������������\n\n");
}


