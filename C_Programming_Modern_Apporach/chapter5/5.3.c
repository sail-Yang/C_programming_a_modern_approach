/* Calculates a broker's commission */

#include <stdio.h>
int main(void)
{
	float commission1,num,price,value;
	
	printf("Enter numbers of stock:");
	scanf("%f",&num);
	printf("\n");
	
	printf("Enter price of stock:");
	scanf("%f",&price);
	value = price * num;
	
//below 是经纪人的佣金计算 
	if (value<2500.00f)
		commission1 = 30.00f + .017f *value;
	else if (value < 6250.00f)
		commission1 = 56.00f + .0066f*value;
	else if (value < 20000.00f)
		commission1 = 76.00f + .0034f*value;
	else if (value < 50000.00f)
		commission1 = 100.00f + .0022f*value;
	else if (value < 500000.00f)
		commission1 = 155.00f + .0011f*value;
	else
		commission1 = 255.00f + .0009f*value;
		
	if (commission1 < 39.00f)
		commission1 = 39.00f;

//below 是经纪人对手的佣金计算
	float commission2;
	if (value<2000.00f){
		commission2 = num * (33.00f+3.00f/100.00f);
	}else {
		commission2 = num * (33.00f+2.00f/100.00f);
	}
	printf("Commission1 : $%.2f\n",commission1);
	printf("Commission2 : $%.2f\n",commission2);
	return 0;
 } 
