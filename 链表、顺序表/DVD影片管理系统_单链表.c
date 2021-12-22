/*计算机2003 201205130 杨帆 DVD影片管理系统*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILMNAME 30	
#define MAX_TYPENAME 30	
#define NUM_AREA 6
#define NUM_TYPE 10
#define NODE_LEN sizeof(Film)
/*类型别名声明*/
typedef int Number;
typedef double Price;
typedef struct Film
{
	char name[MAX_FILMNAME];//影片名
	char area[MAX_TYPENAME];//地区
	char type[MAX_TYPENAME];//种类
	Number num;				//影片编号
	Price price;			//价格
	int year;				//年份
	int month;				//月份
	int day;				//日
	struct Film *next;
}Film,*Film_ptr,*FilmList;
/*全局变量*/
char AllArea[NUM_AREA][MAX_TYPENAME] = {"大陆","港台","欧美","日本","韩国","其它"};
char AllType[NUM_TYPE][MAX_TYPENAME] = {"科幻","爱情","动漫","纪录片","恐怖","喜剧","战争","儿童","励志","其它"};
/*--------函数声明--------*/
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
/*函数定义*/
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
	printf("请按照格式输入新增影片信息(影片编号,影片名,价格,地区类型,类型,年-月-日)：");
	scanf("%d,%[^,],%lf,%[^,],%[^,],%d-%d-%d",&q->num,q->name,&q->price,q->area,q->type,&q->year,&q->month,&q->day);
	/*输入合法判断*/
	//编号是否合法
	while(p!=NULL){
		if(q->num==p->num)
		{
			printf("编号已重复！请重新输入编号:");
			scanf("%d",&q->num);
			fflush(stdin);
		}else
			p=p->next;
	}
	//地区类型是否合法
	for(i=0;i<NUM_AREA;i++)
		if(!strcmp(q->area,AllArea[i]))
			break;
	if(i==NUM_AREA)
	{
		printf("本影片的地区类型不存在于本系统，已自动将地区类型置为其它！是否需要重新输入地区类型(Y/N):\n");
		fflush(stdin);
		scanf("%c",&order);
		if(order=='Y'||order=='y')
		{
			printf("请重新输入地区类型:");
			fflush(stdin);
			scanf("%s",q->area);
			printf("更改地区类型成功！");
		}else
			strcpy(q->area,"其它");
	}
	//类型是否合法
	for(i=0;i<NUM_TYPE;i++)
	{
		if(!strcmp(q->type,AllType[i]))
			break;
	}
	if(i==NUM_TYPE)
	{
		printf("本影片的类型不存在于本系统，已自动将类型置为其它！是否需要重新输入类型(Y/N):\n");
		fflush(stdin);
		scanf("%c",&order);
		if(order=='Y'||order=='y')
		{
			printf("请重新输入类型:");
			fflush(stdin);
			scanf("%s",q->type);
			printf("更改类型成功！");
		}else
			strcpy(q->type,"其它");
	}

	p = *L_ptr;
	while(p->next!=NULL)
		p=p->next;
	p->next=q;
	q->next=NULL;
	printf("新增影片成功！\n");
}


