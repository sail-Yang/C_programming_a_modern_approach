#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
int main(){
	int n,i,k,j,len;
	char str[10][MAX_SIZE+1],ch;
	scanf("%d",&n);
	getchar();
	int count[100],num1=0;
	for(i = 0;i<n;i++)
	{
		num1=0;
		gets(str[i]);
		len = strlen(str[i]);
		//printf("%d",len);
		for (k=0;k<len;k++)
		{
			if(str[i][k]=='A'||str[i][k]==' ')
				continue;
			else if(str[i][k]=='P')
			{
				for(j=k+1;j<len;j++)
				{
					if(str[i][j]==' '||str[i][j]=='A')
					{
						num1 +=1;
						if (num1>=3){
							break;
						}else
							continue;
					}
					else if(str[i][j]=='T')
					{
						if(j==k+1){
							break;
						}else{
							j++;
							while(j<=len){
								if(str[i][j]=='A'||str[i][j]==' '||str[i][j]=='\0')
								{
									if(j == len - 1||j == len)
										goto yes;
									else{
										j++;
										continue;
									}
								}
								else
									break;
							}
							break;
						}
					}
				}
				count[i]=0;
				break;
			}else
			{
				count[i]=0;
				break;
			}
			yes:
				count[i]=1;
				break;
		}
	
	}
	for(i = 0;i<n;i++)
	{
		if(count[i]==1){
			printf("YES");
		}else{
			printf("NO");
		}
		if(i<n-1)
			printf("\n");
	}
	return 0;
} 
