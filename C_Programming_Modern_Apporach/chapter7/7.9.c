#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int a, b, T;
    char c;

	printf("Enter a 12-hour time: ");	
	scanf("%d:%d %c", &a, &b, &c);
    getchar();
    
	switch (toupper(c))
	{
	        case 'A':
	            printf("Equivalent 24-hour time:%d:%d",a,b);
	            break;
	        case 'P':
	            if(a ==12){
	            	a = 0;
	            	printf("Equivalent 24-hour time:%d:%d",a,b);
				}else{
					a = a+12;
	            printf("Equivalent 24-hour time:%d:%d",a,b);
				}
	            break;
	}
	return 0;
}
