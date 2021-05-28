#include <stdio.h>
#define N 20
int main(void){
	int i=0,j,m;
	char a[N],c;
	
	printf("Enter a first and last name: ");
	while((c = getchar())!='\n'){
		a[i] = c;
		if (c == ' ')
			m = i;
		i++;
	}
	
	printf("You enered the name:");
	for(j=m+1;j<i;j++){
		printf("%c",a[j]);
	}
	printf(", %c.",a[0]);
	return 0;
}
