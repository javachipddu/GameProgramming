#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

int calc_frequency(int octave, int inx);
void practice_piano(void);

int calc_frequency(int octave, int inx)
{
    double do_scale = 32.7032;
    double ratio = pow(2.0, 1.0 / 12.0);
    double temp;
    int i;

    temp = do_scale * pow(2.0, octave - 1);

    for (i = 0; i < inx; i++)
    {
        temp = (int)(temp + 0.5);
        temp *= ratio;
    }

    return (int)temp;
}

void practice_piano(void)
{
    int key;
    int index;
    int frequency;

    while (1)
    {
        key = _getch();

        if (key == 27)
        {
            break;
        }

        if (key >= '1' && key <= '8')
        {
            index = key - '1';

            /* 도 레 미 파 솔 라 시 도 */
            int notes[8] = {0, 2, 4, 5, 7, 9, 11, 12};

            frequency = calc_frequency(4, notes[index]);

            Beep(frequency, 500);
        }
    }
}

int main(void)
{
    printf("1부터 8까지 숫자 키를 누르면\n");
    printf("각 음의 소리가 출력됩니다.\n");
    printf("1: 도 2: 레 3: 미 4: 파 5: 솔 6: 라 7: 시 8: 도\n");
    printf("프로그램 종료는 Esc키 입니다.\n");

    practice_piano();

    return 0;
}

