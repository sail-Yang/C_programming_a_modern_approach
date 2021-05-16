#include <stdio.h>
#include <ctype.h.>
int main(void){
	printf("Enter a word:");
	int str;
	int sum=0; 
	do{
		str = getchar();
		str = tolower(str);
		if (str == 'a'||str == 'e'||str == 'i'||str == 'l'||str == 'n'||str == 'o'||str == 'r'||str == 's'||str == 't'||str == 'u'){
			sum += 1;
		}else if(str == 'd'||str == 'g'){
			sum += 2;
		}else if(str == 'b'||str == 'c'||str == 'm'||str == 'p'){
			sum += 3;
		}else if(str == 'f'||str == 'h'||str == 'v'||str == 'w'||str == 'y'){
			sum += 4;
		}else if(str == 'k'){
			sum += 5;
		}else if(str == 'j'||str == 'x'){
			sum += 8;
		}else if(str == 'q'||str == 'z'){
			sum += 10;
		}else {
			continue;
		}
		
	}while(str != '\n');
	printf("Scrabble value:%d",sum);
	return 0;
}
