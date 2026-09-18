#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int r[], int n);

int main(void)
{
    int i, j;
    int lotto[6];
    int bonus;

    srand(time(NULL));

    // 로또 번호 6개 생성
    for (i = 0; i < 6; i++)
    {
        lotto[i] = rand() % 45 + 1;

        // 중복 검사
        for (j = 0; j < i; j++)
        {
            if (lotto[i] == lotto[j])
            {
                i--;
                break;
            }
        }
    }

    // 보너스 번호 생성
    while (1)
    {
        bonus = rand() % 45 + 1;

        // 기존 6개 번호와 중복 검사
        for (i = 0; i < 6; i++)
        {
            if (bonus == lotto[i])
                break;
        }

        // 6개 번호와 겹치지 않으면 종료
        if (i == 6)
            break;
    }

    // 로또 번호 6개만 정렬
    selection_sort(lotto, 6);

    // 결과 출력
    printf("로또 번호: ");
    for (i = 0; i < 6; i++)
        printf("%2d ", lotto[i]);

    printf("\n보너스 번호: %2d\n", bonus);

    return 0;
}

void selection_sort(int r[], int n)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (r[j] < r[min])
                min = j;
        }

        temp = r[min];
        r[min] = r[i];
        r[i] = temp;
    }
}

