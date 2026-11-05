
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 함수 선언
long time_to_number(void);
void number_check(int, int);
void digit_print(int*, int);
void gotoxy(int x, int y);
void dot_print(int hour);

// 숫자 0~9의 모양을 5행 4열 배열로 정의
int zero[20] =
{
    1,1,1,1,
    1,0,0,1,
    1,0,0,1,
    1,0,0,1,
    1,1,1,1
};

int one[20] =
{
    0,0,1,0,
    0,0,1,0,
    0,0,1,0,
    0,0,1,0,
    0,0,1,0
};

int two[20] =
{
    1,1,1,1,
    0,0,0,1,
    1,1,1,1,
    1,0,0,0,
    1,1,1,1
};

int three[20] =
{
    1,1,1,1,
    0,0,0,1,
    1,1,1,1,
    0,0,0,1,
    1,1,1,1
};

int four[20] =
{
    1,0,0,1,
    1,0,0,1,
    1,1,1,1,
    0,0,0,1,
    0,0,0,1
};

int five[20] =
{
    1,1,1,1,
    1,0,0,0,
    1,1,1,1,
    0,0,0,1,
    1,1,1,1
};

int six[20] =
{
    1,0,0,0,
    1,0,0,0,
    1,1,1,1,
    1,0,0,1,
    1,1,1,1
};

int seven[20] =
{
    1,1,1,1,
    0,0,0,1,
    0,0,0,1,
    0,0,0,1,
    0,0,0,1
};

int eight[20] =
{
    1,1,1,1,
    1,0,0,1,
    1,1,1,1,
    1,0,0,1,
    1,1,1,1
};

int nine[20] =
{
    1,1,1,1,
    1,0,0,1,
    1,1,1,1,
    0,0,0,1,
    0,0,0,1
};

// 메인 함수
int main(void)
{
    int line;
    long time_number;

    printf("디지털 시계 프로그램\n\n");
    printf("아무 키나 누르면 현재 시간을 출력합니다.\n");

    getch();
    system("cls");

    while (!kbhit())
    {
        gotoxy(1, 3);

        time_number = time_to_number();

        for (line = 0; line <= 4; line++)
        {
            number_check((int)time_number, line);
            printf("\n");
        }

        dot_print((int)time_number);

        printf("\n\n\n\n아무 키나 누르면 종료합니다.\n");
    }

    return 0;
}

// 현재 시간을 HHMMSS 형태로 반환
long time_to_number(void)
{
    time_t current;
    struct tm *d;

    int hour, min, sec;

    current = time(NULL);
    d = localtime(&current);

    hour = d->tm_hour * 10000;
    min = d->tm_min * 100;
    sec = d->tm_sec;

    return hour + min + sec;
}

// 숫자의 각 자릿수를 분리하여 출력
void number_check(int k, int i)
{
    if (k >= 1)
    {
        number_check(k / 10, i);

        switch (k % 10)
        {
            case 0: digit_print(zero, i); break;
            case 1: digit_print(one, i); break;
            case 2: digit_print(two, i); break;
            case 3: digit_print(three, i); break;
            case 4: digit_print(four, i); break;
            case 5: digit_print(five, i); break;
            case 6: digit_print(six, i); break;
            case 7: digit_print(seven, i); break;
            case 8: digit_print(eight, i); break;
            case 9: digit_print(nine, i); break;
        }
    }
}

// 숫자 배열의 한 행을 출력
void digit_print(int *dim, int check)
{
    int i;

    for (i = check * 4; i <= check * 4 + 3; i++)
    {
        if (dim[i] == 1)
            printf("■");
        else
            printf("  ");
    }

    printf("  ");
}

// 시간 구분점 출력
void dot_print(int hour)
{
    int i;

    if (hour < 100000)
    {
        for (i = 0; i < 2; i++)
        {
            gotoxy(10 + (i * 27), 4);
            printf("■");

            gotoxy(10 + (i * 27), 6);
            printf("■");
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            gotoxy(24 + (i * 26), 4);
            printf("■");

            gotoxy(24 + (i * 26), 6);
            printf("■");
        }
    }
}

// 콘솔 커서 위치 이동
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Pos
    );
}
