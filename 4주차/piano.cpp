#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

int calc_frequency(int octave, int inx);
void practice_piano(void);

int main(void)
{
    printf("1부터 8까지 숫자 키를 누르면\n");
    printf("각 음의 소리가 출력됩니다.\n");
    printf("1: 도 2: 레 3: 미 4: 파 5: 솔 6: 라 7: 시 8: 도\n");
    printf("프로그램 종료는 Esc키 입니다.\n\n");

    practice_piano();

    return 0;
}

/* 음의 주파수를 계산하는 함수 */
int calc_frequency(int octave, int inx)
{
    /*
        inx
        0 : 도(C)
        1 : 레(D)
        2 : 미(E)
        3 : 파(F)
        4 : 솔(G)
        5 : 라(A)
        6 : 시(B)
        7 : 도(C)
    */

    double frequency;

    /* C4 = 약 261.63Hz를 기준으로 계산 */
    frequency = 261.63 * pow(2.0, (double)inx / 12.0);

    /*
       위의 계산은 실제로는 반음 단위 계산이므로
       아래처럼 각 음의 주파수를 직접 지정하는 것이
       이 과제에서는 더 간단하다.
    */

    switch (inx)
    {
    case 0:
        frequency = 261.63;  // 도 C4
        break;

    case 1:
        frequency = 293.66;  // 레 D4
        break;

    case 2:
        frequency = 329.63;  // 미 E4
        break;

    case 3:
        frequency = 349.23;  // 파 F4
        break;

    case 4:
        frequency = 392.00;  // 솔 G4
        break;

    case 5:
        frequency = 440.00;  // 라 A4
        break;

    case 6:
        frequency = 493.88;  // 시 B4
        break;

    case 7:
        frequency = 523.25;  // 도 C5
        break;

    default:
        frequency = 0;
        break;
    }

    return (int)frequency;
}

/* 피아노 연습 함수 */
void practice_piano(void)
{
    int key;
    int frequency;

    while (1)
    {
        /* 키보드에서 한 글자를 입력받음 */
        key = _getch();

        /* ESC 키를 누르면 종료 */
        if (key == 27)
        {
            break;
        }
        
        /* 1~8 키를 누른 경우 */
        if (key >= '1' && key <= '8')
        {
            int index = key - '1';

            /* 음의 주파수 계산 */
            frequency = calc_frequency(4, index);

            /* 해당 주파수의 소리를 500ms 동안 출력 */
            Beep(frequency, 500);
        }
    }
}

