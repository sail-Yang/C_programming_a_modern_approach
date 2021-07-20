#include <stdio.h>
#include <string.h>

int main(){
	char *shiwei[]={"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char *num[]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	int a;
	printf("Enter a two-digit number(0~99): ");
	scanf("%d", &a);
	if(a<=19&&a>=0)
		printf("You entered the number:%s",num[a]);
	else if (a>19&&a<=99)
		if(a%10 != 0)
			printf("You entered the number:%s-%s",shiwei[a/10-2],num[a%10]);
		else
			printf("You entered the number:%s",shiwei[a/10-2]);
	else
		printf("Input erroe!");
	
	return 0;
}
