#include <stdio.h>

int main(void){
	int i,a[10],*p,*q;
	for(i=0;i<10;i++){
		a[i]=i;
	}
	p = &a[0];
	q = p+6;
	p+=6;
	printf("%d",*q);
	return 0;
} 
