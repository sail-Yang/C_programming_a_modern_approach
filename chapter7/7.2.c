#include <stdio.h>

int main(void){
	int i,n;
	printf("This program prints a table of squares.\n");
	printf("Enter number of entries in table:\n");
	scanf("%d",&n);
	int str1;
	getchar();/*用以接受scanf中的\n，如果没有这一行，下面到24的时候会直接跳过。*/ 
	
	for (i = 1;i<=n;i++){
		if (i % 24 == 0){
			printf("Press Enter to continue...\n");
			str1 = getchar();
			if (str1=='\n'){
				printf("%10d%10d\n",i,i*i);
				continue; 
			}else{
				break;
			}
		}else{
			printf("%10d%10d\n",i,i*i);
		}
	}
	
	return 0;
}
