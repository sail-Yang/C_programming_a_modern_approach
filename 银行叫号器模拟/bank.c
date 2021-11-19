/*�����2003� 201205130 ���нк���ģ��(ѭ������)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_DURATION 40 			//�����������ʱ�䣬��λΪmin
#define MAX_WINDOWS_NUM	10			//��������ҵ�񴰿�����
#define MAX_CUSTOMERS 50			//���ÿ�������Ŷ��ٸ���
#define MAX_CUSTOMERS_ARRIVAL 10	//�����û��ﵽ���������ʱ��

/*--------------�ṹ������--------------*/
/*�����¼���������¼�*/
typedef struct linklist
{
	int OccurTime;			//�¼�������ʱ��
	int EventType;			//�¼����ͣ�0��ʾ�����¼���others��ʾ�����ڵ��뿪�¼�
	struct linklist *next;
}Event,*EventList;
typedef Event *Event_ptr;	//����һ��ָ��ʱ�����ָ��

/*���崰�ڶ��е�Ԫ�أ�ÿ���ŶӵĿͻ���Ϣ*/
typedef struct person
{
	int ArrivalTime;	//�ͻ��ĵ���ʱ��
	int Duration;		//ÿ���ͻ�����ҵ���ʱ�䣬���������
	int num;			//ÿ���ͻ�ȡ���ĺţ���ʶ�ǵڼ��������е�
}Person;

/*����ÿ�����ڵĶ���(ѭ������)*/
typedef struct queue
{
	Person customer[MAX_CUSTOMERS];		//����Ԫ������
	int front;
	int rear;
}Window_Queue;

/*ÿ�����ڽ��ܵĹ˿͵���ʷ������*/
typedef struct history
{
	Person people;			//һ���ͻ�����Ϣ
	int AllNum;				//����ͷ��㣬��ʾ������ڽ���Ӵ��˶��ٿ���
	int leave_time;
	struct history *next;
}History;
typedef History * HistoryList;

/*-----------------ȫ�ֱ���-----------------*/
int TotalTimes = 0,CustomerNum = 0;		//�ۼ��û�����ʱ�䣬�ͻ���
int BeginTime = 0,CloseTime = 630;		//1110min�����������°�ʱ����18:30
int WindowsNum = 0;						//���д�������
EventList Ev;							//�¼�����
Window_Queue* Windows = NULL;			//�ö�ʵ��һ���洢ָ�򴰿ڶ���ָ�������
HistoryList *All_History = NULL;		//�ö�ʵ��һ���洢ÿ��������ʷ���������

/*-----------------��������-----------------*/
/*��Ҫ����*/
void OpenForDay();					//��ʼ������ģ����
void Simulation();					//����ģ����
void Interact();					//��������Լ���������
void Event_Drive(Event_ptr p);		//�¼�������
void Arrival_Event(EventList L,Event_ptr p);	//�������¼�
void Leave_Event(EventList L,Event_ptr p);		//�����뿪�¼�
/*��ʼ������*/
EventList InitList(EventList L);	//��ʼ���¼���
void InitQueue(int WindowsNum);		//��ʼ�������ڶ���
void InitHistory(int WindowsNum);	//��ʼ����������ʷ��¼
/*�Խṹ��Ĳ�������*/
void EventInsert(EventList L,int Occurtime,int eventType);	//�������������
void EnQueue(int OccurTime,int Duration,int window);		//�ͻ�������촰�ڶ����Ŷ�
void HistoryInsert(int window,Person people,int occurtime);	//����ָ�����ڵ���ʷ��¼
EventList EventDelete(EventList L);							//ɾ����һ���¼�
void DeQueue(int window,Person *person_ptr);				//����������Ŀͻ��뿪����
/*�������*/
void PrintList(EventList L);		//��ӡ�¼������Ե�ʱ����
void PrintQueue();					//��ӡ���ж��У����Ե�ʱ����
void PrintAllQueue(int WindowsNum);
void PrintHistory(int window);
/*С���*/
int Get_WindowsNum();				//���û��������д�������
void Sort_Occurtime(EventList L);	//���ݷ����¼�����
int Get_Len(EventList L);			//��ȡ�¼�����
Event_ptr GetPreNode(EventList L,Event_ptr p);//��ȡ��ǰ�¼�ǰ���һ���¼�
int Fastest_Window();

