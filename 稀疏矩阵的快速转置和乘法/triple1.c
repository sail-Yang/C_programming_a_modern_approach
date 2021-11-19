/*计算机2003 杨帆 稀疏矩阵的快速转置和乘法运算*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define MAXROW 1000

/*结构声明*/
typedef double ElemType;
/*三元组表的一行*/
typedef struct triple
{
	int row,col;
	ElemType e;
}Triple;

/*求之后矩阵快速转置的向量*/
typedef struct vector
{
	int number;
	int position;
}Vector;
/*声明三元组表的结构*/
typedef struct tsmatrix
{
	Triple data[MAXSIZE+1];			//data[0]不用
	int position[MAXROW+1];			//各行第一个非零元的位置表
	int rows,cols,NoZero_len;		//矩阵的行列数，以及非零元个数
}TsMatrix;
typedef TsMatrix *TsMatrix_ptr;

/*函数声明*/
TsMatrix CreatTsMatrix(TsMatrix A,char *file);			//创建一个稀疏矩阵
void PrintTsMatrix(TsMatrix A,char name);				//打印一个三元表表示的稀疏矩阵
void PrintTransMatrix(TsMatrix A,char oldname,char newname);			//打印转置矩阵 
TsMatrix TransMatrix(TsMatrix A);						//稀疏矩阵的转置
TsMatrix MultMatrix(TsMatrix A,TsMatrix B);				//稀疏矩阵乘法

/*---------main---------*/
int main()
{
	TsMatrix A,B,C,D;
	A = CreatTsMatrix(A,"matrix3.txt");
	PrintTsMatrix(A,'A');
	B = CreatTsMatrix(B,"matrix4.txt");
	PrintTsMatrix(B,'B');
	printf("矩阵A*矩阵B的结果");
	C = MultMatrix(A,B);
	PrintTsMatrix(C,'C');
	D = TransMatrix(A);
	PrintTransMatrix(D,'A','D');
	return 0;
}
/*-----------end---------*/


/*函数定义*/
TsMatrix CreatTsMatrix(TsMatrix A,char *file)
{
	int row,col,i=1;
	FILE *fp1;
	fp1 = fopen(file,"r");
	Vector* vec;
	double e;
	int len,k;
	//printf("请输入稀疏矩阵的行数与列数（格式为row,col）：");
	fscanf(fp1,"%d,%d",&A.rows,&A.cols);
	
	do{
		//printf("请输入稀疏矩阵的非0元素(格式为row,col,data)(输入0结束输入):");
		fscanf(fp1,"%d,%d,%lf",&row,&col,&e);
		if(row==0||col==0||e==0)
			break;
		if(col>A.cols||row>A.rows)
		{
			printf("输入的行列数超出范围，请重新输入！\n");
			continue;
		}
		A.data[i].col = col;
		A.data[i].row = row;
		A.data[i].e = e;
		i++;
		if(i>=MAXSIZE+1)
		{
			printf("矩阵已满，无法再输入！！！\n");
			break;
		}
	}while(1);
	A.NoZero_len = i-1;
	/*求各行第一个非零元的位置*/
	row = 1;
	i = 1;
	while(i<=A.NoZero_len)
	{
		if(A.data[i].row>row)
		{
			A.position[row] = 0;
			row++;
			continue;
		}else if(A.data[i].row==row)
		{
			A.position[row] = i;
			row++;
		}
		i++;
	}
	return A;
}

