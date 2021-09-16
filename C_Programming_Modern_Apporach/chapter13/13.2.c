#include <stdio.h>
#include <string.h>
#define MAX_REMIND	50	//maxium number of reminders
#define MSG_LEN  60		//max length of reminder message

int read_line(char str[],int n);
int main(){
	char reminders[MAX_REMIND][MSG_LEN+11];
	char day_str[11],msg_str[MSG_LEN+1];
	int month,day,hour,minute,i,j,num_remind = 0;
	
	for(;;){
		/*�����ɴ�����������*/
		if(num_remind == MAX_REMIND){
			printf("--NO space left --\n");
			break;
		} 
		
		/*��ȡ����ʱ��*/
		printf("Enter day(mm/dd/hour:minute) and remember:");
		scanf("%2d/%2d/%2d:%2d",&month,&day,&hour,&minute);
		//printf("%d",month);
		if(month == 0)
			break; 
		if(month>12 || month<1||day<1||day>31||hour<0||hour>24||minute<1||minute>59)
		{
			printf("Your input has fault!\n");
			read_line(msg_str,MSG_LEN);
			continue;
		}
		sprintf(day_str,"%2d/%2d/%2d/%2d ",month,day,hour,minute);
		
		/*��ȡ����*/
		read_line(msg_str,MSG_LEN);
		
		/*����λ��*/
		for(i = 0;i < num_remind;i++)
			if (strcmp(day_str, reminders[i]) < 0)
				break;
		/*�ҵ�λ��i�󣬰�i����ʼ���ַ���λ�ö������ƶ�һ��*/ 
		for(j = num_remind;j > i;j--)
			strcpy(reminders[j],reminders[j-1]);
		/*��ʱ�������ƴ������*/ 
		strcpy(reminders[i],day_str);
		strcat(reminders[i],msg_str);
		
		num_remind++; 
	}
	
	/*������*/
	printf("\nDay Reminder\n");
	for (i=0; i<=num_remind;i++)
		printf(" %s\n",reminders[i]);
		 
	return 0;
}

int read_line(char str[],int n)
{
	int ch,i =0;
	while((ch=getchar()) != '\n')
		if (i<n)
			str[i++]=ch;
	str[i] = '\0';
	return i;
}
