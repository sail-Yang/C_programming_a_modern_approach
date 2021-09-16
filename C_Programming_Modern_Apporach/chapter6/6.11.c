#include <stdio.h>
int main(void){
	printf("Enter the n:");
	int n;
	float e;
	e = 1.00;
	scanf("%d",&n);
	int i;
	for (i = 1;i<=n;i++){
		e = e + 1.00f/(1.00f*i);
	}
	printf("%f",e);
	return 0;
}
