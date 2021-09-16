#include <stdio.h>
#include <string.h>
#define LEN 20
int main(){
	char word[LEN+1],smallest_word[LEN+1]="",largest_word[LEN+1]="",ch;
	int count=0;
	do{
		printf("Enter a word:	"); 
		gets(word);
		if (strlen(word)!=4)
			if(strcmp(word,smallest_word) < 0||count == 0)
				strcpy(smallest_word,word);
			else if(strcmp(largest_word,word) < 0)
				strcpy(largest_word,word);
			else
				continue;
		count++;
	}while(strlen(word)!=4);
	printf("Samllest word:	%s\n",smallest_word);
	printf("Largest word:	%s\n",largest_word);
	return 0;
}
