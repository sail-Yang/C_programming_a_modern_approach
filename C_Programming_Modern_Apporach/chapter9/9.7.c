
#include <stdio.h>
 
int power(int, int);
 
int main(void)
{
	int x, n;
	
	printf("输入x和n的值：");
	scanf("%d%d", &x, &n);
	
	
	printf("结果：%d", power(x, n));
	
	return 0;
}
 
int power(int x, int n)
{
	if (n == 0) {
		return 1;
	} else if (n % 2 == 0 && n != 0) {
		return power(x, n / 2) * power(x, n / 2);	
	} else if (n % 2 != 0) {
		return x * power(x, n - 1);
	}
 } 
