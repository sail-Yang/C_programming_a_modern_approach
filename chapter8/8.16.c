#include <stdio.h>
#include <ctype.h>
#define N 26
int main(void){
	int i=0,j=0,a[N];
	char ch,c1[N],c2[N],num;
	
	/*初始化字母数组*/
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
	
	/*统计字母*/
	for(j=0;j<i;j++){
		num = (c1[j]-'a')%26;
		a[num]=a[num]+1;
	}
	/*第二个单词*/
	for(j=0;j<i;j++){
		num = (c1[j]-'a')%26;
		a[num]=a[num]-1;
	}
	
	/*判断是否为变位词*/
	for(j=0;j<N;j++){
		if(a[j]!=0){
			printf("The words are not anagrams.");
			return 0;
		}
	}
	printf("The words are anagrams.");
	return 0;
}
