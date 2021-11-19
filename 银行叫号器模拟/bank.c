/*计算机2003杨帆 201205130 银行叫号器模拟(循环队列)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_DURATION 40 			//定义最长事务处理时间，单位为min
#define MAX_WINDOWS_NUM	10			//定义银行业务窗口数量
#define MAX_CUSTOMERS 50			//最多每个窗口排多少个人
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
typedef struct queue
{
	Person customer[MAX_CUSTOMERS];		//定义元素数组
	int front;
	int rear;
}Window_Queue;

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
Window_Queue* Windows = NULL;			//用堆实现一个存储指向窗口队列指针的数组
HistoryList *All_History = NULL;		//用堆实现一个存储每个窗口历史链表的数组

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
void InitQueue(int WindowsNum);		//初始化各窗口队列
void InitHistory(int WindowsNum);	//初始化各窗口历史记录
/*对结构体的操作函数*/
void EventInsert(EventList L,int Occurtime,int eventType);	//插入事务到事务表
void EnQueue(int OccurTime,int Duration,int window);		//客户进入最快窗口队列排队
void HistoryInsert(int window,Person people,int occurtime);	//插入指定窗口的历史记录
EventList EventDelete(EventList L);							//删除第一个事件
void DeQueue(int window,Person *person_ptr);				//处理完事务的客户离开队伍
/*输出函数*/
void PrintList(EventList L);		//打印事件表，调试的时候用
void PrintQueue();					//打印银行队列，调试的时候用
void PrintAllQueue(int WindowsNum);
void PrintHistory(int window);
/*小组件*/
int Get_WindowsNum();				//让用户输入银行窗口数量
void Sort_Occurtime(EventList L);	//根据发生事件排序
int Get_Len(EventList L);			//获取事件表长度
Event_ptr GetPreNode(EventList L,Event_ptr p);//获取当前事件前面的一个事件
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

/*-----------------函数定义-----------------*/
/*初始化银行模拟器*/
void OpenForDay()
{
	printf("--------------------Welcome to  YANG'S BANK!!!--------------------\n\n");
	//初始化事件表
	Ev = InitList(Ev);
	//初始化各窗口队列
	WindowsNum = Get_WindowsNum();
	InitQueue(WindowsNum);
	//初始化各窗口历史记录
	InitHistory(WindowsNum);
	return;
}

/*银行模拟器*/
void Simulation()
{
	while(Ev->next!=NULL)
		Event_Drive(Ev->next);
	Interact();
	return;
}

