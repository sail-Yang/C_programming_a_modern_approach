#include <stdio.h>

int main(void){
	printf("Enter a number:");
	int num,result,i;
	scanf("%d",&num);
	for (i=1;i<=num;++i){
		if ((i+1)%2 !=0){
			printf("%d\n",i*i);
		}else{
			;
		}
	}
	return 0;
} 
