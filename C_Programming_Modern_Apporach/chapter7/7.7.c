#include <stdio.h>

int main(void)
{
	printf("Enter two fractions separated and a sign:(x/x+y/y)");
	int num1,denom1,num2,denom2;
	char str;
	scanf("%d/%d%c%d/%d",&num1,&denom1,&str,&num2,&denom2);
	int num3,denom3; 
	
	/*进行计算*/ 
	if (str == '+'){
		num3 = num1*denom2+num2*denom1;
		denom3 = denom1*denom2;
	}else if(str == '-'){
		num3 = num1*denom2-num2*denom1;
		denom3 = denom1*denom2;
	}else if(str == '*'){
		num3 = num1*num2;
		denom3 = denom1*denom2;
	}else if(str == '/'){
		if (num2 == 0){
			printf("The division cannot be 0.");
		}else{
			num3 = num1*denom2;
			denom3 = denom3*num2;
		}

	}else if (denom1==0||denom2==0){
		printf("Denominator can't be 0.");
	}else{
		printf("Input error!");
	}
	
	/*化简结果分数*/
	printf("%d/%d\n",num3,denom3); 
	int i=0,m,n;
	m = num3;
	n = denom3;

	while(n!=0){
		i = n;
		n = m%n;
		m = i;
	}
	num3 = num3/m;
	denom3 = denom3/m;
	printf("%d/%d",num3,denom3);
	
	return 0;
	
}
