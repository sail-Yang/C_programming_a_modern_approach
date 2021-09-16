/*用牛顿法计算正浮点数的平方根*/ 
#include <stdio.h>
#include <math.h>

int main(void){
	double x,i=0,y=1;
	printf("Enter a positive number:");
	scanf("%lf",&x);
	
	while(fabs(i-y)>=(0.00001*y)){
		i=y;
		y = x/y;
		y = (y+i)/2.00f;
		
	}
	printf("Square root:%.5f",y);
	return 0;
} 
