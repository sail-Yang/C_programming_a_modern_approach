#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define N 10
#define WAY 4

void generate_random_walk(char b[10][10]);
void print_array(char b[10][10]);

int main(void)
{
	bool a[N][N] = {false};
	char b[N][N];
	int i, j;
	
	//初始化表 
	generate_random_walk(b);
	
	srand((unsigned) time(NULL));
	int ways,m;
	i = 0; j = 0;
	b[0][0] = 'A';
	a[0][0] = true;
	
	for (m = 0; m < 25; ) {
		 //余0表上， 1表下， 2表左， 3表右 
		ways = rand() % WAY;      
		
		if (ways == 0) {
			//如果往上走出表格了，continue重新循环试试别的方向 
			if (i - 1 < 0) {
				continue;
			} 
			//如果往上走有字母了， 进行判断 
			else if (a[i - 1][j] == true){
				//如果四面都是字母，退出 
				if ((a[i + 1][j] == true && a[i][j - 1] == true && a[i][j + 1] == true)
				// 考虑左边和左下角情况 
					|| j - 1 < 0 && a[i + 1][j] == true && a[i][j + 1] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i][j + 1] == true
				// 右边和右下角
					|| j + 1 > 9 && a[i + 1][j] == true && a[i][j - 1] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i][j + 1] == true
				//下边
					|| i + 1 > 9 && a[i][j + 1] == true && a[i][j - 1] == true) break;
				//如果都不是，重新选方向 
				continue;
			} else {				
				a[i - 1][j] = true;
				b[i - 1][j] = 'B' + m;
				m++;
				i--;
				continue;
			}
		} 
		
		if (ways == 1) {
			if (i + 1 > 9) {
				continue;
			} else if (a[i + 1][j] == true){
				if (a[i - 1][j] == true && a[i][j - 1] == true && a[i][j + 1] == true
				//右边和右上角 
					|| j + 1 > 9 && a[i][j - 1] == true && a[i - 1][j] == true
					|| j + 1 > 9 && i - 1 < 0 && a[i][j - 1] == true
				//左边 
					|| j - 1 < 0 && a[i - 1][j] == true && a[i][j + 1] == true
				//上边 
					|| i - 1 < 0 && a[i][j + 1] == true && a[i][j - 1] == true) break;
				continue;
			} else {				
				a[i + 1][j] = true;
				b[i + 1][j] = 'B' + m;
				m++;
				i++;
				continue;
			}
		} 
		
		if (ways == 2) {
			if (j - 1 < 0) {
				continue;
			} else if (a[i][j - 1] == true){
				if (a[i + 1][j] == true && a[i - 1][j] == true && a[i][j + 1] == true
				// 考虑下边和右下角情况 
					|| i + 1 > 9 && a[i - 1][j] == true && a[i][j + 1] == true
					|| j + 1 > 9 && i + 1 > 9 && a[i - 1][j] == true
				// 上边和右上角
					|| i - 1 < 0 && a[i + 1][j] == true && a[i][j + 1] == true
					|| j + 1 > 9 && i - 1 < 0 && a[i][j + 1] == true
				// 右边
					|| j + 1 > 9 && a[i - 1][j] == true && a[i + 1][j] == true) break;
				continue;
			} else {				
				a[i][j - 1] = true;
				b[i][j - 1] = 'B' + m;
				m++;
				j--;
				continue;
			}
		} 
		
		if (ways == 3) {
			if (j + 1 > 9) {
				continue;
			} else if (a[i][j + 1] == true){
				if (a[i + 1][j] == true && a[i][j - 1] == true && a[i - 1][j] == true
				//左边和左下角 
					|| j - 1 < 0 && a[i - 1][j] == true && a[i + 1][j] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i - 1][j] == true
				//下边 
					|| i + 1 > 9 && a[i - 1][j] == true && a[i][j - 1] == true
				//上边 
					|| i - 1 < 0 && a[i][j - 1] == true && a[i + 1][j] == true) break;
				continue;
			} else {				
				a[i][j + 1] = true;
				b[i][j + 1] = 'B' + m;
				m++;
				j++;
				continue;
			}
		} 
	}
	print_array(b);
	return 0;
}
void generate_random_walk(char b[10][10]){
	int i,j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			b[i][j] = '.';
		}
	}
}
void print_array(char b[10][10]){
	int i,j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%c ", b[i][j]);
		}
		printf("\n");
	}
}
