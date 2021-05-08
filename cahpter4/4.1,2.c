 #include <stdio.h>

int main(void)
{
	int x,y,z,data;
	printf("Enter a three-digit number:");
	scanf("%d",&data); 
	x = data/100;
	y = (data-100*x)/10;
	z = data-100*x-10*y;
	
	int re_data;
	re_data = z*100+y*10+x;
	printf("The reversal is: %d",re_data);
	
	return 0;
} 
