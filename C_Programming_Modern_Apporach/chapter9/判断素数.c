/*判定素数*/
#include <stdio.h>
#include <stdbool.h>

/*这里用了函数声明*/
bool is_prime(int n);


int main(void){
	int n;
	
	printf("Enter a number:");
	scanf("%d",&n);
	if(is_prime(n))
		printf("Prime\n");
	else
		printf("Not prime\n");
		
	return 0;	
} 

bool is_prime(int n)
{
	int divisor;
	if (n<=1)
		return false;
	for (divisor = 2;divisor * divisor <=n;divisor++)
		if (n%divisor == 0)
			return false;
	return true;
}