void ReadFile(FilmList *L_ptr)
{
	ClearFilmList(L_ptr);
	FILE *fp;
	char filename[100];
	printf("请输入文件路径(请勿使用\\):");
	scanf("%s",filename);
	fp = fopen(filename,"r");
	/*判断文件是否打开成功*/
	while(fp==NULL)
	{
		printf("文件打开失败！请重新输入文件路径:");
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
	printf("文件读取成功!\n");
	fclose(fp);
}

void SaveFile(FilmList L)
{
	FILE *fp;
	char filename[100];
	printf("请输入文件路径(请勿使用\\):");
	scanf("%s",filename);
	fp = fopen(filename,"w+");
	/*判断文件是否打开成功*/
	while(fp==NULL)
	{
		system("cls");
		printf("文件打开失败！请重新输入文件路径:");
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
	printf("文件保存成功!\n");
	fclose(fp);
}

/*─│┌ ┐└ ┘├ ┤┬ ┴ ┼*/
void PrintAll(FilmList L)
{
	system("cls");
	Film_ptr p = L->next,q;
	printf("┌──────────┬──────────────────────┬──────────┬──────────┬──────────┬────────────────┐\n");
	printf("│   编号   │         片名         │   价格   │   地区   │   类型   │    出版日期    │\n");
	while(p!=NULL)
	{
		printf("├──────────┼──────────────────────┼──────────┼──────────┼──────────┼────────────────┤\n");
		printf("│  %-8d│   %-19s│  %-8.2lf│  %-6s  │  %-6s  │   %04d-%02d-%02d   │\n",p->num,p->name,p->price,p->area,p->type,p->year,p->month,p->day);
		p = p->next;
	}
	printf("└──────────┴──────────────────────┴──────────┴──────────┴──────────┴────────────────┘\n");
}

void DeleteFilm(FilmList *L_ptr)
{
	Number num;
	system("cls");
	printf("请输入你要删除影片的编号:");
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
			printf("下列影片已被删除:\n");
			printf("┌──────────┬──────────────────────┬──────────┬──────────┬──────────┬────────────────┐\n");
			printf("│   编号   │         片名         │   价格   │   地区   │   类型   │    出版日期    │\n");
			printf("├──────────┼──────────────────────┼──────────┼──────────┼──────────┼────────────────┤\n");
			printf("│  %-8d│   %-19s│  %-8.2lf│  %-6s  │  %-6s  │   %04d-%02d-%02d   │\n",q->num,q->name,q->price,q->area,q->type,q->year,q->month,q->day);
			printf("└──────────┴──────────────────────┴──────────┴──────────┴──────────┴────────────────┘\n");
			p->next = q->next;
			free(q);
			return;
		}else
		{
			char order;
			printf("编号不存在！是否要重新输入编号？（y/n）");
			fflush(stdin);
			scanf("%c",&order);
			if(order=='y'||order=='Y')
			{
				printf("请重新输入您要删除影片的编号:");
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
	printf("请输入你要修改的影片的编号:");
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
			printf("%d号影片信息如下:\n",p->num);
			printf("┌──────────┬──────────────────────┬──────────┬──────────┬──────────┬────────────────┐\n");
			printf("│   编号   │         片名         │   价格   │   地区   │   类型   │    出版日期    │\n");
			printf("├──────────┼──────────────────────┼──────────┼──────────┼──────────┼────────────────┤\n");
			printf("│  %-8d│   %-19s│  %-8.2lf│  %-6s  │  %-6s  │   %04d-%02d-%02d   │\n",p->num,p->name,p->price,p->area,p->type,p->year,p->month,p->day);
			printf("└──────────┴──────────────────────┴──────────┴──────────┴──────────┴────────────────┘\n");
			printf("请输入该影片修改后的信息(价格,地区类型,类型,年-月-日):");
			fflush(stdin);
			scanf("%lf,%[^,],%[^,],%d-%d-%d",&p->price,p->area,p->type,&p->year,&p->month,&p->day);
			printf("修改成功!");
			return;
		}else
		{
			char order;
			printf("编号不存在！是否要重新输入编号？（y/n）");
			fflush(stdin);
			scanf("%c",&order);
			if(order=='y'||order=='Y')
			{
				printf("请重新输入您要修改的影片的编号:");
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
    len = Get_Len(*L_ptr);		//获得链表长度（不算头结点）
    for(i=0;i<len-1;i++)		//设链表长度为6，最后一个不用操作，所以咱们5次就够了，
    {
        j = len - i -1;			//每循环一次，我们就可以少比较一个元素，因为每次大的都会被拍到后面，没必要在比较
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
	printf("排序成功！\n");
}

void CountType(FilmList *L_ptr)
{
	system("cls");
	printf("请输入查询统计类型(0代表地区类型,1代表内容类型):");
	int ty,i;
	scanf("%d",&ty);
	while(1)
	{
		if(ty==0||ty==1)
			break;
		printf("类型错误，请重新输入:");
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
		printf("按地区类型进行查询统计:\n");
		printf("┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐\n");
		printf("│          │   大陆   │   港台   │   欧美   │   日本   │   韩国   │   其它   │\n");
		printf("├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n");
		printf("│   数量   │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │\n",Filmarea[0],Filmarea[1],Filmarea[2],Filmarea[3],Filmarea[4],Filmarea[5]);
		printf("└──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘\n");
	}else
	{
		printf("按类型进行查询统计:\n");
		printf("┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐\n");
		printf("│          │   科幻   │   爱情   │   动漫   │  纪录片  │   恐怖   │   喜剧   │   战争   │   儿童   │   励志   │   其它   │\n");
		printf("├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤\n");
		printf("│   数量   │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │     %-4d │\n",Filmtype[0],Filmtype[1],Filmtype[2],Filmtype[3],Filmtype[4],Filmtype[5],Filmtype[6],Filmtype[7],Filmtype[8],Filmtype[9]);
		printf("└──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘\n");
	}
	
}
void PrintMenu()
{
	system("cls");
	printf(	"     功能菜单\n\n"
			"   1.新增DVD影片\n\n"
			"   2.DVD影片浏览\n\n"
			"   3.DVD影片删除\n\n"
			"   4.DVD影片修改\n\n"
			"   5.DVD影片排序\n\n"
			"   6.DVD影片查询统计\n\n"
			"   7.保存DVD影片数据\n\n"
			"   8.从文件中读取DVD影片数据\n\n"
			"   9.输入其它指令退出程序\n\n"
			"请输入指令:"
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
	printf("该节点不存在前驱！\n");
	return NULL;
}