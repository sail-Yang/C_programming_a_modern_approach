/*�����2003 � 201205130 ˳��ջ��*/
/*����һ�������ջOPTR��һ��������ջOPND*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

/*ȫ�ֳ�������*/
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

/*��������*/
NumStack Create_OPND();								/*����һ��������ݵ�˳��ջ*/ 
OperStack Create_OPTR();							/*����һ����ŷ��ŵ�˳��ջ*/
void Push_Num(NumStack OPND,ElemType data1);		/*ѹ��OPND*/
void Push_Oper(OperStack OPTR,char opera1);			/*ѹ��OPTR*/
ElemType Pop_Num(NumStack OPND);					/*��OPND����ջ��Ԫ��*/
char Pop_Oper(OperStack OPTR);						/*��OPTR����ջ��Ԫ��*/
ElemType GetNumTop(NumStack OPND);					/*��ȡOPTRջ��Ԫ��*/
char GetOperTop(OperStack OPTR);					/*��ȡOPTRջ��Ԫ��*/
char precede(char a,char b);						/*�ȽϷ������ȼ�*/
int IsNum(char c);									/*�ж��Ƿ�������*/
double TurnToDouble(char *expression,int *ptr_i);	/*���ַ����е�����ת��Ϊ������*/
ElemType Operate(ElemType a,char c,ElemType b);		/*����*/
ElemType Evaluate_Expression(char *expression);		/*������*/ 

/*------------������------------*/
int main()
{
	ElemType result;
	char oper1,expression[MAX_LEN];
	int i=0;
	printf("���ʽ�ļ�����#����!\n");
	printf("��������ʽ(֧�ָ�����)��");
	gets(expression);
	result = Evaluate_Expression(expression);
	system("cls");
	printf("���ʽ���Ϊ��"); 
	for(i=0;i<strlen(expression)-1;i++)
		printf("%c",expression[i]);
	printf(" = %f\n",result);
	return 0;
}
/*-------------END-------------*/

/*------------��������------------*/

/*����һ��������ݵ�˳��ջ*/
NumStack Create_OPND()
{
	NumStack OPND;
	OPND = (NumStack)malloc(sizeof(Num_Stack));
	OPND->top = -1;
	return OPND;
}

/*����һ������������˳��ջ*/
OperStack Create_OPTR()
{
	OperStack OPTR;
	OPTR = (OperStack)malloc(sizeof(Oper_Stack));
	OPTR->top = -1;
	return OPTR;
}

/*ѹ��OPND*/
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

/*ѹ��OPTR*/
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

/*��OPND����ջ��Ԫ��*/
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

/*��OPTR����ջ��Ԫ��*/
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

/*��ȡOPNDջ��Ԫ��*/
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

/*��ȡOPTRջ��Ԫ��*/
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

/*�ȽϷ������ȼ�*/
char precede(char a,char b)
{
	int i=0,j=0;
 	
 	while(sign[i]!=a) i++;
 	while(sign[j]!=b) j++;
 	return (prec[i][j]);
}

/*�ж��Ƿ�������*/
int IsNum(char c)
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}

/*���ַ����е�����ת��Ϊ������*/ 
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

/*����������*/ 
ElemType Operate(ElemType a,char theta,ElemType b)
{
	ElemType num;
    switch (theta)
    {
		case '+': 	num=a+b;break;
	 	case '-': 	num=a-b;break;
	 	case '*': 	num=a*b;break;
	 	case '/': 	num=a/b;break;
	 	default:	printf("������������\n");return;
    }
    return num;
}

/*������*/
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

