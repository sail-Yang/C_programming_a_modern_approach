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
	
	/*���������鵹����,ѧ������*/
	char temp,*e = &mes[0],*q = &mes[N-1];
	while (e<q){
		temp = *e;
		*e++ = *q;
		*q-- = temp;
	}
	/*�������*/
	for (e = mes;e<mes + N;e++)
		printf("%c",*e); 
	return 0;
}
