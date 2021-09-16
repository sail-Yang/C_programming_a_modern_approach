#include <stdio.h>
int main(void)
{
	printf("Enter a number between 1 and 32767:");
	int data;
	scanf("%d",&data);
	
	int a,b,c,d,e;
	e = data % 8;
	d = (data / 8)%8;
	c = (data / 8/8)%8;
	b = (data/8/8/8)%8;
	a = (data/8/8/8/8)%8;
	
	printf("In octal,your number is:%1d%1d%1d%1d%1d\n",a,b,c,d,e);
	printf("the true number is %o",data);
	
	return 0;
}
