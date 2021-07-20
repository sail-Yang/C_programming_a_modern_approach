#include <stdio.h>
#define N 20
int main(void){
	char mes[N],*p,ch;
	p = mes;
	while((ch=getchar())!= '\n'&& p<mes+N){
		*p++ = ch;
	}
	
	/*  
	for (p=mes+N-1;p>=mes;p--){
		printf("%c",*p);
	}
	printf("\n");*/
	
	/*把整个数组倒过来,学以致用*/
	char temp,*e = &mes[0],*q = &mes[N-1];
	while (e<q){
		temp = *e;
		*e++ = *q;
		*q-- = temp;
	}
	/*输出数组*/
	for (e = mes;e<mes + N;e++)
		printf("%c",*e); 
	return 0;
}
