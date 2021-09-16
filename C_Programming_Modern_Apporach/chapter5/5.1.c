#include <stdio.h>
int main(void)
{
	printf("Enter a number:");
	int num,digit;
	scanf("%d",&num);
	if (num<=9&&num>=-9)
	{
		digit = 1;
		printf("The number %d has %d digits",num,digit);
	}else if ((num<=99&&num>=10)||(num>=-99&&num<=-10)){
		digit = 2;
		printf("The number %d has %d digits",num,digit);
	}else if ((num<=999&&num>=100)||(num>=-999&&num<=-100)){
		digit = 3;
		printf("The number %d has %d digits",num,digit);
	}else if ((num<=9999&&num>=1000)||(num>=-9999&&num<=-1000)){
		digit = 4;
		printf("The number %d has %d digits",num,digit);
	}else{
		printf("the range is from -9999~9999");
	}
	return 0;
 } 
