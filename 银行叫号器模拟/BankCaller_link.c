/*计算机2003杨帆 201205130 银行叫号器模拟链队列*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_DURATION 40 			//定义最长事务处理时间，单位为min
#define MAX_WINDOWS_NUM	10			//定义银行业务窗口数量
#define MAX_CUSTOMERS_ARRIVAL 10	//设置用户达到银行最大间隔时间
/*--------------结构体声明--------------*/
/*定义事件链表，存放事件*/
typedef struct linklist
{
	int OccurTime;			//事件发生的时间
	int EventType;			//事件类型，0表示到达事件，others表示各窗口的离开事件
	struct linklist *next;
}Event,*EventList;
typedef Event *Event_ptr;	//定义一个指向时间结点的指针

/*定义窗口队列的元素：每个排队的客户信息*/
typedef struct person
{
	int ArrivalTime;	//客户的到达时间
	int Duration;		//每个客户处理业务的时间，这是随机的
	int num;			//每个客户取到的号，标识是第几个到银行的
}Person;

/*定义每个窗口的队列(循环队列)*/
typedef struct node
{
	Person customer;		//定义元素数组
	struct node *next;
}QNode,*QueuePtr;
typedef struct queue
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

/*每个窗口接受的顾客的历史（链表）*/
typedef struct history
{
	Person people;			//一个客户的信息
	int AllNum;				//放在头结点，表示这个窗口今天接待了多少客人
	int leave_time;
	struct history *next;
}History;
typedef History * HistoryList;

/*-----------------全局变量-----------------*/
int TotalTimes = 0,CustomerNum = 0;		//累计用户逗留时间，客户数
int BeginTime = 0,CloseTime = 630;		//1110min，代表银行下班时间是18:30
int WindowsNum = 0;						//银行窗口数量
EventList Ev;							//事件链表
Person *Windows = NULL;					//创建正在处理事务的窗口
LinkQueue Q ;							//声明一个总队列
HistoryList *All_History = NULL;		//用堆实现一个存储每个窗口历史链表的数组
int *LeavalTime = NULL;

/*-----------------函数声明-----------------*/
/*主要函数*/
void OpenForDay();					//初始化银行模拟器
void Simulation();					//银行模拟器
void Interact();					//交互面板以及交互操作
void Event_Drive(Event_ptr p);		//事件驱动器
void Arrival_Event(EventList L,Event_ptr p);	//处理到达事件
void Leave_Event(EventList L,Event_ptr p);		//处理离开事件
/*初始化函数*/
EventList InitList(EventList L);	//初始化事件表
void InitQueue();					//初始化总队列
void InitHistory(int WindowsNum);	//初始化各窗口历史记录
void InitWindows();					//初始化各窗口
void InitLeavalTime();
/*对结构体的操作函数*/
void EventInsert(EventList L,int Occurtime,int eventType);	//插入事务到事务表
EventList EventDelete(EventList L);							//删除第一个事件
void EnQueue(int ArrivalTime,int Duration);					//将客户插到总队列
void DeQueue(Person *person_ptr);							//处理完事务的客户离开队伍
void HistoryInsert(int window,Person people,int occurtime);	//插入指定窗口的历史记录
void ClearList(EventList L);								//清空事件表
/*小组件*/
int Get_WindowsNum();		//获得总窗口数量
int EmptyWindow();			//返回空的窗口，如果没有返回0
Event_ptr GetPreNode(EventList L,Event_ptr p);	//获取当前结点的前一个结点
void Sort_Occurtime(EventList L);	//根据发生事件排序
int Get_Len(EventList L);			//获取事件表长度
void ClearBank();			//清空银行，关门

/*输出函数*/
//void PrintList(EventList L);		//打印事件表，调试的时候用
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

/*-----------------函数定义-----------------*/
/*初始化银行模拟器*/
void OpenForDay()
{
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	//初始化事件表
	Ev = InitList(Ev);
	//初始化各窗口队列
	WindowsNum = Get_WindowsNum();
	InitQueue();
	//初始化各窗口历史记录
	InitHistory(WindowsNum);
	InitWindows();
	InitLeavalTime();
	return;
}

/*银行模拟器*/
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

/*交互面板以及交互操作*/
void Interact()
{
	int window;
	system("pause");
	system("cls");
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	while(1)
	{
		printf("请输入想查看业务处理历史的窗口（输入0退出）：");
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
			printf("您输入的窗口不存在！！！");
		}
		system("pause");
		system("cls");
		printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	}
	
}

