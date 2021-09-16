#include <stdio.h>
#define N 5
int main(){
	int row1[N],row2[N],row3[N],row4[N],row5[N],i;
	/*input row1*/
	printf("Enter row 1:\t");
	for (i = 0;i < N;i++){
		scanf("%d",&row1[i]);
	}
	/*input row2*/
	printf("Enter row 2:\t");
	for (i = 0;i < N;i++){
		scanf("%d",&row2[i]);
	}
	/*input row3*/
	printf("Enter row 3:\t");
	for (i = 0;i < N;i++){
		scanf("%d",&row3[i]);
	}
	/*input row5*/
	printf("Enter row 4:\t");
	for (i = 0;i < N;i++){
		scanf("%d",&row4[i]);
	}
	/*input row5*/
	printf("Enter row 5:\t");
	for (i = 0;i < N;i++){
		scanf("%d",&row5[i]);
	}
	
	/*row totals*/
	int n,row_sum[N],col_sum[N],sum1=0;
	for (n = 0;n<5;n++){
		switch (n)
		{
			case 0:{
				for (i=0;i<N;i++){
					sum1 = sum1 + row1[i];
				}
				row_sum[0] = sum1;
				sum1 = 0;
				break;
			}
			case 1:{
				for (i=0;i<N;i++){
					sum1 = sum1 + row2[i];
				}
				row_sum[1] = sum1;
				sum1 = 0;
				break;
			}
			case 2:{
				for (i=0;i<N;i++){
					sum1 = sum1 + row3[i];
				}
				row_sum[2] = sum1;
				sum1 = 0;
				break;
			}
			case 3:{
				for (i=0;i<N;i++){
					sum1 = sum1 + row4[i];
				}
				row_sum[3] = sum1;
				sum1 = 0;
				break;
			}
			case 4:{
				for (i=0;i<N;i++){
					sum1 = sum1 + row5[i];
				}
				row_sum[4] = sum1;
				sum1 = 0;
				break;
			}
		}
	}
	printf("Row totals:\t");
	for (i = 0;i<N;i++){
		printf("%d ",row_sum[i]);
	}
	printf("\n");
	/*column sum*/
	for (i=0;i<N;i++){
		col_sum[i] = row1[i]+row2[i]+row3[i]+row4[i]+row5[i];
	}
	printf("Column totals:\t");
	for (i = 0;i<N;i++){
		printf("%d ",col_sum[i]);
	}
	return 0;
}
