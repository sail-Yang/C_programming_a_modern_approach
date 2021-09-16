## sizeof 与宏

###  用宏来定义数组长度

```c
#define N 10
...
int a[N];
```

牵一发而动全身，用宏只要改一个量就行。若想直观感受到宏和数组结合的好处，咱们直接看reverse.c文件就行。

###  sizeof对宏的替代

在前面我们知道sizeof可以返回字节数。所以sizeof可以用来确定数组的大小，还可以计算数组元素的大小。所以我们可以通过下面这种方式来计算数组长度：

```c
sizeof(a)/sizeof(a[0])
```

上式就是程序员一般得到数组长度的方法。下面我们再来看一看数组a的清零操作：

```c
for (i = 0;i < sizeof(a) / sizeof(a[0]);i++)
	a[i]=0
```

使用这种方法的好处显而易见，就是**即使日后数组长度要改变，也不用改变循环。**在这里sizeof的方法是要优于宏的，但是我们还是要改进一下这种方法：因为sizeof返回的是无符号整型，而int型是有符号整型，，为了避免警告，我们会进行强制数据转换:

```c
for (i = 0;(int) (i < sizeof(a) / sizeof(a[0]));i++)
	a[i]=0
```

但是还是写起来不太方便，我们最后这样写：

```c
#define SIZE ((int) (sizeof(a)/sizeof(a[0])))

for (i=0;i<SIZE;i++)
    a[i]=0;
```

我们这里其实又使用了宏，其实最终的方法还要在后面讲宏的定义时讲到。

---



##  for循环与数组的结合使用

###  常用示例

许多程序中包含的循环都是为了对数组中的每个元素执行一些操作。下面给出了一些常见的操作示例：

```c
for (i=0;i<N;i++)
    a[i] = 0;
for (i = 0;i<N;i++)
    scanf("%d",&a[i]);
for (i = 0;i<N;i++)
    sum += a[i];
```

###  超出下标范围之后

C语言不会检查下标范围，如果下表超出范围，结果会是怎样的呢？

```c
int a[10],i;
for (i=1;i<=10;i++)
    a[i]=0;
```

这个表面上正确的式子实际上产生了一个无限循环。数值0会被放进a[10]，可是a[10]并不存在，所以元素a[9]后数值0会立刻进入内存。如果内存中的变量i位置在a[9]之后，那么变量i将会被重置为0，进而导致循环重新开始。

## 程序示例

###  program1: checks numbers for repeated digits

```c
/*checks numbers for repeated digits*/
#include <stdio.h>
#include <stdbool.h>	/*C99 only*/
int main(void){
	bool digit_seen[10] = {false};
	int digit;
	long n;
	
	printf("Enter a number: ");
	scanf("%ld",&n);
	
	while (n>0){
		digit = n % 10;
		if (digit_seen[digit])
			break;
		digit_seen[digit] = true;
		n /= 10;
	}
	
	if (n>0)
		printf("Repeatepd digit\n");
	else
		printf("No repeated digit\n");
		
	return 0;
} 
```

程序采用布尔值跟踪数据中出现的数字，digit_seen的数组元素存储10个数字，一开始每个元素的值都为假。（tips:实际上第五行只是初始化了第一个值，编译器会自动把其它元素初始化为0，而**0=false**）

作为一个初学者，觉得这个好妙啊！！！

###  program2：发牌

```c
/*Deals a random hand of cards*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main(void){
	bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
	int num_cards, rank, suit;
	const char rank_code[] = {'2','3','4','5','6','7','8','9','t','j','q','k','a'};
	const char suit_code[] = {'c','d','h','s'};
	
	srand((unsigned) time(NULL));/*time函数返回当前时间，传递给srand函数可以避免程序每次运行时产生同样的牌*/
	
	printf("Enter number of cards in hand:");
	scanf("%d",&num_cards);
	
	printf("Your hands");
	while (num_cards > 0){
		suit = rand()% NUM_SUITS; /*rand函数产生伪随机数，采用%,可以缩放rand，比如此例中的0~3,0~12*/
		rank = rand()% NUM_RANKS;
		if (!in_hand[suit][rank]){
			in_hand[suit][rank] = true;
			num_cards--;
			printf("%c%c ",rank_code[rank],suit_code[suit]);
		}
	}
	printf("\n");
	
	return 0;
}
```

