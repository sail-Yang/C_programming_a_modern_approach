/*U.S. tax calculation*/
#include <stdio.h>

int main(void)
{
	printf("Enter your income:");
	float income,tax;
	scanf("%f",&income);
	if (income<750){
		tax = income*0.01f;
	}else if(income>=750&&income<2250){
		tax = 7.50f+(income-750.00f)*0.02f;
	}else if(income>=2250&&income<3750){
		tax = 37.50f+(income-2250.00f)*0.03f;
	}else if(income >=3750&&income<5250){
		tax = 82.50f+(income-3750.00f)*0.04f;
	}else if(income >=5250&&income<7000){
		tax = 142.50f+(income-5250.00f)*0.05f;
	}else{
		tax = 230.00f+(income-7000.00f)*0.06f;
	}
	printf("The tax is :$%.2f",tax); 
	return 0;
}
