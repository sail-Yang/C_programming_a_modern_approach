/*计算机2003 201205130 杨帆 第一题单链表版*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NameLen_Max 30		//字符串最大长度 
#define LEN sizeof(Student)	//结构体字节数 

/*typedef*/
typedef double Score;		//分数 
typedef int Number; 		

/*结点Student*/
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
	struct student *Next;
}Student;

/*函数声明*/
Student *Create();					//读入数据，创建信息表
void Print_Panel();					//打印功能面板 
void Print_Norank(Student *head);	//打印信息表(无排名) ,并将信息表内容写入txt
void Print_Rank(Student *head);		//打印信息表(有排名),并将信息表内容写入txt
void Search(Student *head); 		//用学号查找
Student *Insert(Student *head);		//插入学生，并输出信息
Student *Delete(Student *head);		//删除学生，并输出信息
void Ave_Class(Student *head);		//获取每门课程的平均分 
int Get_Len(Student *head);			//获取学生数量，即链表长度 
Student *Sort_Num(Student *head);	//按学号排序 ，升序 ，使用冒泡排序 
Student *Sort_Sum(Student *head);	//按总分排序，升序 ,使用冒泡排序 


/*-----------主函数-----------*/
int main()
{
	Student *head;
	char order;
	/*生成信息表*/ 
	head = Create();
	/*操作*/ 
	do{
		Print_Panel();
		order = getchar();
		switch(order){
			case '1': 	Search(head);break;
			case '2': 	head = Insert(head);Print_Norank(head);break;
			case '3':	head = Delete(head);break;
			case '4':	Print_Rank(head);break;
			case '5':	Ave_Class(head);break;
			case '6':	head = Sort_Sum(head);Print_Rank(head);break;
			default:	return 0;
		}
		getchar();	//接受\n符 
	}while(1); 
	return 0;
}
/*-----------END-----------*/


/*函数定义*/
/*读入数据，txt文件格式:学号,名字,数学，语文，英语，政治*/
Student *Create()
{
	Student *head;
	Student *p1,*p2;
	FILE *fp1;
	head = NULL;
	int n = 0 ;
	//打开文件，读入数据 
	fp1 = fopen("e:\\homework\\data.txt","r");		//输入文件路径 ,r为只读 
	p1 = (Student *)malloc(LEN);
	p2 = p1;
	fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p1->num,p1->name,&p1->math,&p1->chinese,&p1->english,&p1->polity,&p1->cs);
	/*计算总分和平均分*/ 
	p1->sum = p1->math+p1->chinese+p1->english+p1->polity+p1->cs;
	p1->ave = p1->sum/5;
	
	/*循环读入*/ 
	while (p1->num!=0)	//根据要求，数据源文件最后一行是0,0 
 	{  	
	 	n=n+1;
    	if (n==1)
    		head = p1;
    	else
    		p2->Next = p1;
    p2=p1;
    p1 = (Student *)malloc(LEN);
    fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p1->num,p1->name,&p1->math,&p1->chinese,&p1->english,&p1->polity,&p1->cs);
    p1->sum = p1->math+p1->chinese+p1->english+p1->polity+p1->cs;
	p1->ave = p1->sum/5;
	
	}
    p2->Next=NULL; 		//tail指向NULL 
    fclose(fp1);
    return head;
} 

/*打印功能面板*/
void Print_Panel()
{
	printf("        1.查询信息\n"
  		   "        2.插入新学生\n"
  		   "        3.删除学生\n"
  	       "        4.输出每个学生的总分和平均分\n"
  	       "        5.每门课的平均分\n"
  	       "        6.按总分排序输出\n"
  	       "        7.退出系统\n"
  	       "     	请输入功能选项(1..7)  ");
}

/*打印信息表，无排名*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void Print_Norank(Student *head)
{
	int len=0;		//rank为排名 
	Student *p = head;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(head);
  	printf("\n此表中共有%d个记录:\n",len);
  	
  	if (head!=NULL){	
		printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
		printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");       	
       		printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       	}while (p!=NULL);
    	printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");  
  	}
  	fclose(fp);
}

/*打印信息表,有排名*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void Print_Rank(Student *head)
{
	int rank=1,len=0;		//rank为排名 
	Student *p = head;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(head);
  	printf("\n此表中共有%d个记录:\n",len);
  	
  	if (head!=NULL){	
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

/*用学号查找 */
void Search(Student *head)
{
	Student *p;
	int rank=1,number;
	printf("	请输入你想查找的学生的学号:   ");
	scanf("%d",&number);
	p = head;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\t没找到该学生！\n\n");
}

