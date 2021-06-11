#include <stdio.h>
#include <stdbool.h>

void create_magic_square(int n,int a[n][n]);
void print_magic_square(int n,int a[n][n]);

int main(){	
	int n;
	printf("This program creates a magic square of a specified size.\n");
	printf("The size must be an odd number between 1 and 99.\n");
	printf("Enter size of magic square:");
	scanf("%d",&n);
	
	int a[n][n];
	create_magic_square(n,a);
	print_magic_square(n,a);
}
void create_magic_square(int n,int a[n][n])
{
	int m = (n-1)/2,i,j,x,y;
	bool b[n][n];
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			b[i][j]=false;
		}
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=0;
		}
	}

	x = 0;
	y = m;
	/*把1放到0行的中间*/
	a[0][m]=1;
	b[0][m]=1;
	
	/*放数字*/
	for(i=2;i<=(n*n);i++){
		if(x==0&&y!=n-1){
			x = n-1;
			y = y+1;
			if(b[x][y]==1){
				x = 1;
				y = y-1;
				a[x][y]=i;
				b[x][y]=1;
			}else{
				a[x][y]=i;
				b[x][y]=1;
			}	
		}else if(x==0&&y==n-1){
			x = n-1;
			y = 0;
			if(b[x][y]==1){
				x = 1;
				y = n-1;
				a[x][y]=i;
				b[x][y]=1;
			}else{
				a[x][y]=i;
				b[x][y]=1;
			}
		}else if(x!=0&&y==n-1){
			x = x-1;
			y = 0;
			if(b[x][y]==1){
				x = x-1;
				y = n-1;
				a[x][y]=i;
				b[x][y]=1;
			}else{
				a[x][y]=i;
				b[x][y]=1;
			}
		}else{
			x = x-1;
			y = y+1;
			if(b[x][y]==1){
				x = x+2;
				y = y-1;
				a[x][y]=i;
				b[x][y]=1;
			}else{
				a[x][y]=i;
				b[x][y]=1;
			}
		}
	}
}
void print_magic_square(int n,int a[n][n])
{
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("\t%d",a[i][j]);
		}
		printf("\n");
	}
}

