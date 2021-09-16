/*�����2003 201205130 � ��һ�ⵥ�����*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NameLen_Max 30		//�ַ�����󳤶� 
#define LEN sizeof(Student)	//�ṹ���ֽ��� 

/*typedef*/
typedef double Score;		//���� 
typedef int Number; 		

/*���Student*/
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

/*��������*/
Student *Create();					//�������ݣ�������Ϣ��
void Print_Panel();					//��ӡ������� 
void Print_Norank(Student *head);	//��ӡ��Ϣ��(������) ,������Ϣ������д��txt
void Print_Rank(Student *head);		//��ӡ��Ϣ��(������),������Ϣ������д��txt
void Search(Student *head); 		//��ѧ�Ų���
Student *Insert(Student *head);		//����ѧ�����������Ϣ
Student *Delete(Student *head);		//ɾ��ѧ�����������Ϣ
void Ave_Class(Student *head);		//��ȡÿ�ſγ̵�ƽ���� 
int Get_Len(Student *head);			//��ȡѧ���������������� 
Student *Sort_Num(Student *head);	//��ѧ������ ������ ��ʹ��ð������ 
Student *Sort_Sum(Student *head);	//���ܷ��������� ,ʹ��ð������ 


/*-----------������-----------*/
int main()
{
	Student *head;
	char order;
	/*������Ϣ��*/ 
	head = Create();
	/*����*/ 
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
		getchar();	//����\n�� 
	}while(1); 
	return 0;
}
/*-----------END-----------*/


/*��������*/
/*�������ݣ�txt�ļ���ʽ:ѧ��,����,��ѧ�����ģ�Ӣ�����*/
Student *Create()
{
	Student *head;
	Student *p1,*p2;
	FILE *fp1;
	head = NULL;
	int n = 0 ;
	//���ļ����������� 
	fp1 = fopen("e:\\homework\\data.txt","r");		//�����ļ�·�� ,rΪֻ�� 
	p1 = (Student *)malloc(LEN);
	p2 = p1;
	fscanf(fp1,"%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p1->num,p1->name,&p1->math,&p1->chinese,&p1->english,&p1->polity,&p1->cs);
	/*�����ֺܷ�ƽ����*/ 
	p1->sum = p1->math+p1->chinese+p1->english+p1->polity+p1->cs;
	p1->ave = p1->sum/5;
	
	/*ѭ������*/ 
	while (p1->num!=0)	//����Ҫ������Դ�ļ����һ����0,0 
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
    p2->Next=NULL; 		//tailָ��NULL 
    fclose(fp1);
    return head;
} 

/*��ӡ�������*/
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

/*��ӡ��Ϣ��������*/
/*������ ���� ���� �ȩ� �� ��*/
void Print_Norank(Student *head)
{
	int len=0;		//rankΪ���� 
	Student *p = head;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(head);
  	printf("\n�˱��й���%d����¼:\n",len);
  	
  	if (head!=NULL){	
		printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
		printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
   
    	do{
			fprintf(fp,"%d,%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf\n",p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");       	
       		printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
       		p=p->Next;
       	}while (p!=NULL);
    	printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");  
  	}
  	fclose(fp);
}

/*��ӡ��Ϣ��,������*/
/*������ ���� ���� �ȩ� �� ��*/
void Print_Rank(Student *head)
{
	int rank=1,len=0;		//rankΪ���� 
	Student *p = head;
	FILE *fp;
  	fp=fopen("e:\\result.txt","w");
  	
	len = Get_Len(head);
  	printf("\n�˱��й���%d����¼:\n",len);
  	
  	if (head!=NULL){	
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

/*��ѧ�Ų��� */
void Search(Student *head)
{
	Student *p;
	int rank=1,number;
	printf("	������������ҵ�ѧ����ѧ��:   ");
	scanf("%d",&number);
	p = head;
	while(p!=NULL)
	{
		if(p->num == number)
		{
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',p->num,p->name,p->math,p->chinese,p->english,p->polity,p->cs,p->sum,p->ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			return;
		}	
		rank++;
		p = p->Next;
	}
	printf("\tû�ҵ���ѧ����\n\n");
}

/*����һ����ѧ������Ϣ����ѧ��˳�򽫸�ѧ������Ϣ��������������ʹ��ͷ�巨*/
Student *Insert(Student *head)
{
	Student *p1,*p2;
	p1 = head->Next;
	p2 = (Student *)malloc(LEN);
	p2->Next = p1;
	head->Next = p2;
	printf("\t������ѧ������Ϣ����ʽΪѧ��,����,��ѧ,����,Ӣ��,����,�������Ӣ�Ķ��ţ���");
	scanf("%d,%[^,],%lf,%lf,%lf,%lf,%lf",&p2->num,p2->name,&p2->math,&p2->chinese,&p2->english,&p2->polity,&p2->cs);
	p2->sum = p2->math+p2->chinese+p2->english+p2->polity+p2->cs;
	p2->ave = p2->sum/5;
	head = Sort_Num(head);
	return head;
}

/*��ȡѧ������*/
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

/*��ѧ������ ������ */ 
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


/*ɾ��ѧ����ɾ����Ϣ*/
Student *Delete(Student *head)
{
	Student *p1,*p2,*pre_p1;
	char de_name[NameLen_Max+1];
	printf("	������Ҫɾ��ѧ����������");
	scanf("%s",&de_name); 
	pre_p1 = head;
	p1 = head->Next;
	while(p1!=NULL)
	{
		if(pre_p1 == head && strcmp(pre_p1->name,de_name)==0){
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8c��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",'\0',pre_p1->num,pre_p1->name,pre_p1->math,pre_p1->chinese,pre_p1->english,pre_p1->polity,pre_p1->cs,pre_p1->sum,pre_p1->ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			free(head);
			//free(pre_ptr1);
			head = p1;
			return head;
		}else if(strcmp(p1->name,de_name)==0)
		{
			p2 = p1->Next;
			pre_p1->Next = p2;
			printf("�������������������Щ����������������Щ��������������������������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ����������������Щ�����������������\n");
			printf("������    ��ѧ��    ��  ��      ��    ����ѧ    ������    ��Ӣ��    ������    �������  ���ܷ�    ��ƽ����  ��\n");
			printf("�������������������੤���������������੤�������������������������������੤���������������੤���������������੤���������������੤���������������੤���������������੤���������������੤����������������\n");
			printf("��%-8d��%-8d��%-16s��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��%-8.1f��\n",0,p1->num,p1->name,p1->math,p1->chinese,p1->english,p1->polity,p1->cs,p1->sum,p1->ave);
			printf("�������������������ة����������������ة��������������������������������ة����������������ة����������������ة����������������ة����������������ة����������������ة����������������ة�����������������\n");
			free(p1);
			p1 = NULL;
			return head;
		}else{
			pre_p1 = p1;
			p1 = p1->Next;	
		}
	}
	printf("δ���ҵ���ѧ����\n\n");
	return head;
}

/*��ȡÿ�ſγ̵�ƽ����*/
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
	
	printf("\n\t\t��ѧƽ���֣�\t%3.1lf\n\t\t����ƽ���֣�\t%3.1lf\n\t\tӢ��ƽ���֣�\t%3.1lf\n\t\t����ƽ���֣�\t%3.1lf\n\t\t�����ƽ���֣�\t%3.1lf\n\n",Math/len,Chinese/len,English/len,Polity/len,Cs/len); 
	return; 
}

	
//����ʵ��ð������
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


