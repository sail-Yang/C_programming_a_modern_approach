#include <stdio.h>

int main(void)
{
	printf("Enter a date (mm/dd/yyyy): ");
	int month,days,year;
	scanf("%d/%d/%d",&month,&days,&year);
	printf("You enter the date %d%.2d%d",year,month,days);
	
	return 0;
 } 
