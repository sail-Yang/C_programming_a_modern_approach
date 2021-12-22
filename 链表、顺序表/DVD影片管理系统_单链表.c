/*�����2003 201205130 � DVDӰƬ����ϵͳ*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILMNAME 30	
#define MAX_TYPENAME 30	
#define NUM_AREA 6
#define NUM_TYPE 10
#define NODE_LEN sizeof(Film)
/*���ͱ�������*/
typedef int Number;
typedef double Price;
typedef struct Film
{
	char name[MAX_FILMNAME];//ӰƬ��
	char area[MAX_TYPENAME];//����
	char type[MAX_TYPENAME];//����
	Number num;				//ӰƬ���
	Price price;			//�۸�
	int year;				//���
	int month;				//�·�
	int day;				//��
	struct Film *next;
}Film,*Film_ptr,*FilmList;
/*ȫ�ֱ���*/
char AllArea[NUM_AREA][MAX_TYPENAME] = {"��½","��̨","ŷ��","�ձ�","����","����"};
char AllType[NUM_TYPE][MAX_TYPENAME] = {"�ƻ�","����","����","��¼Ƭ","�ֲ�","ϲ��","ս��","��ͯ","��־","����"};
/*--------��������--------*/
void CreateFilmList(FilmList *L_ptr);
void ClearFilmList(FilmList *L_ptr);
void PrintMenu();
int Get_Len(FilmList L);
Film_ptr GetPreNode(FilmList L,Film_ptr p);
void NewFilm(FilmList *L_ptr);
void PrintAll(FilmList L);
void DeleteFilm(FilmList *L_ptr);
void ModifyFilm(FilmList *L_ptr);
void Sort(FilmList *L_ptr);
void CountType(FilmList *L_ptr);
void ReadFile(FilmList *L_ptr);
void SaveFile(FilmList L);
/*-----------main-------------*/
int main(){
	FilmList L;int order;
	CreateFilmList(&L);
	do{
		PrintMenu();
		scanf("%d",&order);
		switch(order){
			case 1: NewFilm(&L);system("pause");break;
			case 2: PrintAll(L);system("pause");break;
			case 3: DeleteFilm(&L);system("pause");break;
			case 4: ModifyFilm(&L);system("pause");break;
			case 5: Sort(&L);system("pause");break;
			case 6: CountType(&L);system("pause");break;
			case 7: SaveFile(L);system("pause");break;
			case 8: ReadFile(&L);system("pause");break;
			default: return 0;
		}
		getchar();
	}while(1);
	return 0;
}
/*��������*/
void CreateFilmList(FilmList *L_ptr){
	*L_ptr = (Film_ptr)malloc(NODE_LEN);
	(*L_ptr)->next = NULL;
}
void ClearFilmList(FilmList *L_ptr){
	if((*L_ptr)->next!=NULL)
	{
		Film_ptr p = (*L_ptr)->next,q;
		while(p!=NULL){
			q = p->next;
			free(p);
			p = q;
		}
		(*L_ptr)->next = NULL;
	}
}
void NewFilm(FilmList *L_ptr){
	system("cls");
	Film_ptr p=(*L_ptr)->next,q;
	int i;char order;
	q=(Film_ptr)malloc(NODE_LEN);
	printf("�밴�ո�ʽ��������ӰƬ��Ϣ(ӰƬ���,ӰƬ��,�۸�,��������,����,��-��-��)��");
	scanf("%d,%[^,],%lf,%[^,],%[^,],%d-%d-%d",&q->num,q->name,&q->price,q->area,q->type,&q->year,&q->month,&q->day);
	/*����Ϸ��ж�*/
	//����Ƿ�Ϸ�
	while(p!=NULL){
		if(q->num==p->num)
		{
			printf("������ظ���������������:");
			scanf("%d",&q->num);
			fflush(stdin);
		}else
			p=p->next;
	}
	//���������Ƿ�Ϸ�
	for(i=0;i<NUM_AREA;i++)
		if(!strcmp(q->area,AllArea[i]))
			break;
	if(i==NUM_AREA)
	{
		printf("��ӰƬ�ĵ������Ͳ������ڱ�ϵͳ�����Զ�������������Ϊ�������Ƿ���Ҫ���������������(Y/N):\n");
		fflush(stdin);
		scanf("%c",&order);
		if(order=='Y'||order=='y')
		{
			printf("�����������������:");
			fflush(stdin);
			scanf("%s",q->area);
			printf("���ĵ������ͳɹ���");
		}else
			strcpy(q->area,"����");
	}
	//�����Ƿ�Ϸ�
	for(i=0;i<NUM_TYPE;i++)
	{
		if(!strcmp(q->type,AllType[i]))
			break;
	}
	if(i==NUM_TYPE)
	{
		printf("��ӰƬ�����Ͳ������ڱ�ϵͳ�����Զ���������Ϊ�������Ƿ���Ҫ������������(Y/N):\n");
		fflush(stdin);
		scanf("%c",&order);
		if(order=='Y'||order=='y')
		{
			printf("��������������:");
			fflush(stdin);
			scanf("%s",q->type);
			printf("�������ͳɹ���");
		}else
			strcpy(q->type,"����");
	}

	p = *L_ptr;
	while(p->next!=NULL)
		p=p->next;
	p->next=q;
	q->next=NULL;
	printf("����ӰƬ�ɹ���\n");
}


