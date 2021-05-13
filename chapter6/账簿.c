/*账簿程序*/ 
#include <stdio.h>

int main(void)
{
	printf("*** ACME checkbook-balancing program ***\n");
	printf("Commands:0=clear, 1 = credit,2 = debit,");
	printf("3 = balance,4 = exit\n\n");
	int cmd;
	float balance=0.0f,credit,debit;
	for (;;){
		printf("Enter command:");
		scanf("%d",&cmd);
		switch(cmd){
			case 0:
				balance = 0.0f;
				break;
			case 1:
				printf("Enter amount of credit:");
				scanf("%f",&credit);
				balance +=credit;
				break;
			case 2:
				printf("Enter amount of debit:");
				scanf("%f",&debit);
				balance -= debit; 
				break;
			case 3:
				printf("Current balance:$%.2f\n",balance);
				break;
			case 4:
				return 0;/*使程序终止并返回操作系统*/
			default:
			printf("*** ACME checkbook-balancing program ***\n");
			printf("Commands:0=clear, 1 = credit,2 = debit,");
			printf("3 = balance,4 = exit\n\n");
			break;	 
		}
	} 
 } 
