/*计算机2003 杨帆 201205130 顺序栈版*/
/*创建一个运算符栈OPTR，一个操作数栈OPND*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

/*全局常量定义*/
char prec[7][7]={">><<<>>",">><<<>>",">>>><>>",">>>><>>","<<<<<=@",">>>>@>>","<<<<<@="};
char sign[]="+-*/()#";

typedef double ElemType;

/*OPND*/
typedef struct stack
{
	ElemType  Num[MAX_LEN];
	int top;
}Num_Stack;
typedef Num_Stack *NumStack;

/*OPTR*/
typedef struct Stack
{
	char Oper[MAX_LEN];
	int top;
}Oper_Stack;
typedef Oper_Stack *OperStack;

/*函数声明*/
NumStack Create_OPND();								/*创建一个存放数据的顺序栈*/ 
OperStack Create_OPTR();							/*创建一个存放符号的顺序栈*/
void Push_Num(NumStack OPND,ElemType data1);		/*压入OPND*/
void Push_Oper(OperStack OPTR,char opera1);			/*压入OPTR*/
ElemType Pop_Num(NumStack OPND);					/*从OPND弹出栈顶元素*/
char Pop_Oper(OperStack OPTR);						/*从OPTR弹出栈顶元素*/
ElemType GetNumTop(NumStack OPND);					/*获取OPTR栈顶元素*/
char GetOperTop(OperStack OPTR);					/*获取OPTR栈顶元素*/
char precede(char a,char b);						/*比较符号优先级*/
int IsNum(char c);									/*判断是否是数字*/
double TurnToDouble(char *expression,int *ptr_i);	/*将字符串中的数字转化为浮点数*/
ElemType Operate(ElemType a,char c,ElemType b);		/*操作*/
ElemType Evaluate_Expression(char *expression);		/*主运算*/ 

/*------------主函数------------*/
int main()
{
	ElemType result;
	char oper1,expression[MAX_LEN];
	int i=0;
	printf("表达式的计算以#结束!\n");
	printf("请输入表达式(支持浮点数)：");
	gets(expression);
	result = Evaluate_Expression(expression);
	system("cls");
	printf("表达式结果为："); 
	for(i=0;i<strlen(expression)-1;i++)
		printf("%c",expression[i]);
	printf(" = %f\n",result);
	return 0;
}
/*-------------END-------------*/

/*------------函数定义------------*/

/*创建一个存放数据的顺序栈*/
NumStack Create_OPND()
{
	NumStack OPND;
	OPND = (NumStack)malloc(sizeof(Num_Stack));
	OPND->top = -1;
	return OPND;
}

/*创建一个存放运算符的顺序栈*/
OperStack Create_OPTR()
{
	OperStack OPTR;
	OPTR = (OperStack)malloc(sizeof(Oper_Stack));
	OPTR->top = -1;
	return OPTR;
}

/*压入OPND*/
void Push_Num(NumStack OPND,ElemType data1)
{
	if(OPND->top>=MAX_LEN-1)
	{
		printf("OPND is full!!!\n ");
		return;
	}
	OPND->top++;
	OPND->Num[OPND->top] = data1;
	return;
}

/*压入OPTR*/
void Push_Oper(OperStack OPTR,char opera1)
{
	if(OPTR->top>=MAX_LEN-1)
	{
		printf("OPTR is full!!!\n ");
		return;
	}
	OPTR->top++;
	OPTR->Oper[OPTR->top] = opera1;
	return;
}

/*从OPND弹出栈顶元素*/
ElemType Pop_Num(NumStack OPND)
{
	if(OPND->top==-1)
	{
		printf("OPND is empty!!!\n ");
		return;
	}
	ElemType data1;
	data1 = OPND->Num[OPND->top];
	OPND->top--;
	return data1;
}			

/*从OPTR弹出栈顶元素*/
char Pop_Oper(OperStack OPTR)
{
	if(OPTR->top==-1)
	{
		printf("OPTR is empty!!!\n ");
		return;
	}
	char opera1;
	opera1 = OPTR->Oper[OPTR->top];
	OPTR->top--;
	return opera1;
}

/*获取OPND栈顶元素*/
ElemType GetNumTop(NumStack OPND)
{
	if(OPND->top==-1)
	{
		printf("OPND is empty!!!\n ");
		return;
	}
	ElemType data1;
	data1 = OPND->Num[OPND->top];
	return data1;
}

/*获取OPTR栈顶元素*/
char GetOperTop(OperStack OPTR)
{
	if(OPTR->top==-1)
	{
		printf("OPTR is empty!!!\n ");
		return;
	}
	char opera1;
	opera1 = OPTR->Oper[OPTR->top];
	return opera1;
}

/*比较符号优先级*/
char precede(char a,char b)
{
	int i=0,j=0;
 	
 	while(sign[i]!=a) i++;
 	while(sign[j]!=b) j++;
 	return (prec[i][j]);
}

/*判断是否是数字*/
int IsNum(char c)
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}

/*将字符串中的数字转化为浮点数*/ 
double TurnToDouble(char *expression,int *ptr_i) 
{
	int i = *ptr_i;
	int str_len=0;
	char str_result[MAX_LEN];
	ElemType result;
	while((expression[i]<='9'&&expression[i]>='0')||expression[i]=='.')
	{
		str_result[str_len] = expression[i++];
		str_len++;
	}
	str_result[str_len] = '\0';
	result = atof(str_result);
	*ptr_i = i;
	return result;
}

/*操作两个数*/ 
ElemType Operate(ElemType a,char theta,ElemType b)
{
	ElemType num;
    switch (theta)
    {
		case '+': 	num=a+b;break;
	 	case '-': 	num=a-b;break;
	 	case '*': 	num=a*b;break;
	 	case '/': 	num=a/b;break;
	 	default:	printf("运算符输入错误！\n");return;
    }
    return num;
}

/*主运算*/
ElemType Evaluate_Expression(char *expression)
{
	NumStack OPND = Create_OPND();
	OperStack OPTR = Create_OPTR();
	int i=0;
	ElemType a,b,num1;
	char theta,theta1;
	
	Push_Oper(OPTR,'#');
	while(expression[i]!='#'||GetOperTop(OPTR)!='#')
	{
		if(IsNum(expression[i]))
		{
			num1 = TurnToDouble(expression,&i);
			Push_Num(OPND,num1);
		}else
		{
			switch(precede(GetOperTop(OPTR),expression[i]))
			{
				case '<':	Push_Oper(OPTR,expression[i++]);break;
				case '=':	theta1 = Pop_Oper(OPTR);i++;break;
				case '>':	theta = Pop_Oper(OPTR);b = Pop_Num(OPND);a = Pop_Num(OPND);Push_Num(OPND,Operate(a,theta,b));break;
				//Push_Num(OPND,Operate(a,theta,b))
				Default: 	printf("Have something wrong!\n");break;
			}
		}
	}
	return GetNumTop(OPND);
}							

