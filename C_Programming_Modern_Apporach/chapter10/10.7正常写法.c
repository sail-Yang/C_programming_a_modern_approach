#include <stdio.h>
#include <ctype.h>

#define MAX_DIGITS 10

// ��¼�������ֵ������ʽ��Ϣ
const int segments[10][9] = {{0, 1, 0, 1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 1, 1}, {0, 1, 0, 0, 1, 1, 0, 1, 1}, {0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 0, 0, 1, 1}, {0, 1, 0, 1, 1, 0, 1, 1, 1}, {0, 1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 0, 1, 1}};

char digits[3][MAX_DIGITS*4];
int i,j=0;

void clear_digits_array(void);
void process_digits(int digit[], int position);
void print_digits_array(void);

int main(void)
{
	system("color 0A");
    char num;
    int digit[9];
    int position = 0;

    printf("Enter a number: ");

    clear_digits_array();

    while ((num = getchar()) != '\n')
    {
        if (47 < num && num < 58)
        {
            for (i = 0; i < 9; i++)
                digit[i] = segments[num-48][i]; // ������segments�е������ֵ���Ϣ��������digit��

            process_digits(digit, position);
            position++;
        }
    }

    print_digits_array();
	system("date/t\n");
	system("pause");
    return 0;
}


void clear_digits_array(void)
{
    for (i = 0; i < 3; i++)
        for (j = 0; j < MAX_DIGITS * 4; j++)
            digits[i][j] = ' ';
}

void process_digits(int digit[], int position)
{
    char _digit[3][3] = {{' ', '_', ' '}, {'|', '_', '|'}, {'|', '_', '|'}}; // ���ַ�8�������ʽ����������_digit�С�

    for (i = 0; i < 3; i++)             // ��digit�м�¼����ֵ��Ϣ��������_digit��
        for (j = 0; j < 3; j++)
        {
            if (digit[j+i*3] == 0)
                _digit[i][j] = ' ';
            digits[i][j+position*4] = _digit[i][j]; 
        }
}

void print_digits_array(void)
{
    for (i = 0; i < 3; i++)
    {
        printf("\n");
        for (j = 0; j < MAX_DIGITS * 4; j++)
            printf("%c", digits[i][j]);
    }
}