/*--------------------main--------------------*/
int main()
{
	srand((unsigned int)time(NULL));
	OpenForDay();
	Simulation();
	return 0;
}
/*-------------------END--------------------*/

/*-----------------��������-----------------*/
/*��ʼ������ģ����*/
void OpenForDay()
{
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	//��ʼ���¼���
	Ev = InitList(Ev);
	//��ʼ�������ڶ���
	WindowsNum = Get_WindowsNum();
	InitQueue(WindowsNum);
	//��ʼ����������ʷ��¼
	InitHistory(WindowsNum);
	return;
}

/*����ģ����*/
void Simulation()
{
	while(Ev->next!=NULL)
		Event_Drive(Ev->next);
	Interact();
	return;
}

/*��������Լ���������*/
void Interact()
{
	int window;
	while(1)
	{
		printf("��������鿴ҵ������ʷ�Ĵ��ڣ�����0�˳�����");
		scanf("%d",&window);
		if(window>=1&&window<=WindowsNum)
		{
			window--;
			PrintHistory(window);
		}else if(window == 0)
		{
			break;
		}else
		{
			printf("������Ĵ��ڲ����ڣ�����");
		}
		system("pause");
		system("cls");
		printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	}
	
}

/*�¼�������*/
void Event_Drive(Event_ptr p)
{
	if(p!=NULL)
	{
		if(p->EventType == 0)
			Arrival_Event(Ev,p);	//�������¼�
		else
			Leave_Event(Ev,p);		//�����뿪�¼�
		Sort_Occurtime(Ev);
		Ev = EventDelete(Ev);
	}else
		printf("The event is empty!!!\n");
	return;
}

/*�����¼�����*/
void Arrival_Event(EventList L,Event_ptr p)
{
	int Occurtime = rand()%MAX_CUSTOMERS_ARRIVAL+1;		//�����������һ�������¼������ʱ��
	int Duration = rand()%MAX_DURATION+1;				//�����������¼��Ŀͻ���ҵ����ʱ��
	int window = Fastest_Window();;
	Occurtime += p->OccurTime;		//�������ڴ������������¼��ķ����¼�������һ�������¼��ķ����¼�
	if(Occurtime<=CloseTime)
		EventInsert(Ev,Occurtime,0);
	CustomerNum++;
	EnQueue(p->OccurTime,Duration,window);			//�����û�������촰�ڶ����Ŷ�
	EventInsert(Ev,p->OccurTime+Duration,window);	//����ղ�����û����뿪�¼�
	return;
}

/*�����뿪�¼�*/
void Leave_Event(EventList L,Event_ptr p)
{
	Person people;
	int window = p->EventType;
	DeQueue(window,&people);		//����������Ŀͻ��뿪����
	HistoryInsert(window,people,p->OccurTime);	//����ָ�����ڵ���ʷ��¼
	TotalTimes += people.Duration;	//������ͻ�����ҵ���ʱ�����������ҵ����ʱ��
}

/*��ʼ���¼���*/
EventList InitList(EventList L)
{
	Event_ptr ev;	//event�ļ�д
	L = (EventList)malloc(sizeof(Event));
	L->next = NULL;
	//����һ���û������¼������¼���
	EventInsert(L,BeginTime,0);	
	return L;
}

/*��ʼ�������ڶ���*/
void InitQueue(int WindowsNum)
{
	int i;
	//�൱�ڶ��� : Window_Queue*Windows[WindowsNum],ֻ����[]�ﲻ��Ϊ����������ֻ�������ַ���
	Windows = (Window_Queue*)malloc(WindowsNum*sizeof(Window_Queue));
	//��ʼ��ÿ�����ڵĶ���
	Window_Queue *Window_ptr = Windows;
	for(i=0;i<WindowsNum;i++,Window_ptr++)
	{
		Window_ptr->rear = Window_ptr->front = 0;
	}
	return;
}

/*��ʼ����������ʷ��¼*/
void InitHistory(int WindowsNum)
{
	int i;
	All_History = (HistoryList*)malloc(WindowsNum*sizeof(HistoryList));
	/*��ʼ��ÿ�����ڵ���ʷ��¼*/
	for(i=0;i<WindowsNum;i++)
	{
		All_History[i] = (HistoryList)malloc(sizeof(History));
		All_History[i]->next = NULL;
		All_History[i]->AllNum = 0;		//��������ڵĽӴ��ͻ���ʷ�����ŵ�ͷ����AllNum��
	}
	return;
}

