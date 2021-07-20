#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones);
int main(){
	int dollars,twenties,tens,fives,ones;
	printf("Enter a dollar amount:");
	scanf("%d",&dollars);
	pay_amount(dollars,&twenties,&tens,&fives,&ones);
	/*output*/
	printf("$20\tbills:%d\n",twenties);
	printf("$10\tbills:%d\n",tens);
	printf("$5\tbills:%d\n",fives);
	printf("$1\tbills:%d\n",ones);
	return 0;
}
void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones){
	*twenties = dollars / 20;
	*tens = dollars%20/10;
	*fives = dollars%20%10/5;
	*ones = dollars%20%10%5;
} 
