/* Checks numbers for repeated digits */

#include <stdbool.h>   /* C99 only */
#include <stdio.h>

int main(void)
{
  bool digit_seen[10] = {false};
  int digit,i, a[10];
  long n;

  printf("Enter a number: ");
  scanf("%ld", &n);

  for(i = 0; i < 10; i++)
      a[i] = 10;

  while (n > 0) {                    // 将重复的一位数筛选出来，并将其赋值给元素为二位数的数组。
    digit = n % 10;
    if (digit_seen[digit])
        a[digit] = digit;
    else 
        digit_seen[digit] = true;
    n /= 10;
  }

  printf("Repeated digit(s): ");   // 将一位数筛选出来。
  for (i = 0; i < 10; i++)
      if (a[i] != 10)
          printf("%2d", a[i]);
  printf("\n");

  return 0;
}
