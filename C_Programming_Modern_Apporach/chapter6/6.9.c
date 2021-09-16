#include <stdio.h>

int main(void){
	printf("Enter amount of loan:");
	float loan,rate,left,pay;
	scanf("%f",&loan);
	printf("Enter interst rate:");
	scanf("%f",&rate);
	printf("Enter monthly payment:");
	scanf("%f",&pay);
	int time;
	printf("Enter the times of paying:");
	scanf("%d",&time);
	
	int i;
	left = loan;
	for(i=1;i<=time;i++){
		left = left - pay + left*(rate*0.01f/12.00f);
		printf("Balance remaining after %d time payment:&%.2f\n",i,left);
	}
	return 0;
	
	
}
