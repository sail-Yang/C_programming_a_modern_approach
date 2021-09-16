#include <stdio.h>

int main(void){
	int m,d,y;	
	int m_min,d_min,y_min;
	y_min = 9999;
	m_min = 13;
	d_min = 32;
	do{
		printf("Enter a date:");
		scanf("%d/%d/%d",&m,&d,&y);
		if(y == 0&&m == 0&&d == 0){
			break;
		}else{
			if (y>y_min){
				;
			}else if(y == y_min){
				if (m >m_min){
					;
				}else if (m==m_min){
					if (d > d_min){
						;
					}else{
						y_min = y;
						m_min = m;
						d_min = d;
					}
				}else{
					y_min = y;
					m_min = m;
					d_min = d;
				}
			}else{
				y_min = y;
				m_min = m;
				d_min = d;
			}
		}		
	}while(y!=0&&m!=0&&d!=0);
	printf("%d/%d/%.4d is the earliest date",m_min,d_min,y_min);
	return 0;
}
