/*compute 3x^5+2x^4-5x^3-x^2+7x-6*/
#include <stdio.h>
#include <math.h>

float poly(float x){
	float sum;
	sum = 3*pow(x,5)+2*pow(x,4)-5*pow(x,3)-pow(x,2)+7*x-6;
	return sum;
}
int main(){
	float x,sum;
	printf("Enter x:");
	scanf("%f",&x);
	sum = poly(x);
	printf("The result is %f",sum);
	return 0;
} 
