
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTION 10
#define MAX_LENGTH 11

void gotoxy(int x, int y);
void display_text(int count);
void display_question(void);
void display_result(void);
void intro_game(void);

char sol[MAX_QUESTION][MAX_LENGTH];


// 메인 함수
int main(void)
{
    intro_game();

    display_question();

    system("cls");

    printf("문제풀이가 모두 끝났습니다.\n");
    printf("\n풀이를 보려면 아무키나 누르시오.");

    getch();

    display_result();

    gotoxy(1, 20);
    printf("\n심리테스트가 종료되었습니다.\n");

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


// 문제 안내 출력
void display_text(int count)
{
    gotoxy(1, 2);

    printf("다음 문제를 읽고 답을 입력하시오.\n\n");
    printf("(%d번 문제)\n\n", count + 1);
}


// 인트로 화면
void intro_game(void)
{
    system("cls");

    printf("심리테스트 게임\n\n");

    printf("제시되는 문제에 모두 답을 하고나면\n");
    printf("해설이 출력됩니다.\n\n");

    printf("아무키나 누르면 시작합니다. ");

    getch();
}


// 질문 출력 및 답변 저장
void display_question(void)
{
    FILE *fp1;

    char chr1[82];

    int line = 5;
    int count = 0;

    char *file1 = "심리테스트질문.txt";

    fp1 = fopen(file1, "r");

    // 파일 열기 검사
    if(fp1 == NULL)
    {
        printf("\n질문 파일을 열 수 없습니다.\n");
        printf("파일 위치와 이름을 확인하세요.\n");
        exit(1);
    }

    system("cls");

    // 파일 내용을 한 줄씩 읽기
    while(fgets(chr1, sizeof(chr1), fp1) != NULL)
    {
        // 빈 줄 검사
        if(chr1[0] == '\n' || chr1[0] == '\r')
        {
            if(count >= MAX_QUESTION)
            {
                printf("문제가 너무 많습니다.\n");
                fclose(fp1);
                exit(1);
            }

            display_text(count);

            gotoxy(1, line);

            printf("답변 : ");

            scanf("%10s", sol[count]);

            count++;

            system("cls");

            line = 5;
        }
        else
        {
            gotoxy(1, line++);

            printf("%s", chr1);
        }
    }

    // 마지막 문제 답변 처리
    if(line > 5)
    {
        if(count >= MAX_QUESTION)
        {
            printf("문제가 너무 많습니다.\n");
            fclose(fp1);
            exit(1);
        }

        display_text(count);

        gotoxy(1, line);

        printf("답변 : ");

        scanf("%10s", sol[count]);

        count++;
    }

    fclose(fp1);
}


// 해설 출력
void display_result(void)
{
    FILE *fp2;

    char chr1[82];

    int line = 5;
    int count = 0;

    char *file2 = "심리테스트해설.txt";

    fp2 = fopen(file2, "r");

    // 파일 열기 검사
    if(fp2 == NULL)
    {
        printf("\n해설 파일을 열 수 없습니다.\n");
        exit(1);
    }

    system("cls");

    while(fgets(chr1, sizeof(chr1), fp2) != NULL)
    {
        // 빈 줄 검사
        if(chr1[0] == '\n' || chr1[0] == '\r')
        {
            if(count >= MAX_QUESTION)
                break;

            gotoxy(1, line + 1);

            printf("당신의 답은 : %s\n", sol[count]);

            printf("다음 문제의 해설은 아무키나 누르시오.");

            getch();

            count++;

            system("cls");

            line = 5;
        }
        else
        {
            gotoxy(1, line++);

            printf("%s", chr1);
        }
    }

    // 마지막 해설의 답변 출력
    if(count < MAX_QUESTION)
    {
        gotoxy(1, line + 1);

        printf("당신의 답은 : %s\n", sol[count]);
    }

    fclose(fp2);
}

