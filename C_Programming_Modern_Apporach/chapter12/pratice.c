#include <stdio.h>
#define N 10
int main(void)
{
	int *e,i=1;
	int a[10];
	
	for (e=a;e<a+10;e++)
	{
		*e = i;
		i++;
	}
	int *p = &a[0],*q = &a[N-1],temp;	
	
	while(p<q){
		temp = *p;
		*p++ = *q;
		*q-- = temp;
	}
	for (e=a;e<a+10;e++)
		printf("%d ",*e);
    return 0;
}
