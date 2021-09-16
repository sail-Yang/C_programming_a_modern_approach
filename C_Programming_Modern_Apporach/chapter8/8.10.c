#include <stdio.h>
#include <math.h>
#define N 8

int main(){
	const int lea[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};
	const int arr[8] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
	int i,h,m,n,time,min=1300;
	
	printf("Enter a 24-hour time:");
	scanf("%d:%d",&h,&m);
	
	time = 60*h+m;
	for(i=0;i<N;i++){
		if(min<=abs(time-lea[i]))
			min = min;
		else{
			min = abs(time-lea[i]);
			n = i;
		}
			
	}
	
	printf("Closet departure time is ");
	if(lea[n]<=719){
		h = lea[n] / 60;
		m = lea[n] % 60;
		printf("%2d:%2d a.m.,",h,m);
		if (arr[n]<=719){
			h = arr[n] / 60;
			m = arr[n] % 60;
			printf(" arriving at %2d:%2d a.m.",h,m);
		}else{
			h = arr[n] /60 -12;
			m = arr[n] % 60;
			printf(" arriving at %2d:%2d p.m.",h,m);
		}
	}else{
		h = lea[n] /60 -12;
		m = lea[n] % 60;
		printf("%d:%d p.m.,",h,m);
		if (arr[n]<=719){
			h = arr[n] / 60;
			m = arr[n] % 60;
			printf(" arriving at %2d:%2d a.m.",h,m);
		}else{
			h = arr[n] /60 -12;
			m = arr[n] % 60;
			printf(" arriving at %2d:%2d p.m.",h,m);
		}
	}
	return 0;
} 
