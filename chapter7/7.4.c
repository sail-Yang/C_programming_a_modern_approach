#include <stdio.h>

int main(void){
	printf("Enter a phone number:");
	int str;
	do{
		str = getchar();
		if (str == 'A'|| str == 'B' || str == 'C'){
			printf("2"); 
		}else if(str=='D'||str == 'E'||str == 'F'){
			printf("3");
		}else if(str == 'G'|| str == 'H'|| str == 'I'){
			printf("4");
		}else if(str == 'J'|| str == 'K'|| str == 'L'){
			printf("5");
		}else if(str == 'M'|| str == 'N'|| str == 'O'){
			printf("6");
		}else if(str == 'P'|| str == 'R'|| str == 'S'){
			printf("7");
		}else if(str == 'T'|| str == 'U'|| str == 'V'){
			printf("8");
		}else if(str == 'W'|| str == 'X'|| str == 'Y'){
			printf("9");
		}else{
			printf("%c",str);
		}
	}while(str != '\n');
	return 0;
}
