/*计算机2003 201205130 杨帆 第一题数组版*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NameLen_Max 30		//字符串最大长度 
#define ArrayLen_Max 10000	//学生数组最大长度 
#define LEN sizeof(Student)	//结构体字节数

/*typedef*/
typedef double Score;		//分数 
typedef int Number; 		


/*结构体Student*/
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
}Student;
/*全局变量*/
int len = 0;						//学生数 
Student Stu[ArrayLen_Max];			//信息表 


/*函数声明*/
void Create();			//将文件数据读入结构体数组 
void Print_Panel();		//打印功能面板
void Print_Rank();		//打印信息表 ,有排名，并将信息表内容写入txt
void Print_Norank();	//打印信息表，无排名 ， 并将信息表内容写入txt
void Search(); 			//用学号查找
void Insert();			//插入学生，并输出信息
void Sort_Num();		//按学号排序，升序 
void Sort_Sum();		//按总分排序，降序 
void Sum_Ave();			//计算总分和平均分
void Ave_Class();		//计算每门课的平均分 
void Delete();			//删除学生，并输出信息 

int main()
{
	Create();
	char order;
	/*操作*/ 
	do{
		Print_Panel();
		order = getchar();
		switch(order){
			case '1': 	Sum_Ave();Search();break;
			case '2': 	Insert();Sum_Ave();Print_Norank();break;
			case '3':	Delete();break;
			case '4':	Sum_Ave();Print_Rank();break;
			case '5':	Ave_Class();break;
			case '6':	Sort_Sum();Print_Rank();break;
			default:	return 0;
		}
		getchar();	//接受\n符 
	}while(1); 
	return 0;
}

/*将文件数据读入结构体数组*/
void Create()
{
	int i = 0;
	FILE *fp1;
	//打开文件，读入数据 
	fp1 = fopen("e:\\homework\\data.txt","r");		//输入文件路径 ,r为只读
	do{
		fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&Stu[i].num,Stu[i].name,&Stu[i].math,&Stu[i].chinese,&Stu[i].english,&Stu[i].polity,&Stu[i].cs);
		Stu[i].sum = Stu[i].math + Stu[i].chinese+Stu[i].english+Stu[i].polity+Stu[i].cs;
		Stu[i].ave = Stu[i].sum/5;
		i++;
	}while(Stu[i-1].num!=0);
	len = i-1;		//记录学生个数，循环后最后一个是0，新同学从Stu[4]开始插入 
	fclose(fp1);
}

/*打印功能面板 */
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

/*打印信息表,没有排名*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void Print_Norank()
{
	int i=0;		//rank为排名
	FILE *fp;
	fp=fopen("e:\\result.txt","w"); 
	printf("\n此表中共有%d个记录:\n",len);
	printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
	do
	{
		fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
		printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");       	
    	printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
    	i++;
	}while(Stu[i].num!=0);
	printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	fclose(fp);
}

/*打印信息表，有排名*/
/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void Print_Rank()
{
	int rank=1,i=0;		//rank为排名
	FILE *fp;
	fp=fopen("e:\\result.txt","w"); 
	printf("\n此表中共有%d个记录:\n",len);
	printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
	do
	{
		fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
		printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");       	
    	printf("│%-8d│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",rank,Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
    	i++;
    	rank++;
	}while(Stu[i].num!=0);
	printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	fclose(fp);
}

/*用学号查找*/
void Search()
{
	int number,i;
	printf("	请输入你想查找的学生的学号:   ");
	scanf("%d",&number);
	for(i=0;i<len;i++)
	{
		if(Stu[i].num == number)
		{
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			return;
		}else
			continue;
	}
	printf("\t未找到该学生！\n\n");
}

/*插入学生，并输出信息*/
void Insert()
{
	if(len>=ArrayLen_Max){
		
	}else
	{
		
	}
	Student stu1;
	printf("\t请输入学生的信息，格式为学号,姓名,数学,语文,英语,政治,计算机（英文逗号）：");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&Stu[len].num,Stu[len].name,&Stu[len].math,&Stu[len].chinese,&Stu[len].english,&Stu[len].polity,&Stu[len].cs,&Stu[len].sum,&Stu[len].ave);
	Stu[len+1].num = 0;
	len++;
	Sort_Num();
}

/*按学号排序*/ 
void Sort_Num()
{
	Student stu1;
	int i,j=0;
	for(j=0;j<len-1;j++)
	{
		for(i=0;i<len-1-j;i++)
		{
			if(Stu[i].num > Stu[i+1].num)
			{
				stu1 = Stu[i];
				Stu[i] = Stu[i+1];
				Stu[i+1] = stu1;
			}
		}
	}
}

/*按总分排序,降序*/
void Sort_Sum()
{
	Student stu1;
	int i,j=0;
	for(j=0;j<len-1;j++)
	{
		for(i=0;i<len-1-j;i++)
		{
			if(Stu[i].sum <Stu[i+1].sum)
			{
				stu1 = Stu[i];
				Stu[i] = Stu[i+1];
				Stu[i+1] = stu1;
			}
		}
	}
}

/*计算总方和平均分*/
void Sum_Ave()
{
	int i=0;
	for(i=0;i<len;i++)
	{
		Stu[i].sum =  Stu[i].chinese+Stu[i].math+Stu[i].english+Stu[i].polity+Stu[i].cs;
		Stu[i].ave = Stu[i].sum/5;
	}
}

/*计算每门课的平均分*/ 
void Ave_Class()
{
	int i;
	double len1;
	len1 = (double)len;
	double Math=0,Chinese=0,English=0,Polity=0,Cs=0;
	for(i=0;i<len;i++)
	{
		Math +=Stu[i].math;
		Chinese += Stu[i].chinese;
		English += Stu[i].english;
		Polity += Stu[i].polity;
		Cs += Stu[i].cs;
	}
	printf("\n\t\t数学平均分：\t%3.1lf\n\t\t语文平均分：\t%3.1lf\n\t\t英语平均分：\t%3.1lf\n\t\t政治平均分：\t%3.1lf\n\t\t计算机平均分：\t%3.1lf\n\n",Math/len1,Chinese/len1,English/len1,Polity/len1,Cs/len1); 
}

/*删除学生，并输出信息*/
void Delete()
{
	int i,j=0;
	char de_name[NameLen_Max+1];
	printf("	请输入要删除学生的姓名：");
	scanf("%s",&de_name);
	for(i=0;i<len;i++)
	{
		if(strcmp(Stu[i].name,de_name)==0)
		{
			printf("┌────────┬────────┬────────────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
			printf("│排名    │学号    │  名      字    │数学    │语文    │英语    │政治    │计算机  │总分    │平均分  │\n");
			printf("├────────┼────────┼────────────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
			printf("│%-8c│%-8d│%-16s│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│%-8.1f│\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
			printf("└────────┴────────┴────────────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
			for(j=i;j<=len;j++)
			{
				Stu[j] = Stu[j+1];
			}
		}
	}
	len--;
	printf("\t没找到该学生！\n\n");
} 