/*│┌ ┐└ ┘*/
void PrintTsMatrix(TsMatrix A,char name)
{
	int i,j,k=1,m;
	printf("矩阵%c为:\n",name);
	//打印┌                    ┐
	for(i=0;i<=A.cols+1;i++)
	{
		if(i==0)
			printf("\n┌  ");
		else if(i==A.cols+1)
			printf("┐\n");
		else
			printf("%-8c",' ');
	}
	for(m=0;m<=A.cols+1;m++)
		{
			if(m==0)
				printf("│  ");
			else if(m==A.cols+1)
				printf("│\n");
			else
				printf("%-8c",' ');
		}
	for(i=1;i<=A.rows;i++)
	{
		printf("│  ");
		if(A.data[k].row>i)
		{
			for(j=1;j<=A.cols;j++)
			{	
				printf("%-8.2lf",0.00);
			}	
		}else
		{
			for(j=1;j<=A.cols;j++)
			{
				if(j==A.data[k].col&&i==A.data[k].row)
				{
					printf("%-8.2lf",A.data[k].e);
					k++;
				}else
					printf("%-8.2lf",0.00);
			}
		}
		printf("│\n");
		for(m=0;m<=A.cols+1;m++)
		{
			if(m==0)
				printf("│  ");
			else if(m==A.cols+1)
				printf("│\n");
			else
				printf("%-8c",' ');
		}
	}

	for(i=0;i<=A.cols+1;i++)
	{
		if(i==0)
			printf("└  ");
		else if(i==A.cols+1)
			printf("┘\n");
		else
			printf("%-8c",' ');
	}
	return;
}
void PrintTransMatrix(TsMatrix A,char oldname,char newname)
{
	printf("%c的转置",oldname); 
	PrintTsMatrix(A,newname);
	return;	
}


TsMatrix TransMatrix(TsMatrix A)
{
	TsMatrix B;
	B.cols = A.rows;
	B.rows = A.cols;
	B.NoZero_len = A.NoZero_len;
	Vector *vec;
	int i,j;
	vec = (Vector*)malloc((A.cols+1)*sizeof(Vector));//[0]不用
	if(A.NoZero_len)
	{
		for(i=1;i<=A.cols;i++)
			vec[i].number = 0;
		for(i=1;i<=A.NoZero_len;i++)
			vec[A.data[i].col].number++;
		vec[1].position = 1;
		for(i=2;i<=A.cols;i++)
			vec[i].position = vec[i-1].position + vec[i-1].number;
		
		for(i=1;i<=A.NoZero_len;i++)
		{
			j = A.data[i].col;
			B.data[vec[j].position].e = A.data[i].e;
			B.data[vec[j].position].row = j;
			B.data[vec[j].position].col = A.data[i].row;
			vec[j].position++; 
		}
		return B;
	}
	return A;
}

TsMatrix MultMatrix(TsMatrix A,TsMatrix B)
{
	int arow,brow,acol,bcol,crow,ccol,i,j,tp,t;
	if(A.cols!=B.rows)
	{
		printf("这两矩阵不能相乘！\n");
		exit(1);
	}
	ElemType *rowsum;
	TsMatrix C;
	C.rows = A.rows;
	C.cols = B.cols;
	C.NoZero_len = 0;
	rowsum = (ElemType*)malloc((C.cols+1)*sizeof(ElemType));
	for(arow=1;arow<=A.rows;arow++)
	{
		if(A.position[arow]==0)
			continue;
		for(i=1;i<=C.cols;i++)
			rowsum[i] = 0;
		C.position[arow] = C.NoZero_len+1;
		
		if(arow<A.rows)
			tp = A.position[arow+1];
		else
			tp = A.NoZero_len+1;
			
		for(i=A.position[arow];i<tp;i++)
		{
			brow = A.data[i].col;
			if(brow<B.rows)
				t = B.position[brow+1];
			else
				t = B.NoZero_len+1;
			
			for(j = B.position[brow];j<t;j++)
			{
				ccol = B.data[j].col;
				rowsum[ccol] += A.data[i].e*B.data[j].e;
			}
		}
		for(ccol=1;ccol<=C.cols;ccol++)
		{
			if(rowsum[ccol])
			{
				if(++C.NoZero_len>MAXSIZE)
					exit(1);
				C.data[C.NoZero_len].row = arow;
				C.data[C.NoZero_len].col = ccol;
				C.data[C.NoZero_len].e = rowsum[ccol];
			}
		}
	}
	return C;
}
