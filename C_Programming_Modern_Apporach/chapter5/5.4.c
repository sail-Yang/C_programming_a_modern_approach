#include <stdio.h>

int main(void)
{
	int v;
	printf("Enter the speed of wind(nautical mile/hour):");
	scanf("%d",&v);
	
	if (v < 1){
		printf("Calm\n");
	}else if (v>=1&&v<=3){
		printf("Light air\n");
	}else if (v>=3&&v<=27){
		printf("Breeze\n");
	}else if (v>=28&&v<=47){
		printf("Gale\n");
	}else if (v>=48&&v<=63){
		printf("Storm\n");	}else{
		printf("Hurricane\n");
	}
	return 0;
}
