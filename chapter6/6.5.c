#include <stdio.h>
#include <math.h>
int main(void)
{
	int num,count,re,i,m,n;
	printf("Enter a num:");
	scanf("%d",&num);
	count = -1;
	i = num;
	/*计算num的位数*/ 
	do{
		count = count+1;
		m = i%10;		//m用于存放余数 
		i = (i-m)/10;	//每次把i变成两位数 
		
		
	}while(m!=0);
	//printf("%d",count);
	/*开始倒序*/ 
	i = num;
	re = 0;
	do{
		m = i%10;
		count  = count -1;
		n = pow(10,count);
		re = re + m*n;
		i = (i-m)/10;
	}while(count != 0);
	printf("%d",re);
	return 0;
}
