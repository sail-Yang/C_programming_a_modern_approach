#include <stdio.h>

int main(void){
	printf("Enter an expression:");
	char ch1,ch2;
	float num1,num2,num3,n1,n2;
	scanf("%f%c%f%c%f",&num1,&ch1,&num2,&ch2,&num3);
	switch (ch1){
		case '+':n1 = num1 + num2;break;
		case '-':n1 = num1 - num2;break;
		case '*':n1 = num1 * num2;break;
		case '/':n1 = num1 / num2;break;
	}
	switch (ch2){
		case '+':n2 = n1 + num3;break;
		case '-':n2 = n1 - num3;break;
		case '*':n2 = n1 * num3;break;
		case '/':n2 = n1 / num3;break;
	}
	printf("Value of expression:%f",n2);
	return 0;
}
