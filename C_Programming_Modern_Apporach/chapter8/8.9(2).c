/*这个程序是我最初的想法，但是貌似失败了，就放在这吧*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>//使用当前时钟做种子 
#define N 10

int main(){
	char a[N][N],b[26];
	int i=0,j=0,k=0,step=0;
	
	/*初始化数组*/
	for(i=0;i<26;i++){
		b[i] = 'A'+i; 
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a[i][j]='.';
		}
	}
	/*初始化随机数、起点*/
	srand( (unsigned)time( NULL ) );
	a[0][0]='A';
	i=0;
	j=0;
	k=0;
	
	/*以字母序列循环*/
	for (k=1;k<26;k++){
		if (a[i-1][j]!='.'&&a[i+1][j]!='.'&&a[i][j+1]!='.'&&a[i][j-1]!='.')
			break;
		
		if (a[i-1][j]!='.'&&a[i+1][j]!='.'&&a[i][j+1]!='.')
			if(j!=0) 
				step = 0;
			else
				break;
		else if (a[i-1][j]!='.'&&a[i+1][j]!='.'&&a[i][j-1]!='.')
			if(j!=9)
				step = 2;
			else
				break;
		else if (a[i-1][j]!='.'&&a[i][j-1]!='.'&&a[i][j+1]!='.')
			if(i!=0)
				step = 3;
			else
				break;
		else if (a[i+1][j]!='.'&&a[i][j-1]!='.'&&a[i][j+1]!='.')
			if(i!=9)
				step = 1;
			else
				break;	
		else{
			if (a[i][j-1]!='.'&&a[i+1][j]!='.')
				if(i!=0&&j!=9)
					step = rand()%1+2;//2~3
				else if (i==0&&j!=9)
					step=2;
				else if (j==9&&i!=0)
					step=3;
				else
					break;
			else if(a[i+1][j]!='.'&&a[i][j+1]!='.'){
				step = rand()%1;//0、3
				if (step == 1)
					step = step + 2;

				
			}
			else if(a[i][j+1]!='.'&&a[i-1][j]!='.')
				step = rand()%1;//0~1

			else if(a[i-1][j]!='.'&&a[i][j-1]!='.')
				step = rand()%1+1;//1~2
			else if(a[i][j+1]!='.'&&a[i][j-1]!='.'){
				step = rand()%1+1;//1、3 
				if (step==2)
					step=3;
			}
			else if(a[i-1][j]!='.'&&a[i+1][j]!='.'){
				step = rand()%1;//0、2 
				if (step==1)
					step=2;
			}
			else{
				if(a[i][j-1]!='.')
					if(j!=9)
						step=rand()%3+1;
					
				else if(a[i+1][j]!='.'){
					step=rand()%3;
					if(step==1)
						step=3;
				}
				else if(a[i][j+1]!='.'){
					step=rand()%3;
					if(step==2)
						step=3;
				}
				else if(a[i-1][j]!='.'){
					step=rand()%3;
				}
				else{
					step=rand()%4;
				}
			}
				
		}
		switch (step){
			case 0:{
				j = j-1;
				a[i][j]=b[k];
				break;
			}
			case 1:{
				i = i+1;
				a[i][j]=b[k];
				break;
			}
			case 2:{
				j = j+1;
				a[i][j]=b[k];
				break;
			}
			case 3:{
				i = i-1;
				a[i][j]=b[k];
				break;
			}
		}
	}
	
	/*输出数组*/ 
	for (i = 0; i < N; i++){
	        printf("\n");
	        for (j = 0; j < N; j++)
	            printf(" %c", a[i][j]);
	}
	return 0;
}