/*事件驱动*/
void Event_Drive(Event_ptr p)
{
	if(p!=NULL)
	{
		if(p->EventType == 0)
			Arrival_Event(Ev,p);	//处理到达事件
		else
			Leave_Event(Ev,p);		//处理离开事件
	}else
		printf("The event is empty!!!\n");
	return;
}

void Arrival_Event(EventList L,Event_ptr p)
{
	int Occurtime = rand()%MAX_CUSTOMERS_ARRIVAL+1;		//随机生成与下一个到达事件相隔的时间
	int Duration = rand()%MAX_DURATION+1;				//随机生成这个事件的客户的业务处理时间
	Person people;
	int window = EmptyWindow();							//返回空的窗口，如果没有返回0
	printf("%d:%.2d时，客户%d到达银行...\n\n",p->OccurTime/60+8,p->OccurTime%60,CustomerNum+1); 
	Occurtime += p->OccurTime;		//加上正在处理的这个到达事件的发生事件就是下一个到达事件的发生事件
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
			printf("%d:%.2d时，客户%d开始在窗口%d办理业务...\n\n",people.ArrivalTime/60+8,people.ArrivalTime%60,people.num,window);
		EventInsert(Ev,people.ArrivalTime+people.Duration,window);
	}
	Sort_Occurtime(Ev);
	Ev = EventDelete(Ev);
	return;
}

/*处理离开事件*/
void Leave_Event(EventList L,Event_ptr p)
{
	Person people;
	int window = p->EventType;
	people = Windows[window-1];
	if(p->OccurTime<=CloseTime)
	{
		HistoryInsert(window,people,p->OccurTime);	//插入指定窗口的历史记录
		LeavalTime[window-1] = p->OccurTime;
		TotalTimes += people.Duration;	//将这个客户办理业务的时间加入今天办理业务总时间
		Windows[window-1].num = 0;
		printf("%d:%.2d时，客户%d离开银行\n\n",p->OccurTime/60+8,p->OccurTime%60,people.num);
		if(Q.front != Q.rear)
		{
			DeQueue(&people);
			Windows[window-1] = people;
			if(p->OccurTime<CloseTime-5)
				printf("%d:%.2d时，客户%d开始在窗口%d办理业务...\n\n",LeavalTime[window-1]/60+8,LeavalTime[window-1]%60,people.num,window);
			EventInsert(Ev,LeavalTime[window-1]+people.Duration,window);
		}
		TotalTimes += people.Duration;
	}else
	{
		HistoryInsert(window,people,CloseTime);	//插入指定窗口的历史记录
		LeavalTime[window-1] = CloseTime;
		Windows[window-1].num = 0;
		printf("%d:%.2d时，客户%d离开银行\n\n",CloseTime/60+8,CloseTime%60,people.num);
		ClearList(Ev);
		ClearBank();
		return;
	}
	Sort_Occurtime(Ev);
	Ev = EventDelete(Ev);
	return;
	
}

/*初始化事件表*/
EventList InitList(EventList L)
{
	Event_ptr ev;	//event的简写
	L = (EventList)malloc(sizeof(Event));
	L->next = NULL;
	//将第一个用户到达事件插入事件表
	EventInsert(L,BeginTime,0);
	
	return L;
}

/*初始化总队列*/
void InitQueue()
{
	QueuePtr Head_Node;
	Head_Node = (QueuePtr)malloc(sizeof(QNode));
	Head_Node->next = NULL;
	Q.front = Head_Node;
	Q.rear = Q.front;
	return;
}

/*初始化历史记录*/
void InitHistory(int WindowsNum)
{
	int i;
	All_History = (HistoryList*)malloc(WindowsNum*sizeof(HistoryList));
	/*初始化每个窗口的历史记录*/
	for(i=0;i<WindowsNum;i++)
	{
		All_History[i] = (HistoryList)malloc(sizeof(History));
		All_History[i]->next = NULL;
		All_History[i]->AllNum = 0;		//将这个窗口的接待客户历史人数放到头结点的AllNum上
	}
	return;
}

/*初始化各窗口*/
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

/*插入事件到事件表*/
void EventInsert(EventList L,int Occurtime,int eventType)
{
	Event_ptr new_ev,ev;
	new_ev = (EventList)malloc(sizeof(Event));
	new_ev->OccurTime = Occurtime;
	new_ev->EventType = eventType;
	/*让指针指向最后一个结点*/
	ev = L;
	while(ev->next!=NULL)
	{
		ev = ev->next;
	}
	/*在最后插入一个新事件*/
	new_ev->next = ev->next;
	ev->next = new_ev;
	return;
}

