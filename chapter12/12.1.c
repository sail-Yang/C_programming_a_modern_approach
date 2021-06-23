#include <stdio.h>
#define N 20
int main(void){
	char mes[N],*p,ch;
	p = mes;
	while((ch=getchar())!= '\n'&&p<mes+N){
		*p++ = ch;
	}
	for (p=mes+N-1;p>=mes;p--){
		printf("%c",*p);
	}
	printf("\n"); 
	return 0;
}
