#include <stdio.h>

int main(void){
	char c, f;

	printf("Enter a first and last name: ");	
    scanf(" %c", &f);                 		// ����scanf�ڶ�ȡһ���ַ�������֮������벻���ȡ
    
    while ((c = getchar()) != '\n')         // ��������������ѭ��
        if (c == ' ')                       // ��������ˣ�����ȡ�ո�֮����ַ�
        {
            // printf("%c", toupper(' '));      �˺��������н�������ո�Ĵ�д�ַ����䱾��
            while ((c = getchar()) != '\n') 
				printf("%c", c);
            printf(", %c\n", f);
            break;
        }
	return 0;
} 
