/*修改程序8.1，利用宏计算数组长度*/
#include <stdio.h>
#define SIZE ((int)(sizeof(a) / sizeof(a[0])))

int main(){
	int a[10], i;

  	printf("Enter %d numbers: ",SIZE);
  	for (i = 0; i < SIZE; i++)
    	scanf("%d", &a[i]);
    for (i = 0; i < SIZE; i++)
    	printf("%d",a[i]);
    return 0;
}
