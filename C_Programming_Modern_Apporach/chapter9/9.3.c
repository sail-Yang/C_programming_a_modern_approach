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
	
	//��ʼ���� 
	generate_random_walk(b);
	
	srand((unsigned) time(NULL));
	int ways,m;
	i = 0; j = 0;
	b[0][0] = 'A';
	a[0][0] = true;
	
	for (m = 0; m < 25; ) {
		 //��0���ϣ� 1���£� 2���� 3���� 
		ways = rand() % WAY;      
		
		if (ways == 0) {
			//��������߳�����ˣ�continue����ѭ�����Ա�ķ��� 
			if (i - 1 < 0) {
				continue;
			} 
			//�������������ĸ�ˣ� �����ж� 
			else if (a[i - 1][j] == true){
				//������涼����ĸ���˳� 
				if ((a[i + 1][j] == true && a[i][j - 1] == true && a[i][j + 1] == true)
				// ������ߺ����½���� 
					|| j - 1 < 0 && a[i + 1][j] == true && a[i][j + 1] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i][j + 1] == true
				// �ұߺ����½�
					|| j + 1 > 9 && a[i + 1][j] == true && a[i][j - 1] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i][j + 1] == true
				//�±�
					|| i + 1 > 9 && a[i][j + 1] == true && a[i][j - 1] == true) break;
				//��������ǣ�����ѡ���� 
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
				//�ұߺ����Ͻ� 
					|| j + 1 > 9 && a[i][j - 1] == true && a[i - 1][j] == true
					|| j + 1 > 9 && i - 1 < 0 && a[i][j - 1] == true
				//��� 
					|| j - 1 < 0 && a[i - 1][j] == true && a[i][j + 1] == true
				//�ϱ� 
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
				// �����±ߺ����½���� 
					|| i + 1 > 9 && a[i - 1][j] == true && a[i][j + 1] == true
					|| j + 1 > 9 && i + 1 > 9 && a[i - 1][j] == true
				// �ϱߺ����Ͻ�
					|| i - 1 < 0 && a[i + 1][j] == true && a[i][j + 1] == true
					|| j + 1 > 9 && i - 1 < 0 && a[i][j + 1] == true
				// �ұ�
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
				//��ߺ����½� 
					|| j - 1 < 0 && a[i - 1][j] == true && a[i + 1][j] == true
					|| j - 1 < 0 && i + 1 > 9 && a[i - 1][j] == true
				//�±� 
					|| i + 1 > 9 && a[i - 1][j] == true && a[i][j - 1] == true
				//�ϱ� 
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
