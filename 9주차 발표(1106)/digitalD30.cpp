#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

long time_to_number(void);
long world_time_to_number(const wchar_t *time_zone_name);
void print_digit_row(int digit, int row);
void print_digital_time(long time_number);
void set_text_color(WORD color);
void play_minute_sound(void);

int zero[20] =
    {1,1,1,1, 1,0,0,1, 1,0,0,1, 1,0,0,1, 1,1,1,1};
int one[20] =
    {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0};
int two[20] =
    {1,1,1,1, 0,0,0,1, 1,1,1,1, 1,0,0,0, 1,1,1,1};
int three[20] =
    {1,1,1,1, 0,0,0,1, 1,1,1,1, 0,0,0,1, 1,1,1,1};
int four[20] =
    {1,0,0,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1};
int five[20] =
    {1,1,1,1, 1,0,0,0, 1,1,1,1, 0,0,0,1, 1,1,1,1};
int six[20] =
    {1,0,0,0, 1,0,0,0, 1,1,1,1, 1,0,0,1, 1,1,1,1};
int seven[20] =
    {1,1,1,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1};
int eight[20] =
    {1,1,1,1, 1,0,0,1, 1,1,1,1, 1,0,0,1, 1,1,1,1};
int nine[20] =
    {1,1,1,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1};

