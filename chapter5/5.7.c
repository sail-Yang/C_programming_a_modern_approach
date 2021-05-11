#include <stdio.h>

int main(void)
{
	printf("Enter four integers:");
	int num1,num2,num3,num4;
	int max,min;
	scanf("%d %d %d %d",&num1,&num2,&num3,&num4);
	if(num1>=num2&&num1>=num3&&num1>=num4){
		max = num1;
		if (num2<=num3&&num2<=num4){
			min=num2;
		}else if(num3<=num2&&num3<=num4){
			min=num3;
		}else{
			min = num4;
		}
	}else if (num2>=num1&&num2>=num3&&num2>=num4){
		max = num2;
		if (num1<=num3&&num1<=4){
			min = num1;
		}else if(num3<=num1&&num3<=num4){
			min = num3;
		}else {
			min = num4;
		}
	}else if (num3>=num1&&num3>=num2&&num3>=num4){
		max = num3;
		if (num1<=num2&&num1<=4){
			min = num1;
		}else if(num2<=num1&&num2<=num4){
			min = num2;
		}else {
			min = num4;
		}
	}else if (num4>=num1&&num4>=num2&&num4>=num3){
		max = num4;
		if (num1<=num2&&num1<=3){
			min = num1;
		}else if(num2<=num1&&num2<=num3){
			min = num2;
		}else {
			min = num3;
		}
	}
	printf("Largest: %d\n",max);
	printf("Smallest: %d\n",min);
	return 0;
}
