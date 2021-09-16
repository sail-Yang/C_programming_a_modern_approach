/*�����2003 201205130 � ��һ�������*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NameLen_Max 30		//�ַ�����󳤶� 
#define ArrayLen_Max 10000	//ѧ��������󳤶� 
#define LEN sizeof(Student)	//�ṹ���ֽ���

/*typedef*/
typedef double Score;		//���� 
typedef int Number; 		


/*�ṹ��Student*/
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
/*ȫ�ֱ���*/
int len = 0;						//ѧ���� 
Student Stu[ArrayLen_Max];			//��Ϣ�� 


/*��������*/
void Create();			//���ļ����ݶ���ṹ������ 
void Print_Panel();		//��ӡ�������
void Print_Rank();		//��ӡ��Ϣ�� ,��������������Ϣ������д��txt
void Print_Norank();	//��ӡ��Ϣ�������� �� ������Ϣ������д��txt
void Search(); 			//��ѧ�Ų���
void Insert();			//����ѧ�����������Ϣ
void Sort_Num();		//��ѧ���������� 
void Sort_Sum();		//���ܷ����򣬽��� 
void Sum_Ave();			//�����ֺܷ�ƽ����
void Ave_Class();		//����ÿ�ſε�ƽ���� 
void Delete();			//ɾ��ѧ�����������Ϣ 

int main()
{
	Create();
	char order;
	/*����*/ 
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
		getchar();	//����\n�� 
	}while(1); 
	return 0;
}

/*���ļ����ݶ���ṹ������*/
void Create()
{
	int i = 0;
	FILE *fp1;
	//���ļ����������� 
	fp1 = fopen("e:\\homework\\data.txt","r");		//�����ļ�·�� ,rΪֻ��
	do{
		fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&Stu[i].num,Stu[i].name,&Stu[i].math,&Stu[i].chinese,&Stu[i].english,&Stu[i].polity,&Stu[i].cs);
		Stu[i].sum = Stu[i].math + Stu[i].chinese+Stu[i].english+Stu[i].polity+Stu[i].cs;
		Stu[i].ave = Stu[i].sum/5;
		i++;
	}while(Stu[i-1].num!=0);
	len = i-1;		//��¼ѧ��������ѭ�������һ����0����ͬѧ��Stu[4]��ʼ���� 
	fclose(fp1);
}

/*��ӡ������� */
void Print_Panel()
{
	printf("        1.��ѯ��Ϣ\n"
  		   "        2.������ѧ��\n"
  		   "        3.ɾ��ѧ��\n"
  	       "        4.���ÿ��ѧ�����ֺܷ�ƽ����\n"
  	       "        5.ÿ�ſε�ƽ����\n"
  	       "        6.���ܷ��������\n"
  	       "        7.�˳�ϵͳ\n"
  	       "     	�����빦��ѡ��(1..7)  ");
}

/*��ӡ��Ϣ��,û������*/
/*������ ���� ���� �ȩ� �� ��*/
void Print_Norank()
{
	int i=0;		//rankΪ����
	FILE *fp;
	fp=fopen("e:\\result.txt","w"); 
	printf("\n�˱��й���%d����¼:\n",len);
	printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
	printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
	do
	{
		fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
		printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");       	
    	printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
    	i++;
	}while(Stu[i].num!=0);
	printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
	fclose(fp);
}

/*��ӡ��Ϣ��������*/
/*������ ���� ���� �ȩ� �� ��*/
void Print_Rank()
{
	int rank=1,i=0;		//rankΪ����
	FILE *fp;
	fp=fopen("e:\\result.txt","w"); 
	printf("\n�˱��й���%d����¼:\n",len);
	printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
	printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
	do
	{
		fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
		printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");       	
    	printf("��%-8d��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",rank,Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
    	i++;
    	rank++;
	}while(Stu[i].num!=0);
	printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
	fclose(fp);
}

/*��ѧ�Ų���*/
void Search()
{
	int number,i;
	printf("	������������ҵ�ѧ����ѧ��:   ");
	scanf("%d",&number);
	for(i=0;i<len;i++)
	{
		if(Stu[i].num == number)
		{
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			return;
		}else
			continue;
	}
	printf("\tδ�ҵ���ѧ����\n\n");
}

/*����ѧ�����������Ϣ*/
void Insert()
{
	if(len>=ArrayLen_Max){
		
	}else
	{
		
	}
	Student stu1;
	printf("\t������ѧ������Ϣ����ʽΪѧ��,����,��ѧ,����,Ӣ��,����,�������Ӣ�Ķ��ţ���");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&Stu[len].num,Stu[len].name,&Stu[len].math,&Stu[len].chinese,&Stu[len].english,&Stu[len].polity,&Stu[len].cs,&Stu[len].sum,&Stu[len].ave);
	Stu[len+1].num = 0;
	len++;
	Sort_Num();
}

/*��ѧ������*/ 
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

/*���ܷ�����,����*/
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

/*�����ܷ���ƽ����*/
void Sum_Ave()
{
	int i=0;
	for(i=0;i<len;i++)
	{
		Stu[i].sum =  Stu[i].chinese+Stu[i].math+Stu[i].english+Stu[i].polity+Stu[i].cs;
		Stu[i].ave = Stu[i].sum/5;
	}
}

/*����ÿ�ſε�ƽ����*/ 
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
	printf("\n\t\t��ѧƽ���֣�\t%3.1lf\n\t\t����ƽ���֣�\t%3.1lf\n\t\tӢ��ƽ���֣�\t%3.1lf\n\t\t����ƽ���֣�\t%3.1lf\n\t\t�����ƽ���֣�\t%3.1lf\n\n",Math/len1,Chinese/len1,English/len1,Polity/len1,Cs/len1); 
}

/*ɾ��ѧ�����������Ϣ*/
void Delete()
{
	int i,j=0;
	char de_name[NameLen_Max+1];
	printf("	������Ҫɾ��ѧ����������");
	scanf("%s",&de_name);
	for(i=0;i<len;i++)
	{
		if(strcmp(Stu[i].name,de_name)==0)
		{
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',Stu[i].num,Stu[i].name,Stu[i].math,Stu[i].chinese,Stu[i].english,Stu[i].polity,Stu[i].cs,Stu[i].sum,Stu[i].ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			for(j=i;j<=len;j++)
			{
				Stu[j] = Stu[j+1];
			}
		}
	}
	len--;
	printf("\tû�ҵ���ѧ����\n\n");
} 
