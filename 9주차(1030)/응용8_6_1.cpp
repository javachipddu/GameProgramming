
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define box_length 15
#define box_height 15

void intro_game(void);
void game_control(void);
void gotoxy(int x, int y);
int left_right_move(void);
void move_down(int x);
void draw_rectangle(int c, int r);
int max_block(void);

int block_stack[box_length * 2 + 1] = {0};

int main(void)
{
    intro_game();
    game_control();

    gotoxy(1, box_height + 3);
    printf("Game이 종료되었습니다.\n");

    getch();

    return 0;
}


// 게임 소개
void intro_game(void)
{
    system("cls");

    printf("블록 쌓기 게임\n\n");

    printf("블록이 좌우로 움직일 때 스페이스키를 누르면\n");
    printf("블록이 떨어져 바닥에 쌓입니다.\n\n");

    printf("아무키나 누르면 게임을 시작합니다.\n");

    getch();
}


// 게임 진행
void game_control(void)
{
    int x;
    int count = 0;
    int total = 0;

    system("cls");

    draw_rectangle(box_length, box_height);

    gotoxy(box_length * 2 + 5, 3);
    printf("블록의 개수: %2d", box_height);

    gotoxy(box_length * 2 + 5, 4);
    printf("시도한 횟수: %2d", count);

    gotoxy(box_length * 2 + 5, 5);
    printf("쌓인 블록수: %2d", total);

    gotoxy(1, box_height + 3);
    printf("스페이스키를 누르면 블록이 떨어집니다.");

    while(count < box_height)
    {
        gotoxy(box_length * 2 + 5, 4);
        printf("시도한 횟수: %2d", count + 1);

        x = left_right_move();

        // 해당 위치의 블록 개수가 최대 높이에 도달했는지 확인
        if(block_stack[x] >= box_height)
        {
            gotoxy(1, box_height + 4);
            printf("더 이상 블록을 쌓을 수 없습니다.");
            break;
        }

        move_down(x);

        count++;

        total++;

        gotoxy(box_length * 2 + 5, 5);
        printf("쌓인 블록수: %2d", total);

        gotoxy(box_length * 2 + 5, 6);
        printf("최대 높이: %2d", max_block());

        getch();
    }
}


// 커서 이동
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Pos
    );
}


// 좌우 이동
int left_right_move(void)
{
    int x = 3;
    int y = 2;
    int temp = 2;
    int key;

    do
    {
        x += temp;

        if(x >= box_length * 2 - 1)
        {
            x = box_length * 2 - 1;
            temp = -2;
        }

        if(x <= 3)
        {
            x = 3;
            temp = 2;
        }

        gotoxy(x, y);
        printf("□");

        Sleep(50);

        gotoxy(x, y);
        printf("  ");

    } while(!kbhit());

    key = getch();

    // 스페이스바가 아니면 다시 이동
    if(key != 32)
        return left_right_move();

    return x;
}


// 블록 떨어뜨리기
void move_down(int x)
{
    int y;
    int bottom;

    block_stack[x]++;

    bottom = box_height + 1 - block_stack[x];

    for(y = 2; y < bottom; y++)
    {
        gotoxy(x, y);
        printf("□");

        Sleep(30);

        gotoxy(x, y);
        printf("  ");
    }

    // 최종 위치에 블록 고정
    gotoxy(x, bottom);
    printf("□");
}


// 게임판 그리기
void draw_rectangle(int c, int r)
{
    int i, j;

    unsigned char a = 0xa6;
    unsigned char b[7];

    for(i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);

    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);

    printf("%c%c\n", a, b[4]);

    for(i = 0; i < r; i++)
    {
        printf("%c%c", a, b[2]);

        for(j = 0; j < c; j++)
            printf("  ");

        printf("%c%c\n", a, b[2]);
    }

    printf("%c%c", a, b[6]);

    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);

    printf("%c%c\n", a, b[5]);
}


// 가장 높이 쌓인 블록 개수
int max_block(void)
{
    int i;
    int max = 0;

    for(i = 1; i < box_length * 2; i++)
    {
        if(max < block_stack[i])
            max = block_stack[i];
    }

    return max;
}

