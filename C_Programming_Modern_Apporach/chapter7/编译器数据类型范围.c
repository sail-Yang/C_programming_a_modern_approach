/*�鿴�������ͷ�Χ*/
#include <stdio.h>
#include <limits.h>

/* �����ǰ�������������ͷ�Χ */
int main(void)
{
 printf("\nchar�ķ�ΧΪ: %d ���� %d\n", CHAR_MIN, CHAR_MAX);
 printf("unsigned char�ķ�ΧΪ: %u ���� %u\n\n", 0, UCHAR_MAX);
 
 printf("short�ķ�ΧΪ: %hd ���� %hd\n", SHRT_MIN, SHRT_MAX);
 printf("unsigned short�ķ�ΧΪ: %hu ���� %hu\n\n", 0, USHRT_MAX);
 
 printf("int�ķ�ΧΪ: %d ���� %d\n", INT_MIN, INT_MAX);
 printf("unsigned int�ķ�ΧΪ: %u ���� %u\n\n", 0, UINT_MAX);
 
 printf("long�ķ�ΧΪ: %ld ���� %ld\n", LONG_MIN, LONG_MAX);
 printf("unsigned long�ķ�ΧΪ: %lu ���� %lu\n\n", 0, ULONG_MAX);
 
 printf("long long�ķ�ΧΪ: %lld ���� %lld\n", LLONG_MIN, LLONG_MAX);
 printf("unsigned long long�ķ�ΧΪ: %llu ���� %llu\n\n", 0, ULLONG_MAX);
 
 return 0;
}

