#include <stdio.h>

int main(void)
{
	int item,mm,dd,yyyy;
	printf("Enter item number:");
	scanf("%d",&item); 
	
	float price;
	printf("Enter unit price:");
	scanf("%f",&price);
	
	printf("Enter purchase date (mm/dd/yyyy):");
	scanf("%d/%d/%d",&mm,&dd,&yyyy);
	
	printf("Item\tUnit\t\tPuechase\n");
	printf("\tPrice\t\tDate\n");
	printf("%d\t$ %.2f\t\t%d/%.2d/%.4d",item,price,mm,dd,yyyy);
	return 0;
}
