#include <stdio.h>
#include <ctype.h>

int main(){
	int i,n = 0;
	char a[50],c; /*这里有个问题，就是不知道该定义数组为多长*/
	
	while ((c = getchar()) != '\n'){
		a[n] = toupper(c);
		n++;
	}
	for(i = 0;i< n;i++){
		switch (a[i])
		{
			case 'A':a[i]='4';break;
			case 'B':a[i]='8';break;
			case 'E':a[i]='3';break;
			case 'I':a[i]='1';break;
			case 'O':a[i]='0';break;
			case 'S':a[i]='5';break;
			
		}
	}
	printf("In BIFF-speak: ");
	for (i = 0;i < n;i++){
		printf("%c",a[i]);
	}
	printf("!!!!!!!!!!");
	return 0;
}
