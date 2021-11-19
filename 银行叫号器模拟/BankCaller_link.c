/*�����2003� 201205130 ���нк���ģ��������*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_DURATION 40 			//�����������ʱ�䣬��λΪmin
#define MAX_WINDOWS_NUM	10			//��������ҵ�񴰿�����
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
typedef struct node
{
	Person customer;		//����Ԫ������
	struct node *next;
}QNode,*QueuePtr;
typedef struct queue
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

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
Person *Windows = NULL;					//�������ڴ�������Ĵ���
LinkQueue Q ;							//����һ���ܶ���
HistoryList *All_History = NULL;		//�ö�ʵ��һ���洢ÿ��������ʷ���������
int *LeavalTime = NULL;

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
void InitQueue();					//��ʼ���ܶ���
void InitHistory(int WindowsNum);	//��ʼ����������ʷ��¼
void InitWindows();					//��ʼ��������
void InitLeavalTime();
/*�Խṹ��Ĳ�������*/
void EventInsert(EventList L,int Occurtime,int eventType);	//�������������
EventList EventDelete(EventList L);							//ɾ����һ���¼�
void EnQueue(int ArrivalTime,int Duration);					//���ͻ��嵽�ܶ���
void DeQueue(Person *person_ptr);							//����������Ŀͻ��뿪����
void HistoryInsert(int window,Person people,int occurtime);	//����ָ�����ڵ���ʷ��¼
void ClearList(EventList L);								//����¼���
/*С���*/
int Get_WindowsNum();		//����ܴ�������
int EmptyWindow();			//���ؿյĴ��ڣ����û�з���0
Event_ptr GetPreNode(EventList L,Event_ptr p);	//��ȡ��ǰ����ǰһ�����
void Sort_Occurtime(EventList L);	//���ݷ����¼�����
int Get_Len(EventList L);			//��ȡ�¼�����
void ClearBank();			//������У�����

/*�������*/
//void PrintList(EventList L);		//��ӡ�¼������Ե�ʱ����
//void PrintQueue();
void PrintHistory(int window);

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
	InitQueue();
	//��ʼ����������ʷ��¼
	InitHistory(WindowsNum);
	InitWindows();
	InitLeavalTime();
	return;
}

/*����ģ����*/
void Simulation()
{
	while(Ev->next!=NULL)
	{
		Event_Drive(Ev->next);
		//PrintList(Ev);
		//PrintQueue();
	}
	
	Interact();
	return;
}

