#include <stdio.h>
#include <ctype.h>
#define N 26
int main(void){
	int i=0,j=0,a[N];
	char ch,c1[N],c2[N],num;
	
	/*��ʼ����ĸ����*/
	for(j = 0;j<N;j++){
		a[j]=0;
	}  
	/*input words*/
	printf("Enter first word:");
	while((ch = getchar())!='\n'){
		ch = tolower(ch);
		c1[i]=ch;
		i++;
	}
	printf("Enter second word:");
	while((ch = getchar())!='\n'){
		ch = tolower(ch);
		c2[j]=ch;
		j++;
	}
	
	/*ͳ����ĸ*/
	for(j=0;j<i;j++){
		num = (c1[j]-'a')%26;
		a[num]=a[num]+1;
	}
	/*�ڶ�������*/
	for(j=0;j<i;j++){
		num = (c1[j]-'a')%26;
		a[num]=a[num]-1;
	}
	
	/*�ж��Ƿ�Ϊ��λ��*/
	for(j=0;j<N;j++){
		if(a[j]!=0){
			printf("The words are not anagrams.");
			return 0;
		}
	}
	printf("The words are anagrams.");
	return 0;
}
