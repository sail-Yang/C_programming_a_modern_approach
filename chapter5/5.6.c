#include <stdio.h>
int main(void)
{
	printf("Enter the 12 digits of a UPC(x xxxxx xxxxx x):");
	int i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12;
	scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d",&i1,&i2,&i3,&i4,&i5,&i6,&i7,&i8,&i9,&i10,&i11,&i12);
	int first_sum,second_sum,total,result;
	first_sum = i1+i3+i5+i7+i9+i11;
	second_sum= i2+i4+i6+i8+i10;
	total = 3 * first_sum + second_sum;
	result = 9 - ((total-1)%10);
	
	//check
	if (result != i12){
		printf("NOT VALID");
	}else{
		printf("VALID");	
	}
	return 0;
}
