#include <stdio.h>
int main(void)
{
	float num,max;
	max = 0;
	do {
		printf("Enter a number:");
		scanf("%f",&num);
		if (num>=max){
			max = num;
		}
		else
			;		
	}while(num>0);
	printf("The largest number entered was %f",max);
	return 0;
	
}
