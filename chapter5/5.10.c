#include <stdio.h>

int main(void){
	printf("Enter numerical grade:");
	int grade,num;
	scanf("%d",&grade);
	num = grade /10;
	switch (num){
		case 6:printf("Letter grade : D");break;
		case 7:printf("Letter grade : C");break;
		case 8:printf("Letter grade : B");break;
		case 9:printf("Letter grade : A");break;
		case 10:printf("Letter grade : A");break;
		default :printf("Letter grade : F");break;
	}
	return 0;
}
