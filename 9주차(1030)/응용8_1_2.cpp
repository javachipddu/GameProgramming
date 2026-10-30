
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SIZE 18

void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);
void move_arrow_key(int key, int *x, int *y);
void draw_player(int x, int y);
void restore_cell(int x, int y, int matrix[][20]);
void display_stone(int matrix[][20]);

int main(void)
{
    game_control();
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


// 게임판 출력
void draw_check01(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[12];

    for(i = 1; i < 12; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);

    for(i = 0; i < c - 1; i++)
        printf("%c%c", a, b[8]);

    printf("%c%c\n", a, b[4]);

    for(i = 0; i < r - 1; i++)
    {
        printf("%c%c", a, b[7]);

        for(j = 0; j < c - 1; j++)
            printf("%c%c", a, b[11]);

        printf("%c%c\n", a, b[9]);
    }

    printf("%c%c", a, b[6]);

    for(i = 0; i < c - 1; i++)
        printf("%c%c", a, b[10]);

    printf("%c%c\n", a, b[5]);
}


// 원 출력
void draw_player(int x, int y)
{
    gotoxy(x, y);
    printf("○");
}


// 이전 위치의 원래 화면 복원
void restore_cell(int x, int y, int matrix[][20])
{
    int col = (x + 1) / 2;

    gotoxy(x, y);

    if(matrix[col][y] == 1)
        printf("●");
    else if(y == 1)
        printf("%c%c", 0xa6, 0xa0 + 8);
    else if(y == SIZE)
        printf("%c%c", 0xa6, 0xa0 + 10);
    else
        printf("%c%c", 0xa6, 0xa0 + 11);
}


// 돌 출력
void display_stone(int matrix[][20])
{
    int x, y;

    for(x = 1; x <= SIZE; x++)
    {
        for(y = 1; y <= SIZE; y++)
        {
            if(matrix[x][y] == 1)
            {
                gotoxy(x * 2 - 1, y);
                printf("●");
            }
        }
    }
}


// 방향키 이동
void move_arrow_key(int key, int *x, int *y)
{
    switch(key)
    {
        case 72:
            if(*y > 2)
                (*y)--;
            break;

        case 80:
            if(*y < SIZE - 1)
                (*y)++;
            break;

        case 75:
            if(*x > 3)
                *x -= 2;
            break;

        case 77:
            if(*x < 33)
                *x += 2;
            break;
    }
}


// 게임 진행
void game_control(void)
{
    int x = 3;
    int y = 2;

    int old_x, old_y;
    int new_x, new_y;

    int key;

    int matrix[20][20] = {0};

    system("cls");

    // 게임판은 한 번만 그린다.
    draw_check01(18, 18);

    gotoxy(1, 21);
    printf("방향키: 이동 / SPACE: 돌 놓기 / ESC: 종료");

    // 최초 원 출력
    draw_player(x, y);

    while(1)
    {
        key = getch();

        // ESC 종료
        if(key == 27)
            break;

        // 스페이스바
        if(key == 32)
        {
            int col = (x + 1) / 2;

            if(matrix[col][y] == 0)
            {
                matrix[col][y] = 1;

                gotoxy(x, y);
                printf("●");
            }

            continue;
        }

        // 방향키
        if(key == 0 || key == 224)
        {
            key = getch();

            old_x = x;
            old_y = y;

            new_x = x;
            new_y = y;

            move_arrow_key(key, &new_x, &new_y);

            // 돌이 있는 위치로 이동 금지
            if(matrix[(new_x + 1) / 2][new_y] == 1)
                continue;

            // 기존 위치 복원
            restore_cell(old_x, old_y, matrix);

            // 좌표 갱신
            x = new_x;
            y = new_y;

            // 새 위치에 원 출력
            draw_player(x, y);
        }
    }

    gotoxy(1, 23);
    printf("게임을 종료했습니다.\n");
}

