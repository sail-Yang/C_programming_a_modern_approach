/*û�аѱ����������һ����*/ 
#include <stdio.h>

int main(void){
	char ch;
	float vac=0.00f,all=0.00f,length; /*vacΪ������,allΪ������*/ 
	printf("Enter a sentence:");
	while((ch = getchar())!='\n'){
		if (ch == ' ' || ch == '.'||ch == '?'||ch == '!'||ch == ','){
			vac += 1.00f; 
		} else {
			all += 1.00f;
		}
	}
	length = all / vac;
	printf("%f\n %f\n",all,vac);
	printf("Average word length:%.1f",length);
	return 0;
}
