/*计算机2003 201205130 杨帆 第一题双链表版*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h> 
#define NameLen_Max 30		//字符串最大长度 
#define LEN sizeof(Student)	//结构体字节数 

/*结构体以及typedef声明*/
typedef double Score;		//分数 
typedef int Number;

/*Student结点声明*/
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
/*函数声明*/
LinkList Create();					//读入数据，创建信息表
void Print_Panel();					//打印功能面板 
void Print_No_Rank(LinkList L);		//打印信息表，无排名 
void Print_Rank(LinkList L);		//打印信息表，有排名 
int Get_Len(LinkList L);			//获取学生数量，即链表长度 
void Search(LinkList L); 			//用学号查找
void Insert(LinkList L);			//头插法 
void Sort_Num(LinkList L);			//排序学号，升序 （冒泡排序） 
void Sort_Sum(LinkList L);			//排序总分，降序（冒泡排序） 
void Delete(LinkList L);			//删除指定学号的学生 
void Ave_Class(LinkList L);			//输出平均分 

/*-----------主函数-----------*/
int main()
{
	LinkList L;
	char order;
	/*生成信息表*/ 
	L = Create();
	/*操作*/ 
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
			default:	printf("\n程序退出\n");return 0;
		}
		system("pause");
		system("cls");
		fflush(stdin);
		
	}while(1); 
	return 0;
}
/*-----------END-----------*/

/*函数定义*/
/*读入数据，txt文件格式:学号,名字,数学，语文，英语，政治*/
LinkList Create()
{
	LinkList L;
	L = (LinkList)malloc(LEN);
	Stu p1,p2;
	FILE *fp1;
	L->Prior = NULL;
	int n = 0 ;
	//打开文件，读入数据 
	fp1 = fopen("data.txt","r");		//输入文件路径 ,r为只读 
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

/*打印功能面板*/
void Print_Panel()
{
	printf("\t1.查询信息\n"
  		   "\t2.插入新学生\n"
  		   "\t3.删除学生\n"
  	       "\t4.输出每个学生的总分和平均分\n"
  	       "\t5.每门课的平均分\n"
  	       "\t6.按总分排序输出\n"
  	       "\t7.退出系统\n"
  	       "\t请输入功能选项(1..7)  ");
}

/*打印信息表，无排名*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void Print_No_Rank(LinkList L)
{
	int len=0;
	Stu p = L->Next;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(L);
  	printf("\n此表中共有%d个记录:\n",len);
  	
  	if (p!=NULL){	
		printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
		printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");       	
       		printf("│        │%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       	}while (p!=NULL);
    	printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");  
  	}
  	fclose(fp);
}

void Print_Rank(LinkList L)
{
	int len=0,rank=1;		//rank为排名 
	Stu p = L->Next;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(L);
  	printf("\n此表中共有%d个记录:\n",len);
  	
  	if (p!=NULL){	
		printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
		printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");       	
       		printf("│%-8d│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",rank,p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       		rank++;
       	}while (p!=NULL);
    	printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");  
  	}
  	fclose(fp);
}

/*获取学生个数*/
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

/*用学号查找*/
void Search(LinkList L)
{
	Stu p;
	int rank=1,number;
	printf("\t请输入你想查找的学生的学号:   ");
	scanf("%d",&number);
	p = L->Next;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│        │%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\t没找到该学生！\n\n");
}

/*头插法,插入一个新学生的信息，然后按学号顺序输出*/
void Insert(LinkList L)
{
	Stu p,new_p;
	int i=0;
	p = L->Next;
	/*创建新结点*/
	new_p = (Stu)malloc(LEN);
	if(new_p == NULL)
	{
		printf("Segment Fault\n");
		exit(0);
	}
	printf("\t请输入学生的信息，格式为学号,姓名,数学,语文,英语,政治,计算机（英文逗号）：");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&new_p->num,new_p->name,&new_p->math,&new_p->chinese,&new_p->english,&new_p->polity,&new_p->cs);
	new_p->sum = new_p->math+new_p->chinese+new_p->english+new_p->polity+new_p->cs;
	new_p->ave = new_p->sum/5;
	/*插入*/
	L->Next = new_p;
	new_p->Prior = L;
	new_p->Next = p;
	p->Prior = new_p;
 }
 
/*排序学号*/
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

/*排序总分*/
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

/*删除指定位置的学生*/
void Delete(LinkList L)
{
	Stu p;
	int rank=1,number;
	printf("\t请输入你想删除的学生的学号:   ");
	scanf("%d",&number);
	p = L->Next;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			p->Prior->Next = p->Next;
			p->Next->Prior = p->Prior;
			free(p);
			p = NULL; 
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\t没找到该学生！\n\n");
}

/*获取每门课程的平均分*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
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
	printf("\n\t\t   各科平均分表\n");
	printf("\t┌──────────────┬──────────────┐\n");
	printf("\t│      科目    │     平均分   │\n"); 
	printf("\t├──────────────┼──────────────┤\n"); 
	printf("\t│      数学    │      %3.1lf    │\n",Math/len); 
	printf("\t├──────────────┼──────────────┤\n");
	printf("\t│      语文    │      %3.1lf    │\n",Chinese/len); 
	printf("\t├──────────────┼──────────────┤\n");
	printf("\t│      英语    │      %3.1lf    │\n",English/len); 
	printf("\t├──────────────┼──────────────┤\n");
	printf("\t│      政治    │      %3.1lf    │\n",Polity/len); 
	printf("\t├──────────────┼──────────────┤\n");
	printf("\t│     计算机   │      %3.1lf    │\n",Cs/len); 
	printf("\t└──────────────┴──────────────┘\n\n");
}


