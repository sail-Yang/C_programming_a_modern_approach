#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 80 
int main(){
	char ch,a[N],word[26];
	int i=0,j=0,num;
	
	printf("Enter message to be encrypted:");
	
	/*������ӣ�iΪ���ӳ��ȣ��������*/
	while((ch=getchar())!='\n'){
		a[i]=ch;
		i++;
	}
	/*��ʼ��26��ĸ��,�����ʼ����д��ĸ*/
	for(j=0;j<26;j++){
		word[j] = 'A'+j;
	}  
	/*����ƫ��λ��num*/
	printf("Enter shift amount(1~25):");
	scanf("%d",&num);
	
	for (j=0;j<i;j++){
		if (a[j]<=90&&a[j]>=65){
			/*65~90Ϊ��д��ĸ*/
			a[j] = ((a[j]-'A')+num)%26+'A';
		}else if(a[j]>=97&&a[j]<=122){
			/*97~122ΪСд��ĸ*/
			/*ת���ɴ�д��ĸ������*/
			ch = a[j];
			ch = toupper(ch);
			ch = ((ch-'A')+num)%26+'A';
			a[j] = tolower(ch);/*�����Сд*/
		}else{
			continue;
		}
	} 
	
	/*�������*/
	for(j=0;j<i;j++){
		printf("%c",a[j]);
	} 
		
		
	
	return 0;
}
