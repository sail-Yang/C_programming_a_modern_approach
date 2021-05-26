#include <stdio.h>
#define N 10;
int main(){
	int a[10],digit,i;
	long n;
	for(i = 0; i < 10; i++)
		a[i] = 0;
	
	printf("Enter a number:\t  ");
	scanf("%ld",&n);
	
	while(n>0){
		digit = n%10;
		a[digit] = a[digit]+1;
		n /= 10;
	}
	
	printf("Digit:\t\t");
	for (i = 0;i < 10;i++){
		printf("%3d",i);
	}
	printf("\n");
	printf("Occurrences:\t");
	for (i = 0;i < 10;i++){
		printf("%3d",a[i]);
	}
	return 0;
}