/*交互面板以及交互操作*/
void Interact()
{
	int window;
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

/*事件处理器*/
void Event_Drive(Event_ptr p)
{
	if(p!=NULL)
	{
		if(p->EventType == 0)
			Arrival_Event(Ev,p);	//处理到达事件
		else
			Leave_Event(Ev,p);		//处理离开事件
		Sort_Occurtime(Ev);
		Ev = EventDelete(Ev);
	}else
		printf("The event is empty!!!\n");
	return;
}

/*到达事件处理*/
void Arrival_Event(EventList L,Event_ptr p)
{
	int Occurtime = rand()%MAX_CUSTOMERS_ARRIVAL+1;		//随机生成与下一个到达事件相隔的时间
	int Duration = rand()%MAX_DURATION+1;				//随机生成这个事件的客户的业务处理时间
	int window = Fastest_Window();;
	Occurtime += p->OccurTime;		//加上正在处理的这个到达事件的发生事件就是下一个到达事件的发生事件
	if(Occurtime<=CloseTime)
		EventInsert(Ev,Occurtime,0);
	CustomerNum++;
	EnQueue(p->OccurTime,Duration,window);			//将此用户插入最快窗口队列排队
	EventInsert(Ev,p->OccurTime+Duration,window);	//插入刚才这个用户的离开事件
	return;
}

/*处理离开事件*/
void Leave_Event(EventList L,Event_ptr p)
{
	Person people;
	int window = p->EventType;
	DeQueue(window,&people);		//处理完事务的客户离开队伍
	HistoryInsert(window,people,p->OccurTime);	//插入指定窗口的历史记录
	TotalTimes += people.Duration;	//将这个客户办理业务的时间加入今天办理业务总时间
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

/*初始化各窗口队列*/
void InitQueue(int WindowsNum)
{
	int i;
	//相当于定义 : Window_Queue*Windows[WindowsNum],只不过[]里不能为变量，所以只能用这种方法
	Windows = (Window_Queue*)malloc(WindowsNum*sizeof(Window_Queue));
	//初始化每个窗口的队列
	Window_Queue *Window_ptr = Windows;
	for(i=0;i<WindowsNum;i++,Window_ptr++)
	{
		Window_ptr->rear = Window_ptr->front = 0;
	}
	return;
}

/*初始化各窗口历史记录*/
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

/*插入事项，尾插法*/
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

/*插入指定窗口的历史记录*/
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

/*客户进入最快窗口队列排队*/
void EnQueue(int OccurTime,int Duration,int window)
{
	int FastWindow = window-1;			//因为要用于数组下标，所以要-1
	int queue_len = (Windows[FastWindow].rear - Windows[FastWindow].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
	if(Windows[FastWindow].front == (Windows[FastWindow].rear+1)%MAX_CUSTOMERS)
		printf("此队列已满");
	Windows[FastWindow].customer[Windows[FastWindow].rear].ArrivalTime = OccurTime;
	Windows[FastWindow].customer[Windows[FastWindow].rear].Duration = Duration;
	Windows[FastWindow].customer[Windows[FastWindow].rear].num = CustomerNum;
	Windows[FastWindow].rear = (Windows[FastWindow].rear+1) % MAX_CUSTOMERS;
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

/*处理完事务的客户离开队伍*/
void DeQueue(int window,Person *person_ptr)
{
	window--;
	if(Windows[window].front == Windows[window].rear)
	{
		printf("队列是空的，不能出列了！！！");
		return;
	}
	*person_ptr = Windows[window].customer[Windows[window].front];	//提取这个客户的信息
	Windows[window].front = (Windows[window].front+1) % MAX_CUSTOMERS;
	return;
}

/*打印事件表*/
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
}

/*打印银行队列*/
void PrintQueue(int window)
{
	int queue_len = (Windows[window].rear - Windows[window].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
	int i = Windows[window].front;
	while((i%MAX_CUSTOMERS)!=Windows[window].rear)
	{
		printf("编号: %d\t窗口：%d\t到达时间：%d\t处理时间:%d\n",Windows[window].customer[i].num,window,Windows[window].customer[i].ArrivalTime,Windows[window].customer[i].Duration);
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

/*计算哪个窗口所需要的时间最少*/
int Fastest_Window()
{
	int i,j,queue_len,window_number=0,A,B;	//i,j用于循环计数,queue_len是记录每个队列的长度,window_number是记录是哪个窗口,A和B用于比较
	int *window_time = malloc(WindowsNum*sizeof(int));//用堆分配一个数组，存放每个窗口剩余的处理时间，用于之后比较
	for(i=0;i<WindowsNum;i++)
	{
		if(Windows[i].front == Windows[i].rear)//如果此窗口为空，则为0
			window_time[i] = 0;
		else
		{
			queue_len = (Windows[i].rear - Windows[i].front+MAX_CUSTOMERS)%MAX_CUSTOMERS;
			window_time[i] = 0;
			/*循环此窗口正在排队的每个客户的信息，将处理时间加起来*/
			for(j=0;j<queue_len;j++)
			{
				window_time[i] += Windows[i].customer[j].Duration;
			}
		}
	}
	/*进行比较，返回最快的窗口*/
	for(i=0;i<WindowsNum;i++)
	{
		if(window_time[window_number]>=window_time[i])
			window_number = i;
	}
	return window_number+1;

}