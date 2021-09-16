/*����ʵ��9.4�Ľ���Ѿ������˺�����*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define N 26

void read_word(int c[N]);
bool equal_array(int c1[26],int c2[26]);
int main(){
	int c1[N],c2[N];
	/*���뵥������*/
	printf("Enter first word:");
	read_word(c1);
	
	printf("Enter second word:");
	read_word(c2);
	
	if(equal_array(c1,c2)){
		printf("The words are anagrams.");
	}else{
		printf("The words are not anagrams.");
	}
	return 0;
}

void read_word(int c[N]){
	int i=0,j=0;
	char ch,word[N],num;
	/*��ʼ����ĸ����*/ 
	for(j = 0;j<N;j++){
		c[j]=0;
	}
	/*���뵥��*/
	while((ch = getchar())!='\n'){
		ch = tolower(ch);
		word[i]=ch;
		i++;
	}
	/*������ĸ����*/ 
	for(j=0;j<i;j++){
		num = (word[j]-'a')%26;
		c[num]=c[num]+1;
	}
}
bool equal_array(int c1[26],int c2[26])
{
	int j;
	for(j=0;j<N;j++){
		if((c1[j]-c2[j])!=0){
			return false;
		}
	}
	return true;
}
