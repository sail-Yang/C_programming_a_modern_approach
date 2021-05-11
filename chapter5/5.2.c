#include <stdio.h>
int main(void)
{
	printf("Enter a 24-hour time :");
	int hour1,min,hour2;
	scanf("%d:%d",&hour1,&min);
	if (hour1 <= 12&&hour1 >=0){
		hour2 = hour1;
		printf("Equivalent 12-hour time: %d:%.2d AM",hour2,min);
	}else if(hour1 < 24&&hour1 >= 13) {
		hour2 = hour1-12;
		printf("Equivalent 12-hour time: %d:%.2d PM",hour2,min);
	}else if (hour1 ==24&&min>0){
		hour2 = 0;
		printf("Equivalent 12-hour time: %d:%.2d AM",hour2,min);	
	}else if (hour1 == 24 && min==0){
		hour2 = 12;
		printf("Equivalent 12-hour time: %d:%.2d AM",hour2,min);
	}
	else{
		printf("Input has faults.");
	}
	return 0;
 } 
