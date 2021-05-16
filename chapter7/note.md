## 本章组织结构

！[大纲](https://github.com/sail-Yang/image/raw/main/%E5%9F%BA%E6%9C%AC%E7%B1%BB%E5%9E%8B.png)

##  读字符的scanf问题

在读入字符前，scanf函数不会跳过空白字符。如果下一个未读字符是空格，那么在前面的例子中，scanf函数返回后变量ch将包含一个空格。为了强制scanf函数在读入字符前跳过空白字符，需要在格式串中的转换说明%c前面加一个空格。

scanf格式串中的空白意味着"跳过零个或多个空白字符。"

```c
scanf(" %c",&ch);/*skips white space, then reads cn */
```

##  getchar、putchar相比于printf,scanf的优越性

- 前者因为内容专一而更简单

  scanf和printf函数是设计用来按不同的格式读/写不同数据的，所以较前者更为复杂。

- 因为getchar返回的是读入的字符，所以getchar可以应用在**多种不同的C语言惯用法**，包括搜索字符或跳过所有出现的字符。

  先来看一个scanf函数循环，用来跳过输入行的剩余部分：

  ```c
  do{
      scanf("%c",&ch); 
  }while (ch !='\n');
  ```

  用 getchar重新写就成这样了：

  ```c
  do{
  	ch = getchar();
  }while (ch!='\n')
  ```

  我们还可以进一步简化为非常著名的**C语言惯用法**：

  ```c
  while (getchar() != '\n') /*skips rest of line*/
      ;
  ```

  下面再放一个例子：用getchar函数跳过不定数量的空格字符的语句：

  ```
  while ((ch = getchar()) == ' ') /*skips blanks*/
  	;
  ```

  当循环终止时，变量ch将包含getchar函数遇到的第一个非空白字符。

  ###  补充

  - getchar会吸收scanf读入的换行符，所以要在循环中使用getchar，先把scanf里的\n吸收掉。具体示例看7.2练习。

##  类型转换

在执行算术运算时，计算机的限制很多：

- 操作数相同的大小，存储的方式也要相同。
- 比如可以把16位整数和16位整数相加，但是不能把16位整数和32位整数相加。

C语言允许混合使用基本类型，因为C语言会自动转换类型，比如在16位short型+32位int型时，就会把16位short型转化成32位值。我们将编译器自动处理的转换称为**隐式转换**。相对的显示转换，先不讲。

当发生下列情况时，会进行隐式转换：

- 操作数类型不同
- =左右边类型不匹配
- 函数调用形参和实参类型不同
- return表达式的类型和函数返回值类型不匹配。

这里稍微提一下强制类型转换的格式：

（类型名）表达式

##  类型定义

之前我们用#define创建了一个宏，可以用来定义布尔型数据：

```c
#define Bool int
```

但是用**类型定义**可以更好地设置布尔类型：

```c
typedef int Bool;
```

用typedef定义Bool会导致编译器在它所识别的类型名列表中加入Bool。现在，Bool类型可以和内置的类型名一样用于变量声明、强制类型转换表达式和其他地方了。例如,可以使用Bool声明变量：

```c
Bool flag; /*same as int flag*/
```

###  优点

使程序更易于理解，**可以把一类事物归在一起**；还方便进行修改。

###  类型定义和可移植性

##  sizeof

sizeof运算符允许程序存储指定类型所需空间的大小。

sizeof (类型名)

##  Q&A

- 为什么使用%lf读取double类型却使用%f进行显示呢？
  - scanf和printf都是不同寻常的function，它们不会限制参数的数量。scanf和printf都有可变长度的参数列表。当调用带有可变参数的函数时，百年一起会安排float参数自动转化成double类型，这也就导致printf分不清float和double.这就解释了为什么printf可以用%f表示float和double。
  - scanf变量是通过指针指向变量的。%f告诉scanf函数在所传地址上存储一个float类型值，而%lf告诉scanf函数在该地址存储一个double类型。这里是需要区分的，因为字节数量不同。

