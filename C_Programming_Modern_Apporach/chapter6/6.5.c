#include <stdio.h>
#include <math.h>
int main(void)
{
	int num,count,re,i,m,n;
	printf("Enter a num:");
	scanf("%d",&num);
	count = -1;
	i = num;
	/*����num��λ��*/ 
	do{
		count = count+1;
		m = i%10;		//m���ڴ������ 
		i = (i-m)/10;	//ÿ�ΰ�i�����λ�� 
		
		
	}while(m!=0);
	//printf("%d",count);
	/*��ʼ����*/ 
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
