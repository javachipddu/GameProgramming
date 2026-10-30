
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void intro_game(void);
void game_control(void);

int computer_number(int i, int com_array[]);
int user_number(int i, int user_array[]);

int check_duplicate(int number, int i, int array[]);

void number_display(int i, int com_array[],
                    int user_array[], int sum);

void conclusion(int win);
void gotoxy(int x, int y);
void press_any_key(void);


int main(void)
{
    srand((unsigned int)time(NULL));

    intro_game();
    game_control();

    return 0;
}


// 게임 소개
void intro_game(void)
{
    system("cls");

    printf("100을 넘어라 게임\n\n");
    printf("컴퓨터와 사용자가 번갈아가며\n");
    printf("1~10 사이의 숫자를 입력합니다.\n");
    printf("각 플레이어는 중복된 숫자를 사용할 수 없습니다.\n\n");
    printf("최초로 100을 넘기면 승리합니다.\n\n");
    printf("컴퓨터가 먼저 시작합니다.\n");
    printf("아무키나 누르면 시작합니다.");

    getch();
}


// 중복 검사 함수
// 중복이면 1, 중복이 아니면 0
int check_duplicate(int number, int i, int array[])
{
    int j;

    for(j = 0; j < i; j++)
    {
        if(array[j] == number)
            return 1;
    }

    return 0;
}


// 컴퓨터 숫자 생성
int computer_number(int i, int com_array[])
{
    int number;

    while(1)
    {
        number = rand() % 10 + 1;

        if(check_duplicate(number, i, com_array) == 0)
        {
            com_array[i] = number;
            return number;
        }
    }
}


// 사용자 숫자 입력
int user_number(int i, int user_array[])
{
    int number;
    int result;
    int ch;

    while(1)
    {
        gotoxy(1, 7);
        printf("사용자 숫자 입력후 Enter> ");

        result = scanf("%d", &number);

        if(result != 1)
        {
            while((ch = getchar()) != '\n' && ch != EOF);

            gotoxy(1, 8);
            printf("숫자를 입력하세요.              ");
            continue;
        }

        if(number < 1 || number > 10)
        {
            gotoxy(1, 8);
            printf("1~10 사이의 숫자를 입력하세요.  ");
            continue;
        }

        if(check_duplicate(number, i, user_array) == 1)
        {
            gotoxy(1, 8);
            printf("이미 사용한 숫자입니다.        ");
            continue;
        }

        user_array[i] = number;

        return number;
    }
}


// 숫자 출력
void number_display(int i, int com_array[],
                    int user_array[], int sum)
{
    int j;

    gotoxy(1, 2);
    printf("컴퓨터 숫자 : ");

    for(j = 0; j <= i; j++)
        printf("%2d ", com_array[j]);

    gotoxy(1, 3);
    printf("사용자 숫자 : ");

    for(j = 0; j <= i; j++)
    {
        if(user_array[j] != 0)
            printf("%2d ", user_array[j]);
    }

    gotoxy(1, 5);
    printf("현재 합계 : %3d", sum);
}


// 게임 결과
void conclusion(int win)
{
    gotoxy(1, 10);

    if(win == 1)
        printf("컴퓨터가 이겼습니다.\n");
    else if(win == 2)
        printf("사용자가 이겼습니다.\n");
    else
        printf("게임이 종료되었습니다.\n");

    printf("\n아무키나 누르면 종료합니다.");
    getch();
}


// 아무 키나 누르기
void press_any_key(void)
{
    gotoxy(1, 10);
    printf("아무키나 누르시오..");
    getch();
}


// 게임 진행
void game_control(void)
{
    int max = 100;

    int com_array[10] = {0};
    int user_array[10] = {0};

    int number;
    int i;
    int sum = 0;
    int win = 0;

    for(i = 0; i < 10; i++)
    {
        system("cls");

        // 컴퓨터 차례
        number = computer_number(i, com_array);

        sum += number;

        number_display(i, com_array, user_array, sum);

        if(sum > max)
        {
            win = 1;
            break;
        }

        // 사용자 차례
        number = user_number(i, user_array);

        sum += number;

        number_display(i, com_array, user_array, sum);

        if(sum > max)
        {
            win = 2;
            break;
        }

        press_any_key();
    }

    conclusion(win);
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

