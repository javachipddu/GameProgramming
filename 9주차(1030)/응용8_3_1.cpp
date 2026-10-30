
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void time_pass(time_t start);
void display_time(long nhour, long nmin, long nsecond);
void control_watch(void);
void gotoxy(int x, int y);

int main(void)
{
    display_time(0, 0, 0);

    control_watch();

    return 0;
}


// 커서 이동
void gotoxy(int x, int y)
{
    COORD Pos;

    Pos.X = x - 1;
    Pos.Y = y - 1;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Pos
    );
}


// 스톱워치 진행
void control_watch(void)
{
    time_t start;
    time_t elapsed = 0;

    int running = 0;
    int key;

    while(1)
    {
        if(running)
        {
            time_t now;

            now = time(NULL);

            elapsed += 0; // 경과 시간은 아래에서 계산

            time_pass(start + elapsed);
        }

        key = getch();

        // ESC : 종료
        if(key == 27)
            break;

        // 방향키 등 확장 키 무시
        if(key == 0 || key == 224)
        {
            getch();
            continue;
        }

        // Enter : 시작 / 정지
        if(key == 13)
        {
            if(running == 0)
            {
                start = time(NULL);
                running = 1;
            }
            else
            {
                elapsed += difftime(time(NULL), start);
                running = 0;

                time_pass(time(NULL) - (time_t)elapsed);
            }
        }

        // SPACE : 초기화
        else if(key == 32)
        {
            elapsed = 0;
            start = time(NULL);
            running = 1;
        }
    }
}


// 시간 계산 및 표시
void time_pass(time_t start)
{
    time_t now;
    long second;
    long nhour, nmin, nsecond;

    now = time(NULL);

    second = (long)difftime(now, start);

    nhour = second / 3600;
    nmin = (second % 3600) / 60;
    nsecond = second % 60;

    display_time(nhour, nmin, nsecond);
}


// 시간 출력
void display_time(long nhour, long nmin, long nsecond)
{
    gotoxy(1, 1);

    printf("STOPWATCH\n\n");

    printf("%02ld시 %02ld분 %02ld초          \n\n",
           nhour, nmin, nsecond);

    printf("Enter: 시작/정지\n");
    printf("SPACE: 재시작\n");
    printf("ESC: 종료\n");

    fflush(stdout);
}

