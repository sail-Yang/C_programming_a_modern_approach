#include <stdio.h>

int main(void){
	char c,end,a[30];
	int i=0,j=0,m=0;
	
	printf("Enter a sentence:");
	/*ÊäÈë*/
	while((c = getchar())!='\n'){
		a[i]=c;
		if (c == '.'||c == '!'||c=='?'){
			end = c;
		}
		i++;
	}
	
	printf("Reversal of sentence:");
	for(j=i-2;j>=0;j--){
		m = j;
		if(a[m]==' '||m==0){
			do{
				printf("%c",a[m]);
				m++;
				
			}while(a[m]!=' '&&a[m]!=end);
			printf(" ");
		}
		
	}
	printf("%c",end);
	/*
	for(j=0;j<i;j++){
		printf("%c",a[j]);
	}
	printf("%d",i);*/
	return 0;
}