/*输入一个新学生的信息，按学号顺序将该学生的信息插入后输出，这里使用头插法*/
Student *Insert(Student *head)
{
	Student *p1,*p2;
	p1 = head->Next;
	p2 = (Student *)malloc(LEN);
	p2->Next = p1;
	head->Next = p2;
	printf("\t请输入学生的信息，格式为学号,姓名,数学,语文,英语,政治,计算机（英文逗号）：");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p2->num,p2->name,&p2->math,&p2->chinese,&p2->english,&p2->polity,&p2->cs);
	p2->sum = p2->math+p2->chinese+p2->english+p2->polity+p2->cs;
	p2->ave = p2->sum/5;
	head = Sort_Num(head);
	return head;
}

/*获取学生个数*/
int Get_Len(Student *head)
{
	int len = 0;
	Student *p = head;
	while(p != NULL){
		p = p->Next;
		len++;
	}
	return len;
}

/*按学号排序 ，升序 */ 
Student *Sort_Num(Student *head)
{
	
	Student *p1,*p2;
	int len=0,j=0;
	len = Get_Len(head);
	int i;
	for(i=0;i<len-1;i++)
	{
		p1=p2=head; 
		j=len-i-1; 
		while(p1->Next!=NULL && j!=0){
			j--;
			if(p1->num > p1->Next->num){
				if(p1==head)
					head = p1->Next;
				else
					p2->Next = p1->Next;
				p2->Next = p1->Next;
				p2 = p2->Next;
				p1->Next = p2->Next;
				p2->Next = p1;
				p1=p2; 
			}
			p2=p1; 			
			p1=p1->Next; 	
		}
	}
	return head;
}


/*删除学生并删除信息*/
Student *Delete(Student *head)
{
	Student *p1,*p2,*pre_p1;
	char de_name[NameLen_Max+1];
	printf("	请输入要删除学生的姓名：");
	scanf("%s",&de_name); 
	pre_p1 = head;
	p1 = head->Next;
	while(p1!=NULL)
	{
		if(pre_p1 == head && strcmp(pre_p1->name,de_name)==0){
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',pre_p1->num,pre_p1->name,pre_p1->math,pre_p1->chinese,pre_p1->english,pre_p1->polity,pre_p1->cs,pre_p1->sum,pre_p1->ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			free(head);
			//free(pre_ptr1);
			head = p1;
			return head;
		}else if(strcmp(p1->name,de_name)==0)
		{
			p2 = p1->Next;
			pre_p1->Next = p2;
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8d│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",0,p1->num,p1->name,p1->math,p1->chinese,p1->english,p1->polity,p1->cs,p1->sum,p1->ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			free(p1);
			p1 = NULL;
			return head;
		}else{
			pre_p1 = p1;
			p1 = p1->Next;	
		}
	}
	printf("未查找到该学生！\n\n");
	return head;
}

/*获取每门课程的平均分*/
void Ave_Class(Student *head)
{
	int len;
	len = Get_Len(head);
	len = (double)len;
	Student *p;
	p = head;
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
	
	printf("\n\t\t数学平均分：\t%3.1lf\n\t\t语文平均分：\t%3.1lf\n\t\t英语平均分：\t%3.1lf\n\t\t政治平均分：\t%3.1lf\n\t\t计算机平均分：\t%3.1lf\n\n",Math/len,Chinese/len,English/len,Polity/len,Cs/len); 
	return; 
}

	
//链表实现冒泡排序
Student *Sort_Sum(Student *head){
    Student *p1,*p2;
	int len=0,j=0;
	len = Get_Len(head);
	int i;
	for(i=0;i<len-1;i++)
	{
		p1=p2=head; 
		j=len-i-1; 
		while(p1->Next!=NULL && j!=0){
			j--;
			if(p1->sum < p1->Next->sum){
				if(p1==head)
					head = p1->Next;
				else
					p2->Next = p1->Next;
				p2->Next = p1->Next;
				p2 = p2->Next;
				p1->Next = p2->Next;
				p2->Next = p1;
				p1=p2; 
			}
			p2=p1; 			
			p1=p1->Next; 	
		}
	}
	return head;
}


