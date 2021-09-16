#include <stdio.h>

int main(void){
	printf("Enter number of days in month:");
	int days,start;
	scanf("%d",&days);
	printf("Enter starting day of the week:(1 = Sun,7 = Sat)");
	scanf("%d",&start);
	int i;
	for (i = 1;i<start;i++){
		printf("   ");
	}
	int count,date;
	date = 7;
	for(count=1;count<=days;count++){
		if(count<10){
			printf(" %d ",count);
		} else{
			printf("%d ",count);
		}
		
		if (count == (date - start+1)){
			printf("\n");	
		}else{
			continue;
		}
		date = date+7;
	}
	return 0; 
}
