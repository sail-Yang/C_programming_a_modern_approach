#include <stdio.h>

int main(void){
	printf("Enter a positive integer:");
	int i,m;
	scanf("%d",&i);
	short all=1;
	
	for (m = 1;m <=i;m++){
		all = all*m;
	}
	printf("Factorial of %d: %hd",i,all);
	return 0;
}
