#include <stdio.h>
#define N 10
int main(){
	int i,digit,a[N];
	long n;
	
	printf("Enter a number:");
	scanf("%ld",&n);
	for (i = 0;i< N;i++){
		a[i] = 0;
	}
	while(n>0){
		while (n>0){
		digit = n % 10;
		a[digit]++;
		n /= 10;	
		}
		for (i = 0;i<N;i++){
			if (a[i]!=0){
				printf("%2d",i);
			}
		}
		printf("\nEnter a number:");	/*���濪ʼ��һ������*/
		scanf("%ld",&n);
		for (i = 0;i< N;i++){			/*��������*/ 
			a[i] = 0;
		}
	}
	return 0;
}