int main(void)
{
    int mode;
    int ch;
    int current_minute;
    int previous_minute;
    long time_number;
    const wchar_t *zone_name;

    while (1)
    {
        system("cls");

        printf("===== 디지털 시계 프로그램 =====\n\n");
        printf("1. 현재 컴퓨터 시간\n");
        printf("2. 뉴욕 시간\n");
        printf("3. 런던 시간\n");
        printf("4. 시드니 시간\n");
        printf("5. 파리 시간\n");
        printf("6. 인도 시간\n");
        printf("7. 베이징 시간\n");
        printf("8. 두바이 시간\n");
        printf("9. 모스크바 시간\n");
        printf("10. 로스앤젤레스 시간\n");
        printf("11. 시카고 시간\n");
        printf("12. 방콕 시간\n");
        printf("13. 카이로 시간\n");
        printf("14. 오클랜드 시간\n");
        printf("15. 덴버 시간\n");
        printf("16. 카트만두 시간\n");
        printf("17. 나이로비 시간\n");
        printf("18. 테헤란 시간\n");
        printf("19. 다카 시간\n");
        printf("20. 레이캬비크 시간\n");
        printf("21. 호놀룰루 시간\n");
        printf("22. 세인트존스 시간\n");
        printf("23. 양곤 시간\n");
        printf("24. 앵커리지 시간\n");
        printf("0. 프로그램 종료\n\n");
        printf("원하는 모드를 입력하세요: ");

        if (scanf("%d", &mode) != 1)
        {
            printf("잘못된 입력입니다.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        if (mode == 0)
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        if (mode < 1 || mode > 24)
        {
            printf("잘못된 모드입니다.\n");
            Sleep(1000);
            continue;
        }

        zone_name = NULL;

        if (mode == 2)
            zone_name = L"Eastern Standard Time";
        else if (mode == 3)
            zone_name = L"GMT Standard Time";
        else if (mode == 4)
            zone_name = L"AUS Eastern Standard Time";
        else if (mode == 5)
            zone_name = L"Romance Standard Time";
        else if (mode == 6)
            zone_name = L"India Standard Time";
        else if (mode == 7)
            zone_name = L"China Standard Time";
        else if (mode == 8)
            zone_name = L"Arabian Standard Time";
        else if (mode == 9)
            zone_name = L"Russian Standard Time";
        else if (mode == 10)
            zone_name = L"Pacific Standard Time";
        else if (mode == 11)
            zone_name = L"Central Standard Time";
        else if (mode == 12)
            zone_name = L"SE Asia Standard Time";
        else if (mode == 13)
            zone_name = L"Egypt Standard Time";
        else if (mode == 14)
            zone_name = L"New Zealand Standard Time";
        else if (mode == 15)
            zone_name = L"Mountain Standard Time";
        else if (mode == 16)
            zone_name = L"Nepal Standard Time";
        else if (mode == 17)
            zone_name = L"E. Africa Standard Time";
        else if (mode == 18)
            zone_name = L"Iran Standard Time";
        else if (mode == 19)
            zone_name = L"Bangladesh Standard Time";
        else if (mode == 20)
            zone_name = L"Greenwich Standard Time";
        else if (mode == 21)
            zone_name = L"Hawaiian Standard Time";
        else if (mode == 22)
            zone_name = L"Newfoundland Standard Time";
        else if (mode == 23)
            zone_name = L"Myanmar Standard Time";
        else if (mode == 24)
            zone_name = L"Alaskan Standard Time";

        previous_minute = -1;

        /* 선택한 시계 모드를 실행합니다. */
        while (!_kbhit())
        {
            if (mode == 1)
                time_number = time_to_number();
            else
                time_number = world_time_to_number(zone_name);

            current_minute =
                (int)(time_number / 10000) * 60
                + (int)((time_number / 100) % 100);

            /* 분이 바뀌었을 때만 효과음을 재생합니다. */
            if (previous_minute != -1 &&
                current_minute != previous_minute)
            {
                play_minute_sound();
            }

            previous_minute = current_minute;

            system("cls");

            if (mode == 1)
                printf("현재 컴퓨터 시간\n\n");
            else if (mode == 2)
                printf("뉴욕 시간\n\n");
            else if (mode == 3)
                printf("런던 시간\n\n");
            else if (mode == 4)
                printf("시드니 시간\n\n");
            else if (mode == 5)
                printf("파리 시간\n\n");
            else if (mode == 6)
                printf("인도 시간\n\n");
            else if (mode == 7)
                printf("베이징 시간\n\n");
            else if (mode == 8)
                printf("두바이 시간\n\n");
            else if (mode == 9)
                printf("모스크바 시간\n\n");
            else if (mode == 10)
                printf("로스앤젤레스 시간\n\n");
            else if (mode == 11)
                printf("시카고 시간\n\n");
            else if (mode == 12)
                printf("방콕 시간\n\n");
            else if (mode == 13)
                printf("카이로 시간\n\n");
            else if (mode == 14)
                printf("오클랜드 시간\n\n");
            else if (mode == 15)
                printf("덴버 시간\n\n");
            else if (mode == 16)
                printf("카트만두 시간\n\n");
            else if (mode == 17)
                printf("나이로비 시간\n\n");
            else if (mode == 18)
                printf("테헤란 시간\n\n");
            else if (mode == 19)
                printf("다카 시간\n\n");
            else if (mode == 20)
                printf("레이캬비크 시간\n\n");
            else if (mode == 21)
                printf("호놀룰루 시간\n\n");
            else if (mode == 22)
                printf("세인트존스 시간\n\n");
            else if (mode == 23)
                printf("양곤 시간\n\n");
            else
                printf("앵커리지 시간\n\n");

            /* 선택한 시간의 국가를 출력합니다. */
            if (mode == 1)
                printf("국가: 컴퓨터에 설정된 지역\n\n");
            else if (mode == 2)
                printf("국가: 미국\n\n");
            else if (mode == 3)
                printf("국가: 영국\n\n");
            else if (mode == 4)
                printf("국가: 호주\n\n");
            else if (mode == 5)
                printf("국가: 프랑스\n\n");
            else if (mode == 6)
                printf("국가: 인도\n\n");
            else if (mode == 7)
                printf("국가: 중국\n\n");
            else if (mode == 8)
                printf("국가: 아랍에미리트\n\n");
            else if (mode == 9)
                printf("국가: 러시아\n\n");
            else if (mode == 10)
                printf("국가: 미국\n\n");
            else if (mode == 11)
                printf("국가: 미국\n\n");
            else if (mode == 12)
                printf("국가: 태국\n\n");
            else if (mode == 13)
                printf("국가: 이집트\n\n");
            else if (mode == 14)
                printf("국가: 뉴질랜드\n\n");
            else if (mode == 15)
                printf("국가: 미국\n\n");
            else if (mode == 16)
                printf("국가: 네팔\n\n");
            else if (mode == 17)
                printf("국가: 케냐\n\n");
            else if (mode == 18)
                printf("국가: 이란\n\n");
            else if (mode == 19)
                printf("국가: 방글라데시\n\n");
            else if (mode == 20)
                printf("국가: 아이슬란드\n\n");
            else if (mode == 21)
                printf("국가: 미국\n\n");
            else if (mode == 22)
                printf("국가: 캐나다\n\n");
            else if (mode == 23)
                printf("국가: 미얀마\n\n");
            else
                printf("국가: 미국\n\n");

            print_digital_time(time_number);

            printf("\n아무 키나 누르면 메뉴로 돌아갑니다.\n");
            Sleep(200);
        }

        /* 입력된 키를 읽고 메뉴로 돌아갑니다. */
        _getch();
    }

    return 0;
}

/* 컴퓨터에 설정된 현지 시간을 HHMMSS 형태로 반환합니다. */
long time_to_number(void)
{
    time_t current = time(NULL);
    struct tm *local_time = localtime(&current);

    return local_time->tm_hour * 10000L
         + local_time->tm_min * 100L
         + local_time->tm_sec;
}

/* Windows 시간대 정보를 이용해 지정한 지역의 시간을 구합니다. */
long world_time_to_number(const wchar_t *time_zone_name)
{
    SYSTEMTIME utc_time;
    SYSTEMTIME local_time;
    TIME_ZONE_INFORMATION time_zone;
    DYNAMIC_TIME_ZONE_INFORMATION dynamic_time_zone;

    GetSystemTime(&utc_time);

    if (GetDynamicTimeZoneInformation(&dynamic_time_zone)
        == TIME_ZONE_ID_INVALID)
    {
        return 0;
    }

    if (wcscpy_s(
            dynamic_time_zone.TimeZoneKeyName,
            sizeof(dynamic_time_zone.TimeZoneKeyName) /
                sizeof(dynamic_time_zone.TimeZoneKeyName[0]),
            time_zone_name) != 0)
    {
        return 0;
    }

    dynamic_time_zone.DynamicDaylightTimeDisabled = FALSE;

    if (!GetTimeZoneInformationForYear(
            utc_time.wYear,
            &dynamic_time_zone,
            &time_zone))
    {
        return 0;
    }

    if (!SystemTimeToTzSpecificLocalTime(
            &time_zone,
            &utc_time,
            &local_time))
    {
        return 0;
    }

    return local_time.wHour * 10000L
         + local_time.wMinute * 100L
         + local_time.wSecond;
}

/* 콘솔 글자 색상을 설정합니다. */
void set_text_color(WORD color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

/* 숫자의 한 행을 출력합니다. */
void print_digit_row(int digit, int row)
{
    int *number;
    int col;

    switch (digit)
    {
        case 0: number = zero;  break;
        case 1: number = one;   break;
        case 2: number = two;   break;
        case 3: number = three; break;
        case 4: number = four;  break;
        case 5: number = five;  break;
        case 6: number = six;   break;
        case 7: number = seven; break;
        case 8: number = eight; break;
        default: number = nine; break;
    }

    for (col = 0; col < 4; col++)
    {
        if (number[row * 4 + col] == 1)
            printf("##");
        else
            printf("  ");
    }
}

/* HH:MM:SS를 디지털 숫자와 디지털 콜론으로 출력합니다. */
void print_digital_time(long time_number)
{
    int hour   = (int)(time_number / 10000);
    int minute = (int)((time_number / 100) % 100);
    int second = (int)(time_number % 100);

    int digits[6];
    int row;
    int i;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    WORD original_color =
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    if (GetConsoleScreenBufferInfo(console, &info))
        original_color = info.wAttributes;

    digits[0] = hour / 10;
    digits[1] = hour % 10;
    digits[2] = minute / 10;
    digits[3] = minute % 10;
    digits[4] = second / 10;
    digits[5] = second % 10;

    /* 하늘색 계열 */
    set_text_color(
        FOREGROUND_GREEN |
        FOREGROUND_BLUE |
        FOREGROUND_INTENSITY
    );

    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < 6; i++)
        {
            print_digit_row(digits[i], row);

            if (i == 1 || i == 3)
            {
                printf("  ");

                /* 콜론을 디지털 점 두 개로 표시합니다. */
                if (row == 1 || row == 3)
                    printf("##");
                else
                    printf("  ");

                printf("  ");
            }
            else if (i == 0 || i == 2 || i == 4)
            {
                printf("  ");
            }
        }

        printf("\n");
    }

    set_text_color(original_color);
}

/* 분이 바뀔 때 짧은 효과음을 냅니다. */
void play_minute_sound(void)
{
    Beep(880, 150);
}