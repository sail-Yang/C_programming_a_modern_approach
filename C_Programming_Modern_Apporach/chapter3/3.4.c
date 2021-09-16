#include <stdio.h>

int main(void)
{
	printf("Enter phone number [(xxx) xxx-xxxx]:");
	int part1,part2,part3;
	scanf("(%d) %d-%d",&part1,&part2,&part3);
	printf("You entered %d.%d.%d",part1,part2,part3);
	return 0;
}