void ReadFile(FilmList *L_ptr)
{
	ClearFilmList(L_ptr);
	FILE *fp;
	char filename[100];
	printf("�������ļ�·��(����ʹ��\\):");
	scanf("%s",filename);
	fp = fopen(filename,"r");
	/*�ж��ļ��Ƿ�򿪳ɹ�*/
	while(fp==NULL)
	{
		printf("�ļ���ʧ�ܣ������������ļ�·��:");
		getchar();
		scanf("%s",filename);
		fp = fopen(filename,"r");
	}

	Film_ptr p = *L_ptr,q;
	while(!feof(fp))
	{
		q = (Film_ptr)malloc(NODE_LEN);
		fscanf(fp,"%d,%[^,],%lf,%[^,],%[^,],%d-%d-%d",&q->num,q->name,&q->price,q->area,q->type,&q->year,&q->month,&q->day);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	printf("�ļ���ȡ�ɹ�!\n");
	fclose(fp);
}

void SaveFile(FilmList L)
{
	FILE *fp;
	char filename[100];
	printf("�������ļ�·��(����ʹ��\\):");
	scanf("%s",filename);
	fp = fopen(filename,"w+");
	/*�ж��ļ��Ƿ�򿪳ɹ�*/
	while(fp==NULL)
	{
		system("cls");
		printf("�ļ���ʧ�ܣ������������ļ�·��:");
		getchar();
		scanf("%s",filename);
		fp = fopen(filename,"w+");
	}
	Film_ptr p = L->next,q;
	while(p!=NULL)
	{
		fprintf(fp,"%d,%s,%.2lf,%s,%s,%d-%d-%d",p->num,p->name,p->price,p->area,p->type,p->year,p->month,p->day);
		if(p->next!=NULL)
			fprintf(fp,"\n");
		p = p->next;
	}
	printf("�ļ�����ɹ�!\n");
	fclose(fp);
}

/*������ ���� ���� �ȩ� �� ��*/
void PrintAll(FilmList L)
{
	system("cls");
	Film_ptr p = L->next,q;
	printf("�����������������������Щ��������������������������������������������Щ��������������������Щ��������������������Щ��������������������Щ���������������������������������\n");
	printf("��   ���   ��         Ƭ��         ��   �۸�   ��   ����   ��   ����   ��    ��������    ��\n");
	while(p!=NULL)
	{
		printf("�����������������������੤�������������������������������������������੤�������������������੤�������������������੤�������������������੤��������������������������������\n");
		printf("��  %-8d��   %-19s��  %-8.2lf��  %-6s  ��  %-6s  ��   %04d-%02d-%02d   ��\n",p->num,p->name,p->price,p->area,p->type,p->year,p->month,p->day);
		p = p->next;
	}
	printf("�����������������������ة��������������������������������������������ة��������������������ة��������������������ة��������������������ة���������������������������������\n");
}

void DeleteFilm(FilmList *L_ptr)
{
	Number num;
	system("cls");
	printf("��������Ҫɾ��ӰƬ�ı��:");
	fflush(stdin);
	scanf("%d",&num);
	Film_ptr p = *L_ptr,q;
	while(1)
	{
		while(p->next!=NULL)
		{
			if(num==p->next->num)
				break;
			p=p->next;
		}
		if(p->next!=NULL)
		{
			q = p->next;
			printf("����ӰƬ�ѱ�ɾ��:\n");
			printf("�����������������������Щ��������������������������������������������Щ��������������������Щ��������������������Щ��������������������Щ���������������������������������\n");
			printf("��   ���   ��         Ƭ��         ��   �۸�   ��   ����   ��   ����   ��    ��������    ��\n");
			printf("�����������������������੤�������������������������������������������੤�������������������੤�������������������੤�������������������੤��������������������������������\n");
			printf("��  %-8d��   %-19s��  %-8.2lf��  %-6s  ��  %-6s  ��   %04d-%02d-%02d   ��\n",q->num,q->name,q->price,q->area,q->type,q->year,q->month,q->day);
			printf("�����������������������ة��������������������������������������������ة��������������������ة��������������������ة��������������������ة���������������������������������\n");
			p->next = q->next;
			free(q);
			return;
		}else
		{
			char order;
			printf("��Ų����ڣ��Ƿ�Ҫ���������ţ���y/n��");
			fflush(stdin);
			scanf("%c",&order);
			if(order=='y'||order=='Y')
			{
				printf("������������Ҫɾ��ӰƬ�ı��:");
				fflush(stdin);
				scanf("%d",&num);
				p = *L_ptr;
			}else
				return;
		}
	}
}

void ModifyFilm(FilmList *L_ptr)
{
	Number num;
	system("cls");
	printf("��������Ҫ�޸ĵ�ӰƬ�ı��:");
	fflush(stdin);
	scanf("%d",&num);
	Film_ptr p = *L_ptr,q;
	while(1)
	{
		while(p!=NULL)
		{
			if(num==p->num)
				break;
			p=p->next;
		}
		if(p!=NULL)
		{
			printf("%d��ӰƬ��Ϣ����:\n",p->num);
			printf("�����������������������Щ��������������������������������������������Щ��������������������Щ��������������������Щ��������������������Щ���������������������������������\n");
			printf("��   ���   ��         Ƭ��         ��   �۸�   ��   ����   ��   ����   ��    ��������    ��\n");
			printf("�����������������������੤�������������������������������������������੤�������������������੤�������������������੤�������������������੤��������������������������������\n");
			printf("��  %-8d��   %-19s��  %-8.2lf��  %-6s  ��  %-6s  ��   %04d-%02d-%02d   ��\n",p->num,p->name,p->price,p->area,p->type,p->year,p->month,p->day);
			printf("�����������������������ة��������������������������������������������ة��������������������ة��������������������ة��������������������ة���������������������������������\n");
			printf("�������ӰƬ�޸ĺ����Ϣ(�۸�,��������,����,��-��-��):");
			fflush(stdin);
			scanf("%lf,%[^,],%[^,],%d-%d-%d",&p->price,p->area,p->type,&p->year,&p->month,&p->day);
			printf("�޸ĳɹ�!");
			return;
		}else
		{
			char order;
			printf("��Ų����ڣ��Ƿ�Ҫ���������ţ���y/n��");
			fflush(stdin);
			scanf("%c",&order);
			if(order=='y'||order=='Y')
			{
				printf("������������Ҫ�޸ĵ�ӰƬ�ı��:");
				fflush(stdin);
				scanf("%d",&num);
				p = *L_ptr;
			}else
				return;
		}
	}
}

void Sort(FilmList *L_ptr)
{
	Film_ptr p=(*L_ptr)->next,p_next,pre_p;
    int i,j,len;
    len = Get_Len(*L_ptr);		//��������ȣ�����ͷ��㣩
    for(i=0;i<len-1;i++)		//��������Ϊ6�����һ�����ò�������������5�ξ͹��ˣ�
    {
        j = len - i -1;			//ÿѭ��һ�Σ����ǾͿ����ٱȽ�һ��Ԫ�أ���Ϊÿ�δ�Ķ��ᱻ�ĵ����棬û��Ҫ�ڱȽ�
        while(p->next != NULL && j!=0)
        {
            j--;
            p_next = p->next;
            if(p->num > p_next->num)
            {
                pre_p = GetPreNode(*L_ptr,p);
                pre_p->next = p_next;
                p->next = p_next->next;
                p_next->next = p;
            }else
            {
                p = p_next;
            }
        }
        p = (*L_ptr)->next;
    }
	printf("����ɹ���\n");
}

void CountType(FilmList *L_ptr)
{
	system("cls");
	printf("�������ѯͳ������(0�����������,1������������):");
	int ty,i;
	scanf("%d",&ty);
	while(1)
	{
		if(ty==0||ty==1)
			break;
		printf("���ʹ�������������:");
		fflush(stdin);
		scanf("%d",&ty);
	}
	Film_ptr p=(*L_ptr)->next;
	int Filmtype[NUM_TYPE]={0},Filmarea[NUM_AREA]={0};
	while(p)
	{
		for(i=0;i<NUM_AREA;i++)
		{
			if(strcmp(p->area,AllArea[i])==0)
				Filmarea[i]++;
		}
		for(i=0;i<NUM_TYPE;i++)
		{
			if(strcmp(p->type,AllType[i])==0)
				Filmtype[i]++;
		}
		p=p->next;
	}
	system("cls");
	if(ty==0)
	{
		printf("���������ͽ��в�ѯͳ��:\n");
		printf("�����������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ���������������������\n");
		printf("��          ��   ��½   ��   ��̨   ��   ŷ��   ��   �ձ�   ��   ����   ��   ����   ��\n");
		printf("�����������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤��������������������\n");
		printf("��   ����   ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��\n",Filmarea[0],Filmarea[1],Filmarea[2],Filmarea[3],Filmarea[4],Filmarea[5]);
		printf("�����������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة���������������������\n");
	}else
	{
		printf("�����ͽ��в�ѯͳ��:\n");
		printf("�����������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ��������������������Щ���������������������\n");
		printf("��          ��   �ƻ�   ��   ����   ��   ����   ��  ��¼Ƭ  ��   �ֲ�   ��   ϲ��   ��   ս��   ��   ��ͯ   ��   ��־   ��   ����   ��\n");
		printf("�����������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤�������������������੤��������������������\n");
		printf("��   ����   ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��     %-4d ��\n",Filmtype[0],Filmtype[1],Filmtype[2],Filmtype[3],Filmtype[4],Filmtype[5],Filmtype[6],Filmtype[7],Filmtype[8],Filmtype[9]);
		printf("�����������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة��������������������ة���������������������\n");
	}
	
}
void PrintMenu()
{
	system("cls");
	printf(	"     ���ܲ˵�\n\n"
			"   1.����DVDӰƬ\n\n"
			"   2.DVDӰƬ���\n\n"
			"   3.DVDӰƬɾ��\n\n"
			"   4.DVDӰƬ�޸�\n\n"
			"   5.DVDӰƬ����\n\n"
			"   6.DVDӰƬ��ѯͳ��\n\n"
			"   7.����DVDӰƬ����\n\n"
			"   8.���ļ��ж�ȡDVDӰƬ����\n\n"
			"   9.��������ָ���˳�����\n\n"
			"������ָ��:"
	);
}
int Get_Len(FilmList L)
{
	Film_ptr p = L->next;
	int len = 0;
	while(p!=NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}
Film_ptr GetPreNode(FilmList L,Film_ptr p)
{
	Film_ptr q = L;
	while(q!=NULL)
	{
		if(q->next==p)
			return q;
		q=q->next;
	}
	printf("�ýڵ㲻����ǰ����\n");
	return NULL;
}