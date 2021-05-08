#include <stdio.h>

int main(void)
{
	printf("Enter two fractions separated by a plus sign:");
	int num1,denom1,num2,denom2;
	scanf("%d/%d+%d/%d",&num1,&denom1,&num2,&denom2);
	int num3,denom3; 
	num3 = num1*denom2+num2*denom1;
	denom3 = denom2*denom1;
	 
	printf("The sum is %d/%d",num3,denom3);
	printf("%.5d",23);
	return 0;
	
}
