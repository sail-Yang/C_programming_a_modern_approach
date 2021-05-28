#include <stdio.h>
#include <ctype.h>
#define N 15

int main(){
	char a[N],c;
	int i=0,j;
	
	printf("Enter phone number:");
	while((c = getchar()) != '\n'){
		c = toupper(c);
		switch (c) {
			case 65:case 66:case 67:c = '2';break;
			case 68:case 69:case 70:c = '3';break;
			case 71:case 72:case 73:c = '4';break;
			case 74:case 75:case 76:c = '5';break;
			case 77:case 78:case 79:c = '6';break;
			case 80:case 81:case 82:c = '7';break;
			case 83:case 84:case 85:c = '8';break;
			case 86:case 87:case 88:c = '9';break;
		}
		a[i] = c;
		i++;
	}
	printf("In numeric form:");
	for(j=0;j<i;j++){
		printf("%c",a[j]);
	}
	return 0;
}

