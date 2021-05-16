/*查看数据类型范围*/
#include <stdio.h>
#include <limits.h>

/* 输出当前编译器数据类型范围 */
int main(void)
{
 printf("\nchar的范围为: %d —— %d\n", CHAR_MIN, CHAR_MAX);
 printf("unsigned char的范围为: %u —— %u\n\n", 0, UCHAR_MAX);
 
 printf("short的范围为: %hd —— %hd\n", SHRT_MIN, SHRT_MAX);
 printf("unsigned short的范围为: %hu —— %hu\n\n", 0, USHRT_MAX);
 
 printf("int的范围为: %d —— %d\n", INT_MIN, INT_MAX);
 printf("unsigned int的范围为: %u —— %u\n\n", 0, UINT_MAX);
 
 printf("long的范围为: %ld —— %ld\n", LONG_MIN, LONG_MAX);
 printf("unsigned long的范围为: %lu —— %lu\n\n", 0, ULONG_MAX);
 
 printf("long long的范围为: %lld —— %lld\n", LLONG_MIN, LLONG_MAX);
 printf("unsigned long long的范围为: %llu —— %llu\n\n", 0, ULLONG_MAX);
 
 return 0;
}

