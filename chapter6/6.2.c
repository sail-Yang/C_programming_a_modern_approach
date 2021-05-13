#include <stdio.h>

int main(void)
{
	printf("Enter two integers:");
	int m,n;
	int i; /* 存放中间变量 */ 
	scanf("%d%d",&m,&n);
	while (n!=0){
		i = n;
		n = m%n;
		m = i;
	}
	printf("Greast common divisor:%d",m);
 } 
