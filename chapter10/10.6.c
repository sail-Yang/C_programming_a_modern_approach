#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define STACK_SIZE 100
int top = 0;	
int contents[STACK_SIZE];
void make_empty(void)
{
	top = 0;
}
bool is_empty(void){
	return top == 0;
}
bool is_full(void)
{ 
	return top==STACK_SIZE;}

bool push(int i){
	if(is_full()){
		printf("Expression is too complex");
		return false;
	}
	else {
		contents[top++]=i;
		return true;
	}
}
	int pop(void){
		
	if(is_empty())
	return contents[0];
	else return contents[top--];}//弹出contens[top--]那个数据


	int main(void)
	{
	printf("输入运算:");
	char ch;
	int ch1;
	int x,y,i=0,o;
	while((ch=getchar())!='\n')
	{
		if(ch>='0'&&ch<='9')
		{     ch1=ch-48;
			o=push(ch1);
			if(o==false)
				return 0;	 
		}
		else {
			switch(ch){
			case '+':
				top--;
				if(top==0){
					printf("Not enough operands in expression");
					i++;break;}
				else
				{y=pop();}
				if(top==0){
					x=pop();}
				else { x=pop();
				top++;}
				push((x+y));
			
						
			break;
			case '-':
				top--;
				y=pop();
				if(top==0){
					x=pop();}
				else { x=pop();
				top++;}
				push((x-y));
			break;
			case '*':top--;
				y=pop();
				if(top==0){
					x=pop();}
				else { x=pop();
				top++;}
				push((x*y));
			break;
			case '/':top--;
				y=pop();
				if(top==0){
					x=pop();}
				else { x=pop();
				top++;}
				push((x/y));
					   
			break;
			default:
				break;
			}
		}}
	if(i==0)
	printf("%d\n",contents[0]);
	else 
	return 0;
	}

