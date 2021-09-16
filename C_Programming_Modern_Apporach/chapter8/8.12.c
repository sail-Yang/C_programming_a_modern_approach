#include <stdio.h>
#include <ctype.h>

int main(){
	const int a[26]={1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	int i,sum=0;
	char c;
	printf("Enter a word:");
	
	while((c = getchar())!= '\n'){
		c = toupper(c);
		sum += a[c-'A'];
	}
	printf("Scrabble value:%d",sum);
	return 0;
}
