##  条件表达式

$$
表达式1 ？ 表达式2 ： 表达式3
$$

条件表达式为C运算符中唯一一个要求三个操作数的运算符→三元运算符。

这一运算符的意思为：如果表达式1成立，则执行表达式2；否则执行表达式3。那么这一运算符有什么小应用呢？

- return语句

下面先放修改前的代码再放修改后的代码：

```c
if (i>k)
    return i;
else
    return k;
```

这一代码可以精简为：

```c
return i>k ? i : k;
```

- printf语句的调用

```c
if (i>j)
    printf("%d\n",i);
else
    printf("%d\n",j)
```

这一代码可以精简为：

```c
printf("%d\n",i>j ? i :j)
```

虽然条件运算符使得语句精简许多，但最好还是不要随便用，因为会减少可读性。

##  布尔变量简介

这一章稍微提到了布尔值，在C99中，布尔变量可以声明为：
$$
\_Bool\ \  flag;
$$
_Bool是整数类型，把非0整形操作数赋值为1。除了_Bool类型的定义，C99还提供了一个新的头——<stdbool.h>

该头提供了bool宏，用来代表_Bool。如果程序中包含了<stdbool.h>，可以这样写：
bool flag;

还可以这么写：

flag = false; //代表0

falg = true; //代表1

##  switch为什么比if执行速度快？

switch语句，即把表达式和一系列值比较，从中找出当前匹配的值时用的语句。**它为什么会比if语句更快呢？**

[switch快的秘密](https://blog.csdn.net/weixin_43167418/article/details/106184436?ops_request_misc=&request_id=&biz_id=102&utm_term=switch%E4%B8%BA%E4%BB%80%E4%B9%88%E4%BC%9A%E6%AF%94if%E6%9B%B4%E5%BF%AB%E5%91%A2&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-4-106184436.first_rank_v2_pc_rank_v29)

关键词：**基于计算的跳转**，**以空间换时间**。

###  break的必要性

只要记得使用switch的时候在每个分支末尾都要加上break，除非你要让多个分支共享代码，像下面这样：

```c
switch (grade) {
        case4: case3: case2: 
        	printf("Passing");
        	break;
        case0:	printf("Falling");
        		break;
}
```

