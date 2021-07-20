#include <stdio.h>
#define MAX_DIGITS 10

char digits[3][MAX_DIGITS*4];
char segments[50];

void clear_digits_array(void);
void process_digit(int digit,int position);
void print_digits_array(void); 

int main(){
	int digit,position,k=0,pos;
	char num;
	clear_digits_array();
	printf("Enter a number:"); 
	while ((num = getchar()) != '\n')
    {
    	if (47 < num && num < 58){
    		pos = k+k*3;
			process_digit(num,pos);
    		k++;
    	}
    	else
    		continue;
    }
	print_digits_array();	
	return 0;
}

void clear_digits_array(void){
	int i=0,j=0;
	for (i=0;i<3;i++){
		for (j=0;j<MAX_DIGITS*4;j++){
			digits[i][j]='\0';
		}
	}
}

void process_digit(int digit,int position){
	switch(digit){
		case '0':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='\0';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='|';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;	
		case '1':
			digits[0][position]='\0';
			digits[0][position+1]='\0';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='\0';
			digits[1][position+1]='\0';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='\0';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '2':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='\0';
			digits[1][position+1]='_';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='|';
			digits[2][position+1]='_';
			digits[2][position+2]='\0';
			digits[2][position+3]='\0';
			break;
		case '3':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='\0';
			digits[1][position+1]='_';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '4':
			digits[0][position]='\0';
			digits[0][position+1]='\0';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='_';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='\0';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '5':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='_';
			digits[1][position+2]='\0';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '6':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='_';
			digits[1][position+2]='\0';
			digits[1][position+3]='\0';
			digits[2][position]='|';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '7':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='\0';
			digits[1][position+1]='\0';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='_\0';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '8':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='_';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='|';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		case '9':
			digits[0][position]='\0';
			digits[0][position+1]='_';
			digits[0][position+2]='\0';
			digits[0][position+3]='\0';
			digits[1][position]='|';
			digits[1][position+1]='_';
			digits[1][position+2]='|';
			digits[1][position+3]='\0';
			digits[2][position]='\0';
			digits[2][position+1]='_';
			digits[2][position+2]='|';
			digits[2][position+3]='\0';
			break;
		default:
			break;
	}
}

void print_digits_array(void){
	int i=0,j=0;
	for (i=0;i<3;i++){
		for (j=0;j<MAX_DIGITS*4;j++){
			if(j==MAX_DIGITS*4-1){
				printf("%c",digits[i][j]);
				printf("\n");
			}else{
				printf("%c",digits[i][j]);
			}
		}
	}
}
