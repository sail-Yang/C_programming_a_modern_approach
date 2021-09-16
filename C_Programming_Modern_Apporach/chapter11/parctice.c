#include <stdio.h>

int main(){
	int j,*p=&j;
	j = 13;
	printf("%p\n",p);
	return 0;
} 
