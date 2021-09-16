#include <stdio.h>

int main(void){
	printf("Enter a sentence:");
	char ch;
	int sum;
	while ((ch = getchar()) != '\n'){
		ch = toupper(ch); 
		if (ch =='A'||ch == 'E'||ch == 'I'||ch == 'O'||ch == 'U'){
			sum +=1;
		}else{
			continue;
		}
	}
	printf("Your sentence contains %d vowels",sum);
	return 0;
}