/*��������Լ���������*/
void Interact()
{
	int window;
	system("pause");
	system("cls");
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
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

/*�¼�����*/
void Event_Drive(Event_ptr p)
{
	if(p!=NULL)
	{
		if(p->EventType == 0)
			Arrival_Event(Ev,p);	//�������¼�
		else
			Leave_Event(Ev,p);		//�����뿪�¼�
	}else
		printf("The event is empty!!!\n");
	return;
}

void Arrival_Event(EventList L,Event_ptr p)
{
	int Occurtime = rand()%MAX_CUSTOMERS_ARRIVAL+1;		//�����������һ�������¼������ʱ��
	int Duration = rand()%MAX_DURATION+1;				//�����������¼��Ŀͻ���ҵ����ʱ��
	Person people;
	int window = EmptyWindow();							//���ؿյĴ��ڣ����û�з���0
	printf("%d:%.2dʱ���ͻ�%d��������...\n\n",p->OccurTime/60+8,p->OccurTime%60,CustomerNum+1); 
	Occurtime += p->OccurTime;		//�������ڴ������������¼��ķ����¼�������һ�������¼��ķ����¼�
	if(Occurtime<=CloseTime)
	{
		EventInsert(Ev,Occurtime,0);
	}
		
	CustomerNum++;
	EnQueue(p->OccurTime,Duration);
	if(window!=0)
	{
		DeQueue(&people);
		Windows[window-1] = people;
		if(p->OccurTime<CloseTime-5)
			printf("%d:%.2dʱ���ͻ�%d��ʼ�ڴ���%d����ҵ��...\n\n",people.ArrivalTime/60+8,people.ArrivalTime%60,people.num,window);
		EventInsert(Ev,people.ArrivalTime+people.Duration,window);
	}
	Sort_Occurtime(Ev);
	Ev = EventDelete(Ev);
	return;
}

/*�����뿪�¼�*/
void Leave_Event(EventList L,Event_ptr p)
{
	Person people;
	int window = p->EventType;
	people = Windows[window-1];
	if(p->OccurTime<=CloseTime)
	{
		HistoryInsert(window,people,p->OccurTime);	//����ָ�����ڵ���ʷ��¼
		LeavalTime[window-1] = p->OccurTime;
		TotalTimes += people.Duration;	//������ͻ�����ҵ���ʱ�����������ҵ����ʱ��
		Windows[window-1].num = 0;
		printf("%d:%.2dʱ���ͻ�%d�뿪����\n\n",p->OccurTime/60+8,p->OccurTime%60,people.num);
		if(Q.front != Q.rear)
		{
			DeQueue(&people);
			Windows[window-1] = people;
			if(p->OccurTime<CloseTime-5)
				printf("%d:%.2dʱ���ͻ�%d��ʼ�ڴ���%d����ҵ��...\n\n",LeavalTime[window-1]/60+8,LeavalTime[window-1]%60,people.num,window);
			EventInsert(Ev,LeavalTime[window-1]+people.Duration,window);
		}
		TotalTimes += people.Duration;
	}else
	{
		HistoryInsert(window,people,CloseTime);	//����ָ�����ڵ���ʷ��¼
		LeavalTime[window-1] = CloseTime;
		Windows[window-1].num = 0;
		printf("%d:%.2dʱ���ͻ�%d�뿪����\n\n",CloseTime/60+8,CloseTime%60,people.num);
		ClearList(Ev);
		ClearBank();
		return;
	}
	Sort_Occurtime(Ev);
	Ev = EventDelete(Ev);
	return;
	
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

/*��ʼ���ܶ���*/
void InitQueue()
{
	QueuePtr Head_Node;
	Head_Node = (QueuePtr)malloc(sizeof(QNode));
	Head_Node->next = NULL;
	Q.front = Head_Node;
	Q.rear = Q.front;
	return;
}

/*��ʼ����ʷ��¼*/
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

/*��ʼ��������*/
void InitWindows()
{
	int i=0;
	Windows = (Person*)malloc(WindowsNum*sizeof(Person));
	for(i=0;i<WindowsNum;i++)
	{
		Windows[i].num = 0;
	}
	return;
}

void InitLeavalTime()
{
	int i;
	LeavalTime = (int*)malloc(WindowsNum*sizeof(int));
	for(i=0;i<WindowsNum;i++)
	{
		LeavalTime[i] = 0;
	}
	return;
}

/*�����¼����¼���*/
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

/*���ͻ����뵽�ܶ���*/
void EnQueue(int ArrivalTime,int Duration)
{
	QueuePtr new_customer;
	new_customer = (QueuePtr)malloc(sizeof(QNode));
	new_customer->customer.ArrivalTime = ArrivalTime;
	new_customer->customer.Duration = Duration;
	new_customer->customer.num = CustomerNum;
	new_customer->next = Q.rear->next;
	Q.rear->next = new_customer;
	Q.rear = new_customer;
	return;
}

void DeQueue(Person *person_ptr)
{
	QueuePtr node;
	if(Q.front == Q.rear||Q.rear == NULL)
	{
		printf("�����ǿյģ����ܳ����ˣ�����");
		return;
	}
	*person_ptr = Q.front->next->customer;	//��ȡ����ͻ�����Ϣ
	node = Q.front->next;
	Q.front->next = node->next;
	if(node==Q.rear)
		Q.rear = Q.front;
	free(node);
	node = NULL;
	return;
}

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

void ClearList(EventList L)
{
	Event_ptr ev;
	ev = L->next;
	while(ev!=NULL)
	{
		L->next = ev->next;
		free(ev);
		ev = L->next;
	}
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

/*���ؿյĴ��ڣ����û�пյĴ��ڷ���0*/
int EmptyWindow()
{
	int i;
	for(i=0;i<WindowsNum;i++)
	{
		if(Windows[i].num==0)
			return i+1;
	}
	return 0;
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

/*��ӡ�¼���
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
}*/

/*��ӡ�ܶ���
void PrintQueue()
{
	QueuePtr node = Q.front->next;
	while(node!=NULL)
	{
		printf("\n���: %d\t����ʱ�䣺%d\t����ʱ��:%d\n",node->customer.num,node->customer.ArrivalTime,node->customer.Duration);
		node = node->next;
	}
	return;
}*/

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

/*���������ʣ�����*/
void ClearBank()
{
	Person people;
	if(Q.front != Q.rear)
	{
		DeQueue(&people);
		//HistoryInsert(window,people,CloseTime);	//����ָ�����ڵ���ʷ��¼
		printf("%d:%.2dʱ���ͻ�%d�뿪����\n\n",CloseTime/60+8,CloseTime%60,people.num);
	}
	int i;
	for(i=0;i<WindowsNum;i++)
	{
		if(Windows[i].num!=0)
		{
			people = Windows[i];
			Windows[i].num=0;
			printf("%d:%.2dʱ���ͻ�%d�뿪����\n\n",CloseTime/60+8,CloseTime%60,people.num);
		}
	}
	printf("�����ѹ��ţ�����\n");
}
