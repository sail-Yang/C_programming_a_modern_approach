#include <stdio.h>
#define N 10

int main(void){
	int row,col;
	double ident[N][N];
	
	for (row = 0;row <N ;row++)
		for (col = 0;col < N;col++)
			if (col == row)
				ident[row][col]=1.0;
			else
				ident[row][col] = 0.0;
	return 0;
} 
