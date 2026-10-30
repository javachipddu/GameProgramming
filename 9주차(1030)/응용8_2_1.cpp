
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

// 함수 선언
void control_scoreboard(int st, int end,
                        int r[], int h[], int e[], int b[]);

void display_scoreboard(int r[], int h[], int e[], int b[]);

void draw_check02(int c, int r);

void gotoxy(int x, int y);

int input_number(const char *message);

int main(void)
{
    int r[2] = {0, 0};
    int h[2] = {0, 0};
    int e[2] = {0, 0};
    int b[2] = {0, 0};

    system("cls");

    // 최초 전광판 출력
    display_scoreboard(r, h, e, b);

    // 1~9회 진행
    control_scoreboard(1, 9, r, h, e, b);

    // 10~12회 연장전
    control_scoreboard(10, 12, r, h, e, b);

    // 12회까지 동점인 경우
    gotoxy(1, 15);
    printf("무승부입니다. 아무키나 누르시오.");

    getch();

    return 0;
}


// 커서 이동
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Pos
    );
}


// 전광판 그리기
void draw_check02(int c, int r)
{
    int i, j;

    unsigned char a = 0xa6;
    unsigned char b[12];

    for(i = 1; i < 12; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);

    for(i = 0; i < c - 1; i++)
    {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[8]);
    }

    printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[4]);

    for(i = 0; i < r - 1; i++)
    {
        printf("%c%c", a, b[2]);

        for(j = 0; j < c; j++)
        {
            printf("  ");
            printf("%c%c", a, b[2]);
        }

        printf("\n");

        printf("%c%c", a, b[7]);

        for(j = 0; j < c - 1; j++)
        {
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[11]);
        }

        printf("%c%c", a, b[1]);
        printf("%c%c\n", a, b[9]);
    }

    printf("%c%c", a, b[2]);

    for(j = 0; j < c; j++)
    {
        printf("  ");
        printf("%c%c", a, b[2]);
    }

    printf("\n");

    printf("%c%c", a, b[6]);

    for(i = 0; i < c - 1; i++)
    {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[10]);
    }

    printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[5]);
}


// 숫자 입력 및 검증
int input_number(const char *message)
{
    int number;
    int result;
    int ch;

    while(1)
    {
        printf("%s", message);

        result = scanf("%d", &number);

        if(result == 1)
        {
            if(number >= 0)
                return number;

            printf("0 이상의 숫자를 입력하세요.\n");
        }
        else
        {
            printf("숫자만 입력하세요.\n");
        }

        // 잘못 입력한 문자 제거
        while((ch = getchar()) != '\n' && ch != EOF);
    }
}


// 전광판 출력
void display_scoreboard(int r[], int h[], int e[], int b[])
{
    int i, j;

    gotoxy(1, 1);
    printf("스코어보드\n");

    gotoxy(1, 2);
    draw_check02(17, 3);

    // 회차 표시
    for(i = 1; i <= 12; i++)
    {
        gotoxy(i * 4 + 3, 3);
        printf("%2d", i);
    }

    gotoxy(13 * 4 + 4, 3);
    printf("R");

    gotoxy(14 * 4 + 4, 3);
    printf("H");

    gotoxy(15 * 4 + 4, 3);
    printf("E");

    gotoxy(16 * 4 + 4, 3);
    printf("B");

    // 팀 이름
    gotoxy(3, 5);
    printf("CL");

    gotoxy(3, 7);
    printf("TG");

    // 누적 기록
    for(j = 0; j <= 1; j++)
    {
        gotoxy(13 * 4 + 3, 5 + 2 * j);
        printf("%2d", r[j]);

        gotoxy(14 * 4 + 3, 5 + 2 * j);
        printf("%2d", h[j]);

        gotoxy(15 * 4 + 3, 5 + 2 * j);
        printf("%2d", e[j]);

        gotoxy(16 * 4 + 3, 5 + 2 * j);
        printf("%2d", b[j]);
    }
}


// 경기 진행
void control_scoreboard(int st, int end,
                        int r[], int h[], int e[], int b[])
{
    int i, j;

    int rr, hh, ee, bb;

    char state[10];

    for(i = st; i <= end; i++)
    {
        for(j = 0; j <= 1; j++)
        {
            if(j == 0)
                strcpy(state, "초");
            else
                strcpy(state, "말");

            // 해당 회차 점수 초기화
            gotoxy(i * 4 + 3, 5 + 2 * j);
            printf("%2d", 0);

            // 경기 상황 표시
            gotoxy(1, 10);
            printf("%d회%s 결과", i, state);

            // 안타 입력
            gotoxy(1, 11);
            hh = input_number("안타수 입력 : ");

            h[j] += hh;

            gotoxy(14 * 4 + 3, 5 + 2 * j);
            printf("%2d", h[j]);

            // 실책 입력
            gotoxy(1, 12);
            ee = input_number("실책수 입력 : ");

            e[j] += ee;

            gotoxy(15 * 4 + 3, 5 + 2 * j);
            printf("%2d", e[j]);

            // 포볼 입력
            gotoxy(1, 13);
            bb = input_number("포볼수 입력 : ");

            b[j] += bb;

            gotoxy(16 * 4 + 3, 5 + 2 * j);
            printf("%2d", b[j]);

            // 점수 입력
            gotoxy(1, 14);
            rr = input_number("점수   입력 : ");

            r[j] += rr;

            gotoxy(13 * 4 + 3, 5 + 2 * j);
            printf("%2d", r[j]);

            // 해당 회차 점수 표시
            gotoxy(i * 4 + 3, 5 + 2 * j);
            printf("%2d", rr);

            // 입력 완료
            gotoxy(1, 15);
            printf("아무키나 누르시오....");

            getch();

            // 입력 화면 정리
            for(int k = 10; k <= 15; k++)
            {
                gotoxy(1, k);
                printf("                       ");
            }

            // 9회 이후 승부 확인
            if(i >= 9)
            {
                // 초 공격 종료 후 원정팀이 앞서면 경기 종료
                if(j == 0 && r[0] < r[1])
                {
                    gotoxy(1, 15);
                    printf("경기가 끝났습니다. 원정팀 승리!");

                    getch();
                    exit(0);
                }

                // 말 공격 종료 후 점수가 다르면 경기 종료
                if(j == 1 && r[0] != r[1])
                {
                    gotoxy(1, 15);34
                    

                    if(r[0] > r[1])
                        printf("경기가 끝났습니다. 홈팀 승리!");
                    else
                        printf("경기가 끝났습니다. 원정팀 승리!");

                    getch();
                    exit(0);
                }
            }
        }
    }
}

