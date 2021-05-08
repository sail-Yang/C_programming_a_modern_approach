#include <stdio.h>

int main(void)
{
	int gs1,id,pub,item,check;
	printf("Enter ISBN:");
	scanf("%d-%d-%d-%d-%d",&gs1,&id,&pub,&item,&check);
	printf("GS1 prefix: %d\n",gs1);
	printf("Group identifier: %d\n",id);
	printf("Publishier code: %d\n",pub);
	printf("Item number: %d\n",item);
	printf("Check dight: %d\n",check);
	return 0;
}