/*�������β�巨*/
void EventInsert(EventList L,int Occurtime,int eventType)
{
	Event_ptr new_ev,ev;
	new_ev = (EventList)malloc(sizeof(Event));
	new_ev->OccurTime = Occurtime;
	new_ev->EventType = eventType;
	/*��ָ��ָ�����һ�����*/
	ev = L;
	while(ev->next!=NULL)
	{
		ev = ev->next;
	}
	/*��������һ�����¼�*/
	new_ev->next = ev->next;
	ev->next = new_ev;
	return;
}

/*����ָ�����ڵ���ʷ��¼*/
void HistoryInsert(int window,Person people,int occurtime)
{
	HistoryList L,p,new_history;
	window--;
	L = All_History[window];	//��Lָ��Ҫ����Ĵ��ڵ���ʷ��¼
	/*�������β�巨*/
	new_history = (HistoryList)malloc(sizeof(History));
	new_history->people = people;
	new_history->leave_time = occurtime;
	L->AllNum++;
	p = L;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	new_history->next = p->next;
	p->next = new_history;
	return;
}

/*�ͻ�������촰�ڶ����Ŷ�*/
void EnQueue(int OccurTime,int Duration,int window)
{
	int FastWindow = window-1;			//��ΪҪ���������±꣬����Ҫ-1
	int queue_len = (Windows[FastWindow].rear - Windows[FastWindow].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
	if(Windows[FastWindow].front == (Windows[FastWindow].rear+1)%MAX_CUSTOMERS)
		printf("�˶�������");
	Windows[FastWindow].customer[Windows[FastWindow].rear].ArrivalTime = OccurTime;
	Windows[FastWindow].customer[Windows[FastWindow].rear].Duration = Duration;
	Windows[FastWindow].customer[Windows[FastWindow].rear].num = CustomerNum;
	Windows[FastWindow].rear = (Windows[FastWindow].rear+1) % MAX_CUSTOMERS;
	return;
}

/*ɾ����һ���¼�*/
EventList EventDelete(EventList L)
{
	Event_ptr ev;
	ev = L->next;
	L->next = ev->next;
	free(ev);
	ev = NULL;
	return L;
}

/*����������Ŀͻ��뿪����*/
void DeQueue(int window,Person *person_ptr)
{
	window--;
	if(Windows[window].front == Windows[window].rear)
	{
		printf("�����ǿյģ����ܳ����ˣ�����");
		return;
	}
	*person_ptr = Windows[window].customer[Windows[window].front];	//��ȡ����ͻ�����Ϣ
	Windows[window].front = (Windows[window].front+1) % MAX_CUSTOMERS;
	return;
}

/*��ӡ�¼���*/
void PrintList(EventList L)
{
	int len=0;
	Event_ptr p = L->next;
	FILE *fp;
  	
	len = Get_Len(L);
  	printf("\n�˱��й���%d����¼:\n",len);
  	
  	if (p!=NULL){	
    	do{
			printf("%d\t %d\n",p->OccurTime,p->EventType);
       		p=p->next;
       	}while (p!=NULL);
  	}
}

/*��ӡ���ж���*/
void PrintQueue(int window)
{
	int queue_len = (Windows[window].rear - Windows[window].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
	int i = Windows[window].front;
	while((i%MAX_CUSTOMERS)!=Windows[window].rear)
	{
		printf("���: %d\t���ڣ�%d\t����ʱ�䣺%d\t����ʱ��:%d\n",Windows[window].customer[i].num,window,Windows[window].customer[i].ArrivalTime,Windows[window].customer[i].Duration);
		i++;
	}

	return;
}


/**/
void PrintAllQueue(int WindowsNum)
{
	int i=0;
	for(i=0;i<WindowsNum;i++)
	{
		PrintQueue(i);
		printf("\n\n\n");
	}
		
	
	return;
}

void PrintHistory(int window)
{
	HistoryList L,p;
	int arrival_hour,arrival_min;
	int leave_hour,leave_min; 
	Person people;
	L = All_History[window];
	int Num = L->AllNum;
	printf("\n\n���մ���ҵ����ʱ��: %d����\t\t���տͻ�����:     %d��\n",TotalTimes,CustomerNum);
	printf("�������п�ҵʱ��:   8:00\t\t��������Ъҵʱ��: %d:%d\n",CloseTime/60+8,CloseTime%60);
	printf("\n --------------------%d�Ŵ��ڹ�������%dλ�ͻ�������---------------------\n",window+1,Num);
	p = L->next;
	printf("���������������������������Щ������������������������Щ������������������������Щ��������������������������������Щ�������������������������\n");
	printf("���ͻ����    ��������    ������ʱ��    ������ҵ��ʱ��    ���뿪ʱ��    ��\n");
	while(p!=NULL)
	{
		people = p->people;
		arrival_hour = people.ArrivalTime/60+8;
		arrival_min = people.ArrivalTime%60;
		leave_hour = p->leave_time/60+8;
		leave_min = p->leave_time%60;
		printf("���������������������������੤�����������������������੤�����������������������੤�������������������������������੤������������������������\n");
		printf("��%-12d��%-12d��%-2.2d:%-9.2d��%-16d��%-2.2d:%-9.2d��\n",people.num,window+1,arrival_hour,arrival_min,people.Duration,leave_hour,leave_min);
		p = p->next;
	}
	printf("���������������������������ة������������������������ة������������������������ة��������������������������������ة�������������������������\n");
	printf(" ---------------------------------------------------------------------\n"); 
	return;
}

/*���û��������д�������*/
int Get_WindowsNum()
{
	int num;
	printf("������BANK�Ĵ������������Ϊ%d��: ",MAX_WINDOWS_NUM);
	while(1)
	{
		scanf("%d",&num);
		if(num>MAX_WINDOWS_NUM)
		{
			system("cls");
			printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
			printf("������Ĵ�����������󴰿���%d���������������룺",MAX_WINDOWS_NUM);
		}else
			break;	
	}
	system("cls");
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	return num;
}

/*����Occurtime��������*/
void Sort_Occurtime(EventList L)
{
    int i,j,len;
    len = Get_Len(L);		//��������ȣ�����ͷ��㣩
    Event_ptr p,p_next,pre_p;
    p = L->next;
    for(i=0;i<len-1;i++)	//��������Ϊ6�����һ�����ò�������������5�ξ͹��ˣ�
    {
        j = len - i -1;		//ÿѭ��һ�Σ����ǾͿ����ٱȽ�һ��Ԫ�أ���Ϊÿ�δ�Ķ��ᱻ�ĵ����棬û��Ҫ�ڱȽ�
        while(p->next != NULL && j!=0)
        {
            j--;
            p_next = p->next;
            if(p->OccurTime > p_next->OccurTime)
            {
                pre_p = GetPreNode(L,p);
                pre_p->next = p_next;
                p->next = p_next->next;
                p_next->next = p;
            }else
            {
                p = p_next;
            }
        }
        p = L->next;
    }
    return;
}

/*��ȡ�¼�����*/
int Get_Len(EventList L)
{
	int len = 0;
	Event_ptr p = L->next;
	while(p != NULL){
		p = p->next;
		len++;
	}
	return len;
}

/*��ȡǰһ���¼����*/
Event_ptr GetPreNode(EventList L,Event_ptr p)
{
	Event_ptr temp;
	temp = L;
	while(temp->next!=p)
	{
		temp = temp->next;
	}
	return temp;
}

/*�����ĸ���������Ҫ��ʱ������*/
int Fastest_Window()
{
	int i,j,queue_len,window_number=0,A,B;	//i,j����ѭ������,queue_len�Ǽ�¼ÿ�����еĳ���,window_number�Ǽ�¼���ĸ�����,A��B���ڱȽ�
	int *window_time = malloc(WindowsNum*sizeof(int));//�öѷ���һ�����飬���ÿ������ʣ��Ĵ���ʱ�䣬����֮��Ƚ�
	for(i=0;i<WindowsNum;i++)
	{
		if(Windows[i].front == Windows[i].rear)//����˴���Ϊ�գ���Ϊ0
			window_time[i] = 0;
		else
		{
			queue_len = (Windows[i].rear - Windows[i].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
			window_time[i] = 0;
			/*ѭ���˴��������Ŷӵ�ÿ���ͻ�����Ϣ��������ʱ�������*/
			for(j=0;j<queue_len;j++)
			{
				window_time[i] += Windows[i].customer[j].Duration;
			}
		}
	}
	/*���бȽϣ��������Ĵ���*/
	for(i=0;i<WindowsNum;i++)
	{
		if(window_time[window_number]>=window_time[i])
			window_number = i;
	}
	return window_number+1;

}