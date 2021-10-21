/*�����2003 � 201205130 ��ջ��*/
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
typedef struct num
{
	ElemType data;
	struct num *next;
}Num,*Number;

typedef struct numstack
{
	Number top;
	int len;
}Num_Stack,*NumStack;

/*OPTR*/
typedef struct oper
{
	char opera;
	struct oper *next;
}Oper,*Operator;

typedef struct operstack
{
	Operator top;
	int len;
}Oper_Stack,*OperStack;

/*��������*/
NumStack Create_OPND();								/*����һ��������ݵ���ջ*/ 
OperStack Create_OPTR();							/*����һ����ŷ��ŵ���ջ*/
void Push_Num(NumStack OPND,ElemType data1);		/*ѹ��OPND*/
void Push_Oper(OperStack OPTR,char opera1);			/*ѹ��OPTR*/
ElemType Pop_Num(NumStack OPND);					/*��OPND����ջ��Ԫ��*/
char Pop_Oper(OperStack OPTR);						/*��OPTR����ջ��Ԫ��*/
ElemType GetNumTop(NumStack OPND);					/*��ȡOPNDջ��Ԫ��*/
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
/*����һ��������ݵ���ջ*/ 
NumStack Create_OPND()
{
	NumStack OPND;
	OPND = (NumStack)malloc(sizeof(Num_Stack));
	OPND->len = 0;
	OPND->top = NULL;
	return OPND;
}

/*����һ����ŷ��ŵ���ջ*/
OperStack Create_OPTR()
{
	OperStack OPTR;
	OPTR = (OperStack)malloc(sizeof(Oper_Stack));
	OPTR->len = 0;
	OPTR->top = (Operator)malloc(sizeof(Oper));
	OPTR->top->next = NULL;
	return OPTR;
}

/*ѹ��OPND*/
void Push_Num(NumStack OPND,ElemType data1)
{
	Number Num1;
	Num1 = (Number)malloc(sizeof(Num));
	Num1->data = data1;
	Num1->next = OPND->top;
	OPND->top = Num1;
	OPND->len++;
	return;
}

/*ѹ��OPTR*/
void Push_Oper(OperStack OPTR,char opera1)
{
	if(OPTR->len == 0)
	{
		OPTR->top->opera = opera1;
		OPTR->len++;
		return;
	}
	Operator Oper1;
	Oper1 = (Operator)malloc(sizeof(Oper));
	Oper1->opera = opera1;
	Oper1->next = OPTR->top;
	OPTR->top = Oper1;
	OPTR->len++;
	return;
}

/*��OPND����ջ��Ԫ��*/
ElemType Pop_Num(NumStack OPND)
{
	ElemType data1;
	if(OPND->len == 0)
	{
		printf("Empty Stack!Can't pop!\n");
		return;
	}
	data1 = OPND->top->data;
	Number Num1;
	Num1 = OPND->top;
	OPND->top = Num1->next;
	free(Num1);
	Num1 = NULL;
	OPND->len--;
	return data1;
}

/*��OPTR����ջ��Ԫ��*/
char Pop_Oper(OperStack OPTR)
{
	char theta;
	if(OPTR->len == 0)
	{
		printf("Empty Stack!Can't pop!\n");
		return;
	}
	theta = OPTR->top->opera;
	Operator Oper1;
	Oper1 = OPTR->top;
	OPTR->top = Oper1->next;
	free(Oper1);
	Oper1 = NULL;
	OPTR->len--;
	return theta;
}

/*��ȡOPNDջ��Ԫ��*/
ElemType GetNumTop(NumStack OPND)
{
	return OPND->top->data;
}


/*��ȡOPTRջ��Ԫ��*/
char GetOperTop(OperStack OPTR)
{
	return OPTR->top->opera;
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
	char str_result[100];
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
	ElemType a,b,k,num1;
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

