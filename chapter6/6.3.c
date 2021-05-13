#include <stdio.h>

int main(void)
{
	printf("Enter a fraction:");
	int zi,mu;
	scanf("%d/%d",&zi,&mu);
	int i,n,m;
	n = mu;
	m = zi;
	if(zi == 0){
		printf("In lowest terms:0");
	}else{
		while (n!=0){
		i = n;
		n = m%n; 
		m = i;
		} 
		zi = zi/m;
		mu = mu/m;
		printf("In lowest terms:%d/%d",zi,mu);
	}
	
	return 0;
 } 
