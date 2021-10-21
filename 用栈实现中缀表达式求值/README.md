# 前言

&emsp;&emsp;这是数据结构的第二个作业，主要是用链栈和顺序栈分别实现中缀表达式的求值。

# 题目

&emsp;&emsp;用链栈和顺序栈分别实现中缀表达式的求值，要求支持浮点数，表达式以#结束，比如`12.4+6*(7+8)#`

#  细节注意点
&emsp;&emsp;这个小练习的基本思路是用**算符优先**的方式，其具体思路可以看严蔚敏版数据结构的算法3.3，有详细的说明，我这就不详细赘述。这里我主要说一些我遇到的C语言本身的问题。

- 从字符串中切出浮点数并转化为浮点数格式

  &emsp;&emsp;这个是我自己加的功能，老师给的例子是不支持浮点数的，其实加个浮点数也很简单，我来说说我的思路：

  &emsp;&emsp;这个题目首先要求将输入的表达式整个读入到一个字符串，比如`12.4+6.4*(10+3.4)`。我们在转化之前会判断是否是数字，比如i=0的时候，是12.4的1，这个时候就会进行转化。

  &emsp;&emsp;我的想法是用while循环将字符串中的浮点数提取出来读入到一个字符数组里，判断条件是`while((str>='0'&&str<='9')||str=='.')`。然后<u>不要忘了在新的字符数组的末尾加个'\0'</u>，因为之后我们要把这个字符数组作为参数传给**atof（）函数**，其读取停止的条件就有'\0'。经过atof()函数转化，就会生成对应的浮点数。除此之外，为了方便，我们要将下标i自动跳到浮点数下面一个字符，比如我们转化完12.4后，下标i应该到'+'的位置了。这个只要传入指向i的指针就可以解决。具体的代码可以看`double TurnToDouble(char *expression,int *ptr_i)`这个函数。

- 链栈的声明

  &emsp;&emsp;注意，链栈是可以不用头结点的，具体的声明方法如下：

  ```c
  typedef struct num
  {
  	ElemType data;
  	struct num *next;
  }Num,*Number;
  
  typedef struct numstack
  {
  	Number top;
  	int len;
  }Num_Stack,*NumStack;
  ```

  &emsp;&emsp;初始化的时候malloc一下NumStack的空间就行了，top直接指向NULL，不需要申请空间：

  ```c
  NumStack Create_OPND()
  {
  	NumStack OPND;
  	OPND = (NumStack)malloc(sizeof(Num_Stack));
  	OPND->len = 0;
  	OPND->top = NULL;
  	return OPND;
  }
  ```

- `算符优先算法`我觉得还挺机智的，值得好好学习学习。

&emsp;&emsp;其他也没什么好说的，都是栈的基础操作。
