
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 20

void intro_game(void);
void horizontal_slide(int x, int y, char *c2);
void draw_rectangle(int r, int c);
void display_text(int count, int r_count);
void game_control(int *r_c, int rnd);
void gotoxy(int x, int y);
void clear_position(int x, int y);

int main(void)
{
    int count = 0;
    int rnd;
    int r_count = 0;

    srand((unsigned int)time(NULL));

    intro_game();

    do
    {
        system("cls");

        // 게임판 출력
        draw_rectangle(BOARD_HEIGHT, 20);

        // 표적 위치 설정
        rnd = rand() % 35 + 3;

        gotoxy(rnd, 2);
        printf("□");

        count++;

        display_text(count, r_count);

        game_control(&r_count, rnd);

    } while(count < 10);

    // 최종 결과
    system("cls");

    printf("========== 게임 종료 ==========\n\n");
    printf("총 발사 횟수 : 10\n");
    printf("명중 횟수    : %d\n", r_count);
    printf("명중률       : %.1f%%\n", r_count * 10.0);

    if(r_count >= 7)
        printf("\n훌륭합니다!\n");
    else if(r_count >= 4)
        printf("\n잘했습니다!\n");
    else
        printf("\n다음에는 더 잘할 수 있습니다!\n");

    getch();

    return 0;
}


// 게임 소개
void intro_game(void)
{
    system("cls");

    printf("말타며 화살쏘기\n\n");
    printf("말을 타고 이동하면서\n");
    printf("목표물(□)을 맞추는 게임입니다.\n");
    printf("화살은 스페이스키로 발사합니다.\n\n");
    printf("총 10번의 기회가 주어집니다.\n\n");
    printf("아무키나 누르면 시작합니다.");

    getch();
}


// 커서 위치의 문자 지우기
void clear_position(int x, int y)
{
    gotoxy(x, y);
    printf(" ");
}


// 말 이동 애니메이션
void horizontal_slide(int x, int y, char *c2)
{
    gotoxy(x, y);
    printf("%s", c2);

    Sleep(50);

    gotoxy(x, y);
    printf(" ");
}


// 게임판 출력
void draw_rectangle(int r, int c)
{
    int i, j;

    // 위쪽 테두리
    printf("+");

    for(i = 0; i < c * 2; i++)
        printf("-");

    printf("+\n");

    // 좌우 테두리
    for(i = 0; i < r; i++)
    {
        printf("|");

        for(j = 0; j < c * 2; j++)
            printf(" ");

        printf("|\n");
    }

    // 아래쪽 테두리
    printf("+");

    for(i = 0; i < c * 2; i++)
        printf("-");

    printf("+\n");
}


// 게임 정보 출력
void display_text(int count, int r_count)
{
    gotoxy(46, 2);
    printf("스페이스키를 누르면");

    gotoxy(46, 3);
    printf("화살이 발사됩니다.");

    gotoxy(46, 5);
    printf("횟수 : %d / 10", count);

    gotoxy(46, 6);
    printf("성공 : %d", r_count);
}


// 게임 진행
void game_control(int *r_c, int rnd)
{
    int i = 1;
    int k = 1;
    int y;

    int hit = 0;

    char *horse = "▲";
    char chr;

    // 말 이동
    while(1)
    {
        i += k;

        if(i >= 38)
            k = -1;

        else if(i <= 1)
            k = 1;

        horizontal_slide(i + 1, 21, horse);

        // 키 입력 확인
        if(kbhit())
        {
            chr = getch();

            if(chr == 32)
                break;
        }
    }

    // 화살 발사
    y = 20;

    while(y > 2)
    {
        y--;

        // 화살 출력
        gotoxy(i + 1, y);
        printf("↑");

        Sleep(50);

        // 화살이 표적 높이에 도달했을 때 판정
        if(y == 2)
        {
            // 정확히 같은 X좌표일 때만 명중
            if(i + 1 == rnd)
                hit = 1;
        }

        // 화살 이전 위치 지우기
        gotoxy(i + 1, y);
        printf(" ");

        if(hit)
            break;
    }

    // 명중 결과
    if(hit == 1)
    {
        gotoxy(rnd, 2);
        printf("☆");

        gotoxy(46, 8);
        printf("맞았습니다!");

        (*r_c)++;
    }
    else
    {
        gotoxy(46, 8);
        printf("빗나갔습니다.");
    }

    // 현재 말 위치 정리
    gotoxy(i + 1, 21);
    printf(" ");

    gotoxy(1, 24);
    printf("아무키나 누르면 다음 진행...");

    getch();
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

