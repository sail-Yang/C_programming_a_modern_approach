#include <stdio.h>

int main(void){
	printf("Enter first date (mm/dd/yyyy):");
	int m1,d1,y1;
	scanf("%d/%d/%d",&m1,&d1,&y1);	
	printf("Enter second date (mm/dd/yyyy):");
	int m2,d2,y2;
	scanf("%d/%d/%d",&m2,&d2,&y2);
	
	if (y1<y2){
		printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m1,d1,y1,m2,d2,y2);
	}else if(y1 == y2){
		if (m1<m2){
			printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m1,d1,y1,m2,d2,y2);
		}else if (m1==m2){
			if (d1 < d2){
				printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m1,d1,y1,m2,d2,y2);
			}else{
				printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m2,d2,y2,m1,d1,y1);
			}
		}else{
			printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m2,d2,y2,m1,d1,y1);
		}
	}else{
		printf("%d/%d/%.4d is earlier than %d/%d/%.4d",m2,d2,y2,m1,d1,y1);
	}
	return 0;
}
