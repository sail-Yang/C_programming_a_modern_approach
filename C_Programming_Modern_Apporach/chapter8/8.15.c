#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 80 
int main(){
	char ch,a[N],word[26];
	int i=0,j=0,num;
	
	printf("Enter message to be encrypted:");
	
	/*读入句子，i为句子长度，包括标点*/
	while((ch=getchar())!='\n'){
		a[i]=ch;
		i++;
	}
	/*初始化26字母表,这里初始化大写字母*/
	for(j=0;j<26;j++){
		word[j] = 'A'+j;
	}  
	/*读入偏移位：num*/
	printf("Enter shift amount(1~25):");
	scanf("%d",&num);
	
	for (j=0;j<i;j++){
		if (a[j]<=90&&a[j]>=65){
			/*65~90为大写字母*/
			a[j] = ((a[j]-'A')+num)%26+'A';
		}else if(a[j]>=97&&a[j]<=122){
			/*97~122为小写字母*/
			/*转换成大写字母来运算*/
			ch = a[j];
			ch = toupper(ch);
			ch = ((ch-'A')+num)%26+'A';
			a[j] = tolower(ch);/*最后再小写*/
		}else{
			continue;
		}
	} 
	
	/*输出数组*/
	for(j=0;j<i;j++){
		printf("%c",a[j]);
	} 
		
		
	
	return 0;
}
