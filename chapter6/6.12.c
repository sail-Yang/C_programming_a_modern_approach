#include <stdio.h>

int main(void){
	float e,ep;
	int i;
	e =1;
	printf("Enter epsilon :");
	scanf("%f",&ep);
	for(i=1;;i++){
		if (e<=ep){
			e = e + 1.00f/(1.00f*i);
		}else{
			break;
		}
	} 
	printf("%f",e);
	return 0;
}
