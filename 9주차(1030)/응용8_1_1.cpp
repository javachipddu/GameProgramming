
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 함수 선언
void move_arrow_key(int key, int *x, int *y);
void gotoxy(int x, int y);
void draw_check01(void);
void game_control(void);
void draw_player(int x, int y);


int main(void)
{
    // 콘솔 화면 커서 숨기기
    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 1;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &cursor
    );

    game_control();

    return 0;
}


// 커서 위치 이동
void gotoxy(int x, int y)
{
    COORD Pos;

    Pos.X = x - 1;
    Pos.Y = y - 1;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Pos
    );
}


// 게임판 그리기
void draw_check01(void)
{
    int i;

    // 윗부분
    gotoxy(1, 1);
    printf("+------------------------------------+");

    // 좌우 테두리
    for(i = 2; i <= 18; i++)
    {
        gotoxy(1, i);
        printf("|");

        gotoxy(38, i);
        printf("|");
    }

    // 아랫부분
    gotoxy(1, 19);
    printf("+------------------------------------+");

    // 안내 문구
    gotoxy(1, 21);
    printf("방향키로 원을 이동하세요. ESC : 종료");
}


// 원 출력
void draw_player(int x, int y)
{
    gotoxy(x, y);
    printf("○");
}


// 게임 진행
void game_control(void)
{
    int x = 2;
    int y = 2;
    int key;

    system("cls");

    // 게임판은 최초 한 번만 그리기
    draw_check01();

    // 최초 원 출력
    draw_player(x, y);

    while(1)
    {
        key = getch();

        // ESC 종료
        if(key == 27)
            break;

        // 방향키 입력
        if(key == 0 || key == 224)
        {
            key = getch();

            // 기존 원 지우기
            gotoxy(x, y);
            printf("  ");

            // 좌표 이동
            move_arrow_key(key, &x, &y);

            // 이동한 위치에 원 출력
            draw_player(x, y);
        }
    }

    system("cls");

    printf("게임을 종료했습니다.\n");
}


// 방향키 이동 및 경계 검사
void move_arrow_key(int key, int *x, int *y)
{
    switch(key)
    {
        case 72:    // 위쪽
            if(*y > 2)
                (*y)--;
            break;

        case 80:    // 아래쪽
            if(*y < 18)
                (*y)++;
            break;

        case 75:    // 왼쪽
            if(*x > 2)
                *x -= 2;
            break;

        case 77:    // 오른쪽
            if(*x < 36)
                *x += 2;
            break;
    }
}