/*删除第一个事件*/
EventList EventDelete(EventList L)
{
	Event_ptr ev;
	ev = L->next;
	L->next = ev->next;
	free(ev);
	ev = NULL;
	return L;
}

/*将客户插入到总队列*/
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
		printf("队列是空的，不能出列了！！！");
		return;
	}
	*person_ptr = Q.front->next->customer;	//提取这个客户的信息
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
	L = All_History[window];	//将L指向要处理的窗口的历史记录
	/*单链表的尾插法*/
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

/*让用户输入银行窗口数量*/
int Get_WindowsNum()
{
	int num;
	printf("请输入BANK的窗口数量（最多为%d）: ",MAX_WINDOWS_NUM);
	while(1)
	{
		scanf("%d",&num);
		if(num>MAX_WINDOWS_NUM)
		{
			system("cls");
			printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
			printf("您输入的窗口数超出最大窗口数%d！！！请重新输入：",MAX_WINDOWS_NUM);
		}else
			break;	
	}
	system("cls");
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	return num;
}

/*返回空的窗口，如果没有空的窗口返回0*/
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

/*获取前一个事件结点*/
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

/*依据Occurtime升序排列*/
void Sort_Occurtime(EventList L)
{
    int i,j,len;
    len = Get_Len(L);		//获得链表长度（不算头结点）
    Event_ptr p,p_next,pre_p;
    p = L->next;
    for(i=0;i<len-1;i++)	//设链表长度为6，最后一个不用操作，所以咱们5次就够了，
    {
        j = len - i -1;		//每循环一次，我们就可以少比较一个元素，因为每次大的都会被拍到后面，没必要在比较
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

/*获取事件表长度*/
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

/*打印事件表
void PrintList(EventList L)
{
	int len=0;
	Event_ptr p = L->next;
	FILE *fp;
  	
	len = Get_Len(L);
  	printf("\n此表中共有%d个记录:\n",len);
  	
  	if (p!=NULL){	
    	do{
			printf("%d\t %d\n",p->OccurTime,p->EventType);
       		p=p->next;
       	}while (p!=NULL);
  	}
}*/

/*打印总队列
void PrintQueue()
{
	QueuePtr node = Q.front->next;
	while(node!=NULL)
	{
		printf("\n编号: %d\t到达时间：%d\t处理时间:%d\n",node->customer.num,node->customer.ArrivalTime,node->customer.Duration);
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
	printf("\n\n今日处理业务总时间: %d分钟\t\t今日客户人数:     %d人\n",TotalTimes,CustomerNum);
	printf("今日银行开业时间:   8:00\t\t今日银行歇业时间: %d:%d\n",CloseTime/60+8,CloseTime%60);
	printf("\n --------------------%d号窗口共处理了%d位客户的事务---------------------\n",window+1,Num);
	p = L->next;
	printf("┌────────────┬────────────┬────────────┬────────────────┬────────────┐\n");
	printf("│客户编号    │处理窗口    │到达时间    │处理业务时间    │离开时间    │\n");
	while(p!=NULL)
	{
		people = p->people;
		arrival_hour = people.ArrivalTime/60+8;
		arrival_min = people.ArrivalTime%60;
		leave_hour = p->leave_time/60+8;
		leave_min = p->leave_time%60;
		printf("├────────────┼────────────┼────────────┼────────────────┼────────────┤\n");
		printf("│%-12d│%-12d│%-2.2d:%-9.2d│%-16d│%-2.2d:%-9.2d│\n",people.num,window+1,arrival_hour,arrival_min,people.Duration,leave_hour,leave_min);
		p = p->next;
	}
	printf("└────────────┴────────────┴────────────┴────────────────┴────────────┘\n");
	printf(" ---------------------------------------------------------------------\n"); 
	return;
}

/*清除银行里剩余的人*/
void ClearBank()
{
	Person people;
	if(Q.front != Q.rear)
	{
		DeQueue(&people);
		//HistoryInsert(window,people,CloseTime);	//插入指定窗口的历史记录
		printf("%d:%.2d时，客户%d离开银行\n\n",CloseTime/60+8,CloseTime%60,people.num);
	}
	int i;
	for(i=0;i<WindowsNum;i++)
	{
		if(Windows[i].num!=0)
		{
			people = Windows[i];
			Windows[i].num=0;
			printf("%d:%.2d时，客户%d离开银行\n\n",CloseTime/60+8,CloseTime%60,people.num);
		}
	}
	printf("银行已关门！！！\n");
}
