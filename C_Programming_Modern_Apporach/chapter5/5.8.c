#include <stdio.h>

int main(void)
{
	printf("Enter a 24-hour time:");
	int h1,h2,h3,h4,h5,h6,h7,h8,m1,m2,m3,m4,m5,m6,m7,m8;
	int t1,t2,t3,t4,t5,t6,t7,t8;
	int t,h,m;
	scanf("%d:%d",&h,&m);
	//数据
	h1 = 8;
	h2 = 9;
	h3 = 11;
	h4 = 12;
	h5 = 2;
	h6 = 3;
	h7 = 7;
	h8 = 9;
	m1 = 0;
	m2 = 43;
	m3 = 19;
	m4 = 47;
	m5 = 0;
	m6 = 45;
	m7 = 0;
	m8 = 45; 
	//数据转换 
	t1 = h1*60+m1;
	t2 = h2*60+m2;
	t3 = h3*60+m3;
	t4 = h4*60+m4;
	t5 = (h5+12)*60+m5;
	t6 = (h6+12)*60+m6;
	t7 = (h7+12)*60+m7;
	t8 = (h8+12)*60+m8;
	t = h*60+m;
	
	int sub1,sub2,sub3,sub4,sub5,sub6,sub7,sub8;
	sub1 = abs(t - t1);
	sub2 = abs(t - t2);
	sub3 = abs(t - t3);
	sub4 = abs(t - t4);
	sub5 = abs(t - t5);
	sub6 = abs(t - t6);
	sub7 = abs(t - t7);
	sub8 = abs(t - t8);
	
	int min;
	min = sub1;
	if (sub2<min){
		min = sub2;
	}else {
		min = sub1;
	}
	if (sub3<min){
		min = sub3;
	}else{
		min = min;
	}
	if (sub4<min){
		min = sub4;
	}else{
		min = min;
	}
	if (sub5<min){
		min = sub5;
	}else{
		min = min;
	}
	if (sub6<min){
		min = sub6;
	}else{
		min = min;
	}
	if (sub7<min){
		min = sub7;
	}else{
		min = min;
	}
	if (sub8<min){
		min = sub8;
	}else{
		min = min;
	}
	
	
	if (min == sub1){
		printf("Closet departure time is %d:%d a.m.,arriving at 10:16 a.m.",h1,m1);
	}else if(min == sub2){
		printf("Closet departure time is %d:%d a.m.,arriving at 11:52 a.m.",h2,m2);
	}else if(min==sub3){
		printf("Closet departure time is %d:%d a.m.,arriving at 1:31 p.m.",h3,m3);
	}else if(min==sub4){
		printf("Closet departure time is %d:%d p.m.,arriving at 3:00 p.m.",h4,m4);
	}else if(min==sub5){
		printf("Closet departure time is %d:%d p.m.,arriving at 4:08 p.m.",h5,m5);
	}else if(min==sub6){
		printf("Closet departure time is %d:%d p.m.,arriving at 5:55 p.m.",h6,m6);
	}else if(min==sub7){
		printf("Closet departure time is %d:%d p.m.,arriving at 9:20 p.m.",h7,m7);
	}else{
		printf("Closet departure time is %d:%d p.m.,arriving at 11:58 p.m.",h8,m8);
	}
	return 0;
}
