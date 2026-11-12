#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <vector>
#include <windows.h>

long time_to_number(void);
long new_york_time_to_number(void);
void print_digit_row(int digit, int row);
void print_digital_time(long time_number);
void set_text_color(WORD color);
void play_text_color_mode(void);
void play_minute_sound(void);
void wait_seconds(double seconds);
void play_key_count_game(void);
void play_binary_mode_menu(void);
void play_binary_display_mode(void);
void play_binary_guess_game(void);
void play_binary_twos_complement_mode(void);
void play_binary_shift_mode(void);
void play_stopwatch_mode(void);
void print_digital_stopwatch(long long elapsed_ms);
void print_binary_number(int value);
int read_signed_binary_value(const char *title, int *value, int *is_signed);
int read_key_press(void);
int load_best_score(void);
int save_best_score(int score);
void print_lap_records(long long lap_times[],
                       long long total_times[],
                       int lap_count);

/* 디지털 블랙잭 함수 */
void play_blackjack_mode(void);
void print_blackjack_card(int rank, int suit);
void print_blackjack_hand(int cards[], int suits[], int count);
void print_blackjack_score(int score);
int calculate_blackjack_score(int cards[], int count);

/* 20초 맞히기 게임 함수 */
void play_20_second_game(void);
void print_digital_accuracy_time(long long elapsed_ms,
                                 int hide_seconds);

/* 디지털 비밀금고 시도 기록 구조체 */
struct VaultAttempt
{
    char guess[7];
    int correct_position;
    int correct_number;
};

/* 디지털 비밀금고 함수 */
void play_digital_vault_game(void);
void play_digital_vault_mode(int code_length, int allow_duplicates);
void play_timer_mode(void);
void print_digital_vault_code(const char code[], const int colors[], int length);

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

/* 일반 글자색과 프로그램 시작 당시의 디지털 숫자 기본색을 저장합니다. */
WORD base_text_color =
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD original_console_color =
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

/* 3~8번 모드의 디지털 숫자는 일반 글자색 설정과 무관하게 흰색으로 표시합니다. */
WORD digital_white_color =
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

int main(void)
{
    int mode;
    int ch;
    int current_minute;
    int previous_minute;
    long time_number;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO console_info;

    /* 현재 콘솔의 기본 글자색을 저장합니다. */
    if (GetConsoleScreenBufferInfo(console, &console_info))
    {
        original_console_color = console_info.wAttributes;
        base_text_color = console_info.wAttributes;
    }

    /* 난수 생성기를 현재 시간으로 초기화합니다. */
    srand((unsigned int)time(NULL));

    while (1)
    {
        system("cls");

        printf("===== 디지털 시계 프로그램 =====\n\n");
        printf("1. 현재 컴퓨터 시간\n");
        printf("2. 뉴욕 시간\n");
        printf("3. 키 입력 횟수 게임\n");
        printf("4. 8자리 이진수 표기\n");
        printf("5. 스톱워치\n");
        printf("6. 디지털 블랙잭\n");
        printf("7. 20초 맞히기 게임\n");
        printf("8. 디지털 비밀금고\n");
        printf("9. 디지털 타이머\n");
        printf("10. 기본 글자색 설정\n");
        printf("0. 프로그램 종료\n\n");
        printf("원하는 모드를 입력하세요: ");

        if (scanf("%d", &mode) != 1)
        {
            printf("잘못된 입력입니다.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            wait_seconds(1.0);
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

        if (mode < 1 || mode > 10)
        {
            printf("잘못된 모드입니다.\n");
            wait_seconds(1.0);
            continue;
        }

        /* 3번 모드는 키 입력 횟수 게임을 실행합니다. */
        if (mode == 3)
        {
            play_key_count_game();
            continue;
        }

        /* 4번 모드는 이진수 관련 하위 메뉴를 실행합니다. */
        if (mode == 4)
        {
            play_binary_mode_menu();
            continue;
        }

        /* 5번 모드는 스톱워치를 실행합니다. */
        if (mode == 5)
        {
            play_stopwatch_mode();
            continue;
        }

        /* 6번 모드는 디지털 블랙잭을 실행합니다. */
        if (mode == 6)
        {
            play_blackjack_mode();
            continue;
        }

        /* 7번 모드는 20초 맞히기 게임을 실행합니다. */
        if (mode == 7)
        {
            play_20_second_game();
            continue;
        }

        /* 8번 모드는 디지털 비밀금고를 실행합니다. */
        if (mode == 8)
        {
            play_digital_vault_game();
            continue;
        }

        /* 9번 모드는 디지털 타이머를 실행합니다. */
        if (mode == 9)
        {
            play_timer_mode();
            continue;
        }

        /* 10번 모드는 디지털 숫자를 제외한 일반 글자색을 설정합니다. */
        if (mode == 10)
        {
            play_text_color_mode();
            continue;
        }

        previous_minute = -1;

        /* 선택한 시계 모드를 실행합니다. */
        while (!_kbhit())
        {
            if (mode == 1)
                time_number = time_to_number();
            else
                time_number = new_york_time_to_number();

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
            else
                printf("뉴욕 시간\n\n");

            /* 1번과 2번 모드의 디지털 시계를 파란색 계열로 출력합니다. */
            set_text_color(
                FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            print_digital_time(time_number);

            /* 디지털 시계 출력이 끝나면 원래 글자색으로 복원합니다. */
            set_text_color(base_text_color);

            printf("\n아무 키나 누르면 메뉴로 돌아갑니다.\n");
            wait_seconds(0.2);
        }

        /* 입력된 키를 읽고 메뉴로 돌아갑니다. */
        _getch();
    }

    return 0;
}

/* 콘솔의 글자색을 지정합니다. */
void set_text_color(WORD color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

/* 10번 모드: 디지털 숫자를 제외한 일반 글자색을 설정합니다. */
void play_text_color_mode(void)
{
    WORD colors[15];
    WORD background_color = original_console_color & 0xF0;
    const char *color_names[15] =
    {
        "파란색", "초록색", "청록색", "빨간색", "자주색",
        "노란색", "밝은 회색", "검은색", "밝은 파란색", "밝은 초록색",
        "밝은 청록색", "밝은 빨간색", "밝은 자주색", "밝은 노란색",
        "흰색"
    };
    int i;
    int choice;
    int ch;
    const char *current_color_name = "사용자 지정 색상";

    /* 기존 콘솔 배경색은 유지하고 글자색만 바꿉니다. */
    colors[0] = background_color | FOREGROUND_BLUE;
    colors[1] = background_color | FOREGROUND_GREEN;
    colors[2] = background_color | FOREGROUND_GREEN | FOREGROUND_BLUE;
    colors[3] = background_color | FOREGROUND_RED;
    colors[4] = background_color | FOREGROUND_RED | FOREGROUND_BLUE;
    colors[5] = background_color | FOREGROUND_RED | FOREGROUND_GREEN;
    colors[6] = background_color | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    colors[7] = background_color;
    colors[8] = background_color | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    colors[9] = background_color | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    colors[10] = background_color | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    colors[11] = background_color | FOREGROUND_RED | FOREGROUND_INTENSITY;
    colors[12] = background_color | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    colors[13] = background_color | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    colors[14] = background_color | FOREGROUND_RED | FOREGROUND_GREEN |
                 FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    for (i = 0; i < 15; i++)
    {
        if (colors[i] == base_text_color)
        {
            current_color_name = color_names[i];
            break;
        }
    }

    while (1)
    {
        system("cls");
        set_text_color(base_text_color);

        printf("===== 기본 글자색 설정 =====\n\n");
        printf("디지털 숫자의 색상은 변경하지 않고, 일반 글자색만 변경합니다.\n\n");
        printf("현재 기본 글자색: %s\n\n", current_color_name);

        for (i = 0; i < 15; i++)
        {
            set_text_color(colors[i]);
            printf("%2d. %s\n", i + 1, color_names[i]);
        }

        set_text_color(base_text_color);
        printf("\n 0. 이전 메뉴로 돌아가기\n\n");
        printf("변경할 글자색을 선택하세요: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("잘못된 입력입니다. 숫자를 입력해 주세요.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            wait_seconds(1.0);
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        if (choice == 0)
            return;

        if (choice < 1 || choice > 15)
        {
            printf("잘못된 선택입니다. 0~15 사이의 번호를 입력해 주세요.\n");
            wait_seconds(1.0);
            continue;
        }

        base_text_color = colors[choice - 1];
        set_text_color(base_text_color);
        printf("\n기본 글자색이 %s(으)로 변경되었습니다.\n", color_names[choice - 1]);
        printf("디지털 숫자는 기존 색상을 유지합니다.\n");
        printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
        read_key_press();
        return;
    }
}

/* 컴퓨터에 설정된 현지 시간을 HHMMSS 형태로 반환합니다. */
long time_to_number(void)
{
    time_t current = time(NULL);
    struct tm *local_time = localtime(&current);

    if (local_time == NULL)
        return 0;

    return local_time->tm_hour * 10000L
         + local_time->tm_min * 100L
         + local_time->tm_sec;
}

/* 뉴욕 시간을 표준 C 함수만 사용해 HHMMSS 형태로 반환합니다. */
long new_york_time_to_number(void)
{
    time_t current_utc = time(NULL);
    struct tm *utc_time;
    struct tm utc_copy;
    int leap_year;
    int march_first_weekday;
    int november_first_weekday;
    int second_sunday_march;
    int first_sunday_november;
    int is_daylight_saving;
    int utc_day;
    int utc_hour;
    int offset;

    if (current_utc == (time_t)-1)
        return 0;

    utc_time = gmtime(&current_utc);

    if (utc_time == NULL)
        return 0;

    utc_copy = *utc_time;

    /* 윤년 여부를 확인합니다. */
    leap_year =
        (utc_copy.tm_year % 4 == 0 &&
        (utc_copy.tm_year % 100 != 0 ||
         (utc_copy.tm_year + 1900) % 400 == 0));

    /*
       미국 서머타임 시작:
       3월 둘째 일요일 오전 2시(뉴욕 현지 시간)
       이는 UTC 기준 오전 7시입니다.

       미국 서머타임 종료:
       11월 첫째 일요일 오전 2시(뉴욕 현지 시간)
       이는 UTC 기준 오전 6시입니다.
    */
    march_first_weekday =
        (utc_copy.tm_wday - (utc_copy.tm_yday -
        (31 + 28 + leap_year)) % 7 + 7) % 7;

    november_first_weekday =
        (utc_copy.tm_wday - (utc_copy.tm_yday -
        (304 + leap_year)) % 7 + 7) % 7;

    second_sunday_march =
        31 + 28 + leap_year +
        (7 - march_first_weekday) % 7 + 7;

    first_sunday_november =
        304 + leap_year +
        (7 - november_first_weekday) % 7;

    utc_day = utc_copy.tm_yday;
    utc_hour = utc_copy.tm_hour;

    is_daylight_saving = 0;

    if ((utc_day > second_sunday_march ||
         (utc_day == second_sunday_march && utc_hour >= 7)) &&
        (utc_day < first_sunday_november ||
         (utc_day == first_sunday_november && utc_hour < 6)))
    {
        is_daylight_saving = 1;
    }

    /* 뉴욕은 서머타임 UTC-4, 표준시 UTC-5입니다. */
    if (is_daylight_saving)
        offset = -4;
    else
        offset = -5;

    /* UTC 시각에 시차를 적용한 뒤 gmtime()으로 시각을 구합니다. */
    current_utc += offset * 60 * 60;
    utc_time = gmtime(&current_utc);

    if (utc_time == NULL)
        return 0;

    return utc_time->tm_hour * 10000L
         + utc_time->tm_min * 100L
         + utc_time->tm_sec;
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

    digits[0] = hour / 10;
    digits[1] = hour % 10;
    digits[2] = minute / 10;
    digits[3] = minute % 10;
    digits[4] = second / 10;
    digits[5] = second % 10;

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
}

/* 분이 바뀔 때 짧은 효과음을 냅니다. */
void play_minute_sound(void)
{
    Beep(880, 150);
}

/* 표준 C의 clock()을 이용해 지정한 시간만큼 대기합니다. */
void wait_seconds(double seconds)
{
    clock_t start = clock();

    while ((double)(clock() - start) / CLOCKS_PER_SEC < seconds)
    {
    }
}

/* 분:초:밀리초 형식으로 스톱워치 시간을 디지털 숫자로 출력합니다. */
void print_digital_stopwatch(long long elapsed_ms)
{
    int minutes;
    int seconds;
    int milliseconds;
    int digits[7];
    int row;
    int i;

    /* 경과 시간을 분, 초, 밀리초로 분리합니다. */
    minutes = (int)((elapsed_ms / 60000) % 100);
    seconds = (int)((elapsed_ms / 1000) % 60);
    milliseconds = (int)(elapsed_ms % 1000);

    digits[0] = minutes / 10;
    digits[1] = minutes % 10;
    digits[2] = seconds / 10;
    digits[3] = seconds % 10;
    digits[4] = milliseconds / 100;
    digits[5] = (milliseconds / 10) % 10;
    digits[6] = milliseconds % 10;

    /* 5번 모드의 디지털 숫자는 항상 흰색으로 출력합니다. */
    set_text_color(digital_white_color);

    /* 기존 디지털 숫자 모양을 재사용하여 MM:SS:MMM을 출력합니다. */
    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < 7; i++)
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
            else if (i != 6)
            {
                printf("  ");
            }
        }

        printf("\n");
    }

    set_text_color(base_text_color);
}

/* 저장된 구간 기록을 출력합니다. */
void print_lap_records(long long lap_times[],
                       long long total_times[],
                       int lap_count)
{
    int i;
    long long lap_minutes;
    long long lap_seconds;
    long long lap_milliseconds;
    long long total_minutes;
    long long total_seconds;
    long long total_milliseconds;

    printf("\n===== 구간 기록 =====\n\n");

    if (lap_count == 0)
    {
        printf("저장된 구간 기록이 없습니다.\n");
        return;
    }

    for (i = 0; i < lap_count; i++)
    {
        lap_minutes = (lap_times[i] / 60000) % 100;
        lap_seconds = (lap_times[i] / 1000) % 60;
        lap_milliseconds = lap_times[i] % 1000;

        total_minutes = (total_times[i] / 60000) % 100;
        total_seconds = (total_times[i] / 1000) % 60;
        total_milliseconds = total_times[i] % 1000;

        printf("Lap %d | ", i + 1);

        printf("구간 시간: %02lld:%02lld:%03lld | ",
               lap_minutes, lap_seconds, lap_milliseconds);

        printf("누적 시간: %02lld:%02lld:%03lld\n",
               total_minutes, total_seconds, total_milliseconds);
    }
}

/* 디지털 숫자로 경과 시간을 표시하는 스톱워치입니다. */
void play_stopwatch_mode(void)
{
    typedef std::chrono::steady_clock StopwatchClock;
    StopwatchClock::time_point start_time;
    StopwatchClock::time_point current_time;

    long long elapsed_ms = 0;
    long long accumulated_ms = 0;

    /* 구간 기록을 저장할 배열입니다. */
    long long lap_times[100];
    long long total_times[100];

    /* 직전 구간 기록 시점의 누적 시간입니다. */
    long long last_lap_ms = 0;

    int lap_count = 0;
    int key;
    int running = 0;

    system("cls");

    printf("===== 디지털 스톱워치 =====\n\n");
    printf("아무 키나 누르면 스톱워치가 시작됩니다.\n");
    printf("작동 중 j 키: 일시 정지\n");
    printf("작동 중 l 키: 구간 기록\n");
    printf("정지 중 k 키: 다시 시작\n");
    printf("정지 중 j 키: 0으로 초기화\n");
    printf("정지 중 l 키: 구간 기록\n");
    printf("정지 중 0 키: 메인 메뉴로 돌아가기\n");

    /* 시작을 알리는 첫 번째 키 입력은 측정에 포함하지 않습니다. */
    read_key_press();
    start_time = StopwatchClock::now();
    running = 1;

    while (1)
    {
        if (running)
        {
            /* 작동 중에는 j 키와 l 키를 처리합니다. */
            if (_kbhit())
            {
                key = read_key_press();

                if (key == 'j' || key == 'J')
                {
                    current_time = StopwatchClock::now();

                    accumulated_ms +=
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            current_time - start_time).count();

                    running = 0;

                    system("cls");
                    printf("===== 스톱워치 일시 정지 =====\n\n");
                    print_digital_stopwatch(accumulated_ms);

                    print_lap_records(lap_times, total_times, lap_count);

                    printf("\n정지 상태에서 선택하세요.\n");
                    printf("j : 초기화\n");
                    printf("k : 다시 시작\n");
                    printf("l : 구간 기록\n");
                    printf("0 : 메인 메뉴로 돌아가기\n");
                }
                else if (key == 'l' || key == 'L')
                {
                    /* 현재까지의 경과 시간을 계산합니다. */
                    current_time = StopwatchClock::now();

                    elapsed_ms = accumulated_ms +
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            current_time - start_time).count();

                    /* 구간 기록을 배열에 저장합니다. */
                    if (lap_count < 100)
                    {
                        lap_times[lap_count] = elapsed_ms - last_lap_ms;
                        total_times[lap_count] = elapsed_ms;

                        last_lap_ms = elapsed_ms;
                        lap_count++;
                    }
                }
            }

            if (running)
            {
                current_time = StopwatchClock::now();

                elapsed_ms = accumulated_ms +
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        current_time - start_time).count();

                system("cls");
                printf("===== 디지털 스톱워치 =====\n\n");

                print_digital_stopwatch(elapsed_ms);

                print_lap_records(lap_times, total_times, lap_count);

                printf("\nj 키: 일시 정지 | l 키: 구간 기록\n");

                if (lap_count >= 100)
                    printf("구간 기록이 최대 개수(100개)에 도달했습니다.\n");

                /* 10밀리초 간격으로 화면을 갱신합니다. */
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        else
        {
            /* 일시 정지 상태에서는 명령 키 입력을 기다립니다. */
            key = read_key_press();

            if (key == '0')
            {
                /* 정지 상태에서 0을 누르면 메인 메뉴로 복귀합니다. */
                return;
            }
            else if (key == 'k' || key == 'K')
            {
                /* 누적 시간은 유지하고 새 시작 시각부터 다시 측정합니다. */
                start_time = StopwatchClock::now();
                running = 1;
            }
            else if (key == 'j' || key == 'J')
            {
                /* 누적 시간과 구간 기록을 모두 초기화합니다. */
                accumulated_ms = 0;
                elapsed_ms = 0;
                last_lap_ms = 0;
                lap_count = 0;

                system("cls");
                printf("===== 스톱워치 초기화 =====\n\n");

                print_digital_stopwatch(0);

                print_lap_records(lap_times, total_times, lap_count);

                printf("\n초기화되었습니다. 현재 정지 상태입니다.\n");
                printf("k : 시작\n");
                printf("l : 구간 기록\n");
                printf("0 : 메인 메뉴로 돌아가기\n");
            }
            else if (key == 'l' || key == 'L')
            {
                /* 정지 상태에서는 현재 누적 시간을 기록합니다. */
                elapsed_ms = accumulated_ms;

                if (lap_count < 100)
                {
                    lap_times[lap_count] = elapsed_ms - last_lap_ms;
                    total_times[lap_count] = elapsed_ms;

                    last_lap_ms = elapsed_ms;
                    lap_count++;
                }

                system("cls");

                printf("===== 스톱워치 일시 정지 =====\n\n");

                print_digital_stopwatch(accumulated_ms);

                print_lap_records(lap_times, total_times, lap_count);

                printf("\nk : 다시 시작\n");
                printf("j : 초기화\n");
                printf("l : 구간 기록\n");
                printf("0 : 메인 메뉴로 돌아가기\n");

                if (lap_count >= 100)
                    printf("\n구간 기록이 최대 개수(100개)에 도달했습니다.\n");
            }
        }
    }
}

/* 텍스트 파일에서 최고 기록을 읽어옵니다. */
int load_best_score(void)
{
    FILE *record_file;
    int best_score = 0;

    record_file = fopen("record.txt", "r");

    /* 기록 파일이 없으면 최초 실행으로 간주하고 0회를 반환합니다. */
    if (record_file == NULL)
        return 0;

    /* 파일에 저장된 숫자를 최고 기록으로 읽습니다. */
    if (fscanf(record_file, "%d", &best_score) != 1 || best_score < 0)
        best_score = 0;

    fclose(record_file);

    return best_score;
}

/* 새로운 최고 기록을 텍스트 파일에 저장합니다. */
int save_best_score(int score)
{
    FILE *record_file;

    record_file = fopen("record.txt", "w");

    if (record_file == NULL)
        return 0;

    fprintf(record_file, "%d\n", score);
    fclose(record_file);

    return 1;
}

/* 확장 키도 한 번의 입력으로 처리합니다. */
int read_key_press(void)
{
    int key = _getch();

    /* 방향키, 기능키 등 일부 특수 키는 추가 코드가 전달됩니다. */
    if (key == 0 || key == 224)
        _getch();

    return key;
}

/* 10초 동안 키 입력 횟수를 세는 게임입니다. */
void play_key_count_game(void)
{
    int key_count = 0;
    int best_score;
    int elapsed_seconds;
    int remaining_seconds;
    int previous_remaining = -1;
    int new_record = 0;
    int save_success = 1;
    clock_t start_time;
    clock_t current_time;
    clock_t result_start_time;

    /* 게임을 시작하기 전에 파일에 저장된 최고 기록을 읽습니다. */
    best_score = load_best_score();

    system("cls");

    printf("===== 키 입력 횟수 게임 =====\n\n");
    printf("현재 최고 기록: %d회\n\n", best_score);
    printf("아무 키나 한 번 누르면 게임이 시작됩니다.\n");
    printf("시작을 알리는 키 입력은 횟수에 포함하지 않습니다.\n");

    /* 첫 번째 키 입력을 시작 신호로 사용합니다. */
    read_key_press();
    start_time = clock();

    /* 제한 시간 10초 동안 키 입력을 받습니다. */
    while (1)
    {
        current_time = clock();
        elapsed_seconds =
            (int)((double)(current_time - start_time) / CLOCKS_PER_SEC);

        if (elapsed_seconds >= 10)
            break;

        remaining_seconds = 10 - elapsed_seconds;

        /* 남은 시간이 바뀔 때만 화면을 다시 출력합니다. */
        if (remaining_seconds != previous_remaining)
        {
            system("cls");

            printf("===== 키 입력 횟수 게임 =====\n\n");
            printf("남은 시간\n\n");
            /* 3번 모드의 디지털 숫자는 항상 흰색으로 출력합니다. */
            set_text_color(digital_white_color);
            print_digital_time((long)remaining_seconds);
            set_text_color(base_text_color);
            printf("\n현재 입력 횟수: %d\n", key_count);
            printf("최고 기록: %d회\n", best_score);

            previous_remaining = remaining_seconds;
        }

        /* 입력된 키가 있으면 한 번의 입력으로 계산합니다. */
        if (_kbhit())
        {
            read_key_press();
            key_count++;
        }
    }

    /* 이번 점수가 최고 기록보다 높으면 새 기록으로 저장합니다. */
    if (key_count > best_score)
    {
        best_score = key_count;
        new_record = 1;
        save_success = save_best_score(best_score);
    }

    system("cls");

    printf("===== 게임 종료 =====\n\n");
    printf("제한 시간 10초가 종료되었습니다.\n\n");
    printf("이번 입력 횟수: %d회\n", key_count);
    printf("최고 기록: %d회\n", best_score);

    if (new_record)
    {
        if (save_success)
            printf("축하합니다! 새로운 최고 기록을 저장했습니다.\n");
        else
            printf("새 기록이지만 record.txt 파일 저장에 실패했습니다.\n");
    }
    else
    {
        printf("최고 기록을 갱신하지 못했습니다.\n");
    }

    printf("\n점수를 확인할 수 있도록 3초 동안 키 입력을 무시합니다.\n");

    /* 게임 종료 후 3초 동안 입력을 버려 점수 화면이 유지되도록 합니다. */
    result_start_time = clock();

    while ((double)(clock() - result_start_time) / CLOCKS_PER_SEC < 3.0)
    {
        /* 10초 게임 중 남아 있는 입력과 3초 동안의 입력을 모두 비웁니다. */
        while (_kbhit())
        {
            read_key_press();
        }
    }

    /* 3초가 지난 뒤부터 새로운 키 입력을 받아 메뉴로 돌아갑니다. */
    printf("\n아무 키나 누르면 메뉴로 돌아갑니다.\n");

    while (_kbhit())
    {
        read_key_press();
    }

    _getch();
}

/* 정수를 8비트 2의 보수 비트 패턴으로 디지털 숫자에 표시합니다. */
void print_binary_number(int value)
{
    unsigned int bits = (unsigned int)value & 0xFF;
    int i;
    int row;

    /* 4번 모드의 디지털 숫자는 항상 흰색으로 출력합니다. */
    set_text_color(digital_white_color);

    /* 부호와 관계없이 하위 8비트만 사용합니다. */
    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < 8; i++)
        {
            int bit = (bits >> (7 - i)) & 1;
            print_digit_row(bit, row);

            if (i < 7)
                printf("  ");
        }

        printf("\n");
    }

    set_text_color(base_text_color);
}

/* 부호 없는 8비트 또는 부호 있는 8비트 정수를 선택해 입력받습니다. */
int read_signed_binary_value(const char *title, int *value, int *is_signed)
{
    int number_choice;
    int input_value;
    int ch;

    system("cls");
    printf("===== %s =====\n\n", title);
    printf("표현 방식을 선택하세요.\n");
    printf("1. 양수 / 부호 없는 정수 (0 ~ 255)\n");
    printf("2. 음수 포함 / 부호 있는 정수 (-128 ~ 127)\n\n");
    printf("선택: ");

    if (scanf("%d", &number_choice) != 1)
    {
        printf("잘못된 입력입니다.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (number_choice != 1 && number_choice != 2)
    {
        printf("1 또는 2만 선택할 수 있습니다.\n");
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return 0;
    }

    if (number_choice == 1)
    {
        *is_signed = 0;
        printf("\n양수(부호 없는 정수)를 입력하세요 (0~255): ");
    }
    else
    {
        *is_signed = 1;
        printf("\n부호 있는 정수를 입력하세요 (-128~127): ");
    }

    if (scanf("%d", &input_value) != 1)
    {
        printf("잘못된 입력입니다. 정수를 입력하세요.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (!*is_signed)
    {
        if (input_value < 0 || input_value > 255)
        {
            printf("부호 없는 정수는 0부터 255까지만 입력할 수 있습니다.\n");
            printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
            _getch();
            return 0;
        }
    }
    else
    {
        if (input_value < -128 || input_value > 127)
        {
            printf("부호 있는 정수는 -128부터 127까지만 입력할 수 있습니다.\n");
            printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
            _getch();
            return 0;
        }
    }

    *value = input_value;
    return 1;
}

/* 4번 모드에서 실행할 하위 메뉴입니다. */
void play_binary_mode_menu(void)
{
    int choice;
    int ch;

    while (1)
    {
        system("cls");

        printf("===== 이진수 모드 =====\n\n");
        printf("1. 8자리 이진수 표기\n");
        printf("2. 이진수 보고 정수 맞히기 게임\n");
        printf("3. 8자리 이진수 2의 보수 표기\n");
        printf("4. 8자리 이진수 시프트 연산\n");
        printf("0. 이전 메뉴로 돌아가기\n\n");
        printf("원하는 기능을 선택하세요: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            wait_seconds(1.0);
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        if (choice == 0)
            return;
        else if (choice == 1)
            play_binary_display_mode();
        else if (choice == 2)
            play_binary_guess_game();
        else if (choice == 3)
            play_binary_twos_complement_mode();
        else if (choice == 4)
            play_binary_shift_mode();
        else
        {
            printf("잘못된 메뉴 선택입니다.\n");
            wait_seconds(1.0);
        }
    }
}

/* 양수 또는 음수를 선택한 뒤 8자리 이진수로 출력합니다. */
void play_binary_display_mode(void)
{
    int value;
    int is_signed;

    if (!read_signed_binary_value("8자리 이진수 표기", &value, &is_signed))
        return;

    system("cls");
    printf("===== 8자리 이진수 표기 =====\n\n");
    printf("입력한 정수: %d\n", value);
    printf("표현 방식: %s\n", is_signed ? "부호 있는 8비트 정수" : "부호 없는 8비트 정수");
    printf("8비트 이진수 표현:\n\n");
    print_binary_number(value);

    printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
    _getch();
}

/* 입력한 양수의 음수 값을 8비트 2의 보수로 계산해 표시합니다.
   부호 있는 모드에서 음수를 입력한 경우에는 해당 음수 자체를 표현합니다. */
void play_binary_twos_complement_mode(void)
{
    int value;
    int is_signed;
    int magnitude;
    int encoded;
    int signed_result;

    if (!read_signed_binary_value("8자리 이진수 2의 보수 표기", &value, &is_signed))
        return;

    /* 양수 42를 입력하면 -42의 8비트 2의 보수인 11010110을 계산합니다.
       이미 음수를 입력했다면 그 음수의 비트 패턴을 그대로 계산합니다. */
    if (is_signed && value < 0)
    {
        magnitude = -value;
        encoded = ((~magnitude + 1) & 0xFF);
        signed_result = value;
    }
    else
    {
        magnitude = value;
        encoded = ((~magnitude + 1) & 0xFF);
        signed_result = (encoded >= 128) ? encoded - 256 : encoded;
    }

    system("cls");
    printf("===== 8자리 이진수 2의 보수 표기 =====\n\n");
    printf("입력한 정수: %d\n", value);
    printf("표현 방식: %s\n", is_signed ? "부호 있는 8비트 정수" : "부호 없는 8비트 정수");
    printf("\n절댓값 %d의 8비트 이진수:\n\n", magnitude);
    print_binary_number(magnitude);
    printf("\n1의 보수 (비트 반전):\n\n");
    print_binary_number((~magnitude) & 0xFF);
    printf("\n1을 더한 2의 보수 결과:\n\n");
    print_binary_number(encoded);
    printf("\n2의 보수 비트 패턴의 부호 있는 정수 값: %d\n", signed_result);

    printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
    _getch();
}

/* 양수 또는 음수의 8비트 패턴에 1비트 시프트 연산을 수행합니다. */
void play_binary_shift_mode(void)
{
    int value;
    int is_signed;
    int operator_choice;
    int result_bits;
    int result_value;
    int bits;
    int ch;

    if (!read_signed_binary_value("8자리 이진수 시프트 연산", &value, &is_signed))
        return;

    bits = value & 0xFF;

    system("cls");
    printf("===== 8자리 이진수 시프트 연산 =====\n\n");
    printf("입력한 정수: %d\n", value);
    printf("표현 방식: %s\n", is_signed ? "부호 있는 8비트 정수" : "부호 없는 8비트 정수");
    printf("연산 전 8자리 이진수:\n\n");
    print_binary_number(value);

    printf("\n연산자를 선택하세요.\n");
    printf("1. 왼쪽 시프트 (<<)\n");
    printf("2. 오른쪽 시프트 (>>)\n");
    printf("3. 논리적 오른쪽 시프트 (>>>)\n");
    printf("\n선택: ");

    if (scanf("%d", &operator_choice) != 1)
    {
        printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (operator_choice == 1)
    {
        /* 8비트를 벗어나는 왼쪽 비트는 버립니다. */
        result_bits = (bits << 1) & 0xFF;
    }
    else if (operator_choice == 2)
    {
        /* 부호 있는 음수만 산술적 오른쪽 시프트로 부호 비트를 유지합니다.
           부호 없는 정수는 왼쪽 빈자리를 0으로 채웁니다. */
        result_bits = bits >> 1;
        if (is_signed && (bits & 0x80))
            result_bits |= 0x80;
    }
    else if (operator_choice == 3)
    {
        /* 논리적 오른쪽 시프트는 왼쪽 빈자리를 항상 0으로 채웁니다. */
        result_bits = bits >> 1;
    }
    else
    {
        printf("잘못된 연산자 선택입니다. 1부터 3까지 입력하세요.\n");
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return;
    }

    /* 입력 표현 방식에 맞춰 결과 비트 패턴을 정수로 해석합니다. */
    if (is_signed)
        result_value = (result_bits >= 128) ? result_bits - 256 : result_bits;
    else
        result_value = result_bits;

    system("cls");
    printf("===== 8자리 이진수 시프트 연산 결과 =====\n\n");
    printf("입력한 정수: %d\n", value);
    printf("연산 전 8자리 이진수:\n\n");
    print_binary_number(value);

    printf("\n선택한 연산자: ");
    if (operator_choice == 1)
        printf("<< (왼쪽 시프트)\n");
    else if (operator_choice == 2)
    {
        if (is_signed)
            printf(">> (부호 있는 산술적 오른쪽 시프트)\n");
        else
            printf(">> (부호 없는 논리적 오른쪽 시프트)\n");
    }
    else
        printf(">>> (논리적 오른쪽 시프트)\n");

    printf("이동 횟수: 1비트\n");
    printf("\n연산 결과의 8비트 패턴:\n\n");
    print_binary_number(result_bits);
    printf("\n연산 결과 정수(%s 해석): %d\n",
           is_signed ? "부호 있는 8비트" : "부호 없는 8비트",
           result_value);

    printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
    _getch();
}

/* 부호 없는 8비트 또는 부호 있는 8비트 정수의 이진수를 맞히는 게임입니다. */
void play_binary_guess_game(void)
{
    int number_choice;
    int answer;
    int guess;
    int attempts = 0;
    int ch;

    system("cls");
    printf("===== 이진수 보고 정수 맞히기 =====\n\n");
    printf("정답의 표현 방식을 선택하세요.\n");
    printf("1. 양수 / 부호 없는 정수 (0 ~ 255)\n");
    printf("2. 음수 포함 / 부호 있는 정수 (-128 ~ 127)\n\n");
    printf("선택: ");

    if (scanf("%d", &number_choice) != 1)
    {
        printf("잘못된 입력입니다.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (number_choice == 1)
    {
        answer = rand() % 256;
    }
    else if (number_choice == 2)
    {
        answer = (rand() % 256) - 128;
    }
    else
    {
        printf("1 또는 2만 선택할 수 있습니다.\n");
        printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
        _getch();
        return;
    }

    system("cls");
    printf("===== 이진수 보고 정수 맞히기 =====\n\n");
    printf("아래에 표시된 8자리 이진수가 나타내는 정수를 맞혀보세요.\n");
    if (number_choice == 1)
        printf("정답 범위: 0부터 255까지\n\n");
    else
        printf("정답 범위: -128부터 127까지\n\n");

    print_binary_number(answer);
    printf("\n");

    while (1)
    {
        printf("정수 입력: ");

        if (scanf("%d", &guess) != 1)
        {
            printf("잘못된 입력입니다. 정수를 입력하세요.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF) {}

        if ((number_choice == 1 && (guess < 0 || guess > 255)) ||
            (number_choice == 2 && (guess < -128 || guess > 127)))
        {
            if (number_choice == 1)
                printf("0부터 255 사이의 정수를 입력하세요.\n\n");
            else
                printf("-128부터 127 사이의 정수를 입력하세요.\n\n");
            continue;
        }

        attempts++;

        if (guess == answer)
        {
            printf("\n정답입니다!\n");
            printf("정답: %d\n", answer);
            printf("시도 횟수: %d회\n", attempts);
            break;
        }
        else if (guess < answer)
        {
            printf("틀렸습니다. 정답은 입력한 값보다 큰 수입니다.\n\n");
        }
        else
        {
            printf("틀렸습니다. 정답은 입력한 값보다 작은 수입니다.\n\n");
        }
    }

    printf("\n아무 키나 누르면 이전 메뉴로 돌아갑니다.\n");
    _getch();
}

/* 블랙잭 카드 한 장을 출력합니다. */
void print_blackjack_card(int rank, int suit)
{
    const char *rank_names[14] =
    {
        "", "A", "2", "3", "4", "5", "6",
        "7", "8", "9", "10", "J", "Q", "K"
    };

    const char *suit_names[4] =
    {
        "S", "H", "D", "C"
    };

    printf("+-------+\n");
    printf("| %-2s    |\n", rank_names[rank]);
    printf("|   %s   |\n", suit_names[suit]);
    printf("|    %-2s |\n", rank_names[rank]);
    printf("+-------+\n");
}

/* 블랙잭 카드 패를 출력합니다. */
void print_blackjack_hand(int cards[], int suits[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        print_blackjack_card(cards[i], suits[i]);
        printf("\n");
    }
}

/* 블랙잭 점수를 기존 디지털 숫자 출력 함수로 표시합니다. */
void print_blackjack_score(int score)
{
    int digits[2];
    int row;
    int i;

    digits[0] = score / 10;
    digits[1] = score % 10;

    set_text_color(digital_white_color);

    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < 2; i++)
        {
            print_digit_row(digits[i], row);

            if (i == 0)
                printf("  ");
        }

        printf("\n");
    }

    set_text_color(base_text_color);
}

/* 블랙잭 카드 패의 합계를 계산합니다. */
int calculate_blackjack_score(int cards[], int count)
{
    int total = 0;
    int ace_count = 0;
    int i;
    int value;

    for (i = 0; i < count; i++)
    {
        if (cards[i] == 1)
        {
            /* 에이스는 우선 11점으로 계산합니다. */
            total += 11;
            ace_count++;
        }
        else if (cards[i] >= 11)
        {
            /* J, Q, K는 10점입니다. */
            total += 10;
        }
        else
        {
            total += cards[i];
        }
    }

    /* 21점을 초과하면 에이스를 11점에서 1점으로 변경합니다. */
    while (total > 21 && ace_count > 0)
    {
        total -= 10;
        ace_count--;
    }

    return total;
}

/* 6번 모드: 디지털 블랙잭 게임입니다. */
void play_blackjack_mode(void)
{
    int deck[52];
    int deck_suits[52];

    int player_cards[12];
    int player_suits[12];
    int dealer_cards[12];
    int dealer_suits[12];

    int deck_index = 0;
    int player_count = 0;
    int dealer_count = 0;

    int i;
    int j;
    int temp;

    int player_score;
    int dealer_score;
    int choice;
    int ch;

    int player_natural;
    int dealer_natural;
    int player_bust = 0;

    /* 52장의 카드 덱을 생성합니다. */
    for (i = 0; i < 52; i++)
    {
        deck[i] = (i % 13) + 1;
        deck_suits[i] = i / 13;
    }

    /* Fisher-Yates 방식으로 카드 덱을 섞습니다. */
    for (i = 51; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;

        temp = deck_suits[i];
        deck_suits[i] = deck_suits[j];
        deck_suits[j] = temp;
    }

    /* 플레이어와 딜러에게 번갈아 두 장씩 배분합니다. */
    player_cards[player_count] = deck[deck_index];
    player_suits[player_count] = deck_suits[deck_index];
    player_count++;
    deck_index++;

    dealer_cards[dealer_count] = deck[deck_index];
    dealer_suits[dealer_count] = deck_suits[deck_index];
    dealer_count++;
    deck_index++;

    player_cards[player_count] = deck[deck_index];
    player_suits[player_count] = deck_suits[deck_index];
    player_count++;
    deck_index++;

    dealer_cards[dealer_count] = deck[deck_index];
    dealer_suits[dealer_count] = deck_suits[deck_index];
    dealer_count++;
    deck_index++;

    player_score = calculate_blackjack_score(player_cards, player_count);
    dealer_score = calculate_blackjack_score(dealer_cards, dealer_count);

    player_natural = (player_score == 21);
    dealer_natural = (dealer_score == 21);

    /* 플레이어의 선택 단계입니다. */
    while (1)
    {
        system("cls");

        printf("====================================\n");
        printf("          DIGITAL BLACKJACK\n");
        printf("====================================\n\n");

        printf("[ DEALER ]\n\n");

        print_blackjack_card(dealer_cards[0], dealer_suits[0]);

        if (dealer_count >= 2)
        {
            printf("+-------+\n");
            printf("|   ?   |\n");
            printf("|  ???  |\n");
            printf("|   ?   |\n");
            printf("+-------+\n");
        }

        printf("\n공개된 카드 점수: ");

        if (dealer_cards[0] == 1)
            printf("1 또는 11\n");
        else if (dealer_cards[0] >= 10)
            printf("10\n");
        else
            printf("%d\n", dealer_cards[0]);

        printf("\n====================================\n\n");

        printf("[ PLAYER ]\n\n");

        print_blackjack_hand(player_cards, player_suits, player_count);

        player_score = calculate_blackjack_score(player_cards, player_count);

        printf("PLAYER SCORE\n\n");
        print_blackjack_score(player_score);

        printf("\n점수: %d\n", player_score);

        printf("\n====================================\n");

        /* 플레이어가 21점을 초과하면 즉시 패배합니다. */
        if (player_score > 21)
        {
            player_bust = 1;
            break;
        }

        /* 최초 두 장으로 21점을 만들었다면 블랙잭입니다. */
        if (player_natural)
            break;

        printf("\n1. HIT\n");
        printf("2. STAND\n");
        printf("0. 메뉴로 돌아가기\n\n");
        printf("선택: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            wait_seconds(1.0);
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        if (choice == 0)
            return;

        if (choice == 1)
        {
            /* 카드를 한 장 더 받습니다. */
            if (player_count < 12 && deck_index < 52)
            {
                player_cards[player_count] = deck[deck_index];
                player_suits[player_count] = deck_suits[deck_index];

                player_count++;
                deck_index++;
            }
            else
            {
                printf("더 이상 카드를 받을 수 없습니다.\n");
                wait_seconds(1.0);
                break;
            }
        }
        else if (choice == 2)
        {
            /* 현재 카드로 승부를 진행합니다. */
            break;
        }
        else
        {
            printf("잘못된 선택입니다.\n");
            wait_seconds(1.0);
        }
    }

    /* 플레이어가 버스트하지 않았고 블랙잭도 아닌 경우 딜러가 진행합니다. */
    if (!player_bust && !player_natural)
    {
        while (1)
        {
            dealer_score =
                calculate_blackjack_score(dealer_cards, dealer_count);

            /* 딜러는 17점 이상이면 카드를 받지 않습니다. */
            if (dealer_score >= 17)
                break;

            if (dealer_count >= 12 || deck_index >= 52)
                break;

            dealer_cards[dealer_count] = deck[deck_index];
            dealer_suits[dealer_count] = deck_suits[deck_index];

            dealer_count++;
            deck_index++;
        }
    }

    /* 최종 결과를 출력합니다. */
    system("cls");

    player_score = calculate_blackjack_score(player_cards, player_count);
    dealer_score = calculate_blackjack_score(dealer_cards, dealer_count);

    printf("====================================\n");
    printf("          BLACKJACK RESULT\n");
    printf("====================================\n\n");

    printf("[ DEALER ]\n\n");
    print_blackjack_hand(dealer_cards, dealer_suits, dealer_count);

    printf("DEALER SCORE\n\n");
    print_blackjack_score(dealer_score);
    printf("\n점수: %d\n", dealer_score);

    printf("\n====================================\n\n");

    printf("[ PLAYER ]\n\n");
    print_blackjack_hand(player_cards, player_suits, player_count);

    printf("PLAYER SCORE\n\n");
    print_blackjack_score(player_score);
    printf("\n점수: %d\n", player_score);

    printf("\n====================================\n\n");

    /* 블랙잭 및 승패를 판정합니다. */
    if (player_bust)
    {
        printf("PLAYER BUST!\n");
        printf("플레이어가 21점을 초과했습니다.\n");
        printf("딜러 승리!\n");
    }
    else if (player_natural && dealer_natural)
    {
        printf("BOTH BLACKJACK!\n");
        printf("무승부입니다.\n");
    }
    else if (player_natural)
    {
        printf("BLACKJACK!\n");
        printf("플레이어 승리!\n");
    }
    else if (dealer_natural)
    {
        printf("DEALER BLACKJACK!\n");
        printf("딜러 승리!\n");
    }
    else if (dealer_score > 21)
    {
        printf("DEALER BUST!\n");
        printf("딜러가 21점을 초과했습니다.\n");
        printf("플레이어 승리!\n");
    }
    else if (player_score > dealer_score)
    {
        printf("PLAYER WIN!\n");
        printf("플레이어 승리!\n");
    }
    else if (player_score < dealer_score)
    {
        printf("DEALER WIN!\n");
        printf("딜러 승리!\n");
    }
    else
    {
        printf("DRAW!\n");
        printf("무승부입니다.\n");
    }

    printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
    _getch();
}

/* 분:초:밀리초를 디지털 숫자로 출력합니다.
   hide_seconds가 1이면 초의 두 자리를 숨깁니다. */
void print_digital_accuracy_time(long long elapsed_ms,
                                 int hide_seconds)
{
    int minutes;
    int seconds;
    int milliseconds;
    int digits[7];
    int row;
    int i;

    minutes = (int)((elapsed_ms / 60000) % 100);
    seconds = (int)((elapsed_ms / 1000) % 60);
    milliseconds = (int)(elapsed_ms % 1000);

    digits[0] = minutes / 10;
    digits[1] = minutes % 10;
    digits[2] = seconds / 10;
    digits[3] = seconds % 10;
    digits[4] = milliseconds / 100;
    digits[5] = (milliseconds / 10) % 10;
    digits[6] = milliseconds % 10;

    set_text_color(digital_white_color);

    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < 7; i++)
        {
            /* 3초가 지난 뒤에는 초의 두 자리를 공백으로 출력합니다. */
            if (hide_seconds && (i == 2 || i == 3))
                printf("        ");
            else
                print_digit_row(digits[i], row);

            if (i == 1 || i == 3)
            {
                printf("  ");

                if (row == 1 || row == 3)
                    printf("##");
                else
                    printf("  ");

                printf("  ");
            }
            else if (i != 6)
            {
                printf("  ");
            }
        }

        printf("\n");
    }

    set_text_color(base_text_color);
}

/* 20초에 최대 500밀리초의 오차를 허용하는 게임입니다. */
void play_20_second_game(void)
{
    typedef std::chrono::steady_clock GameClock;

    GameClock::time_point start_time;
    GameClock::time_point current_time;

    long long elapsed_ms;
    long long difference_ms;
    long long blink_start_ms;
    long long hide_after_ms;

    int key;
    int difficulty;
    int ch;
    int show_time;

    system("cls");

    printf("===== 20초 맞히기 게임 =====\n\n");
    printf("난이도를 선택하세요.\n\n");
    printf("1. 엄청 쉬움 - 시간을 계속 보여줍니다.\n");
    printf("2. 쉬움       - 5초부터 깜빡이고 10초부터 숨깁니다.\n");
    printf("3. 보통       - 3초부터 깜빡이고 7초부터 숨깁니다.\n");
    printf("4. 어려움     - 3초부터 숨깁니다.\n\n");
    printf("난이도 입력: ");

    /* 1부터 4까지의 난이도를 입력받습니다. */
    while (1)
    {
        if (scanf("%d", &difficulty) != 1)
        {
            printf("잘못된 입력입니다. 1부터 4까지 입력하세요: ");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        if (difficulty >= 1 && difficulty <= 4)
            break;

        printf("잘못된 난이도입니다. 1부터 4까지 입력하세요: ");
    }

    /* 난이도에 따라 깜빡임 시작 시간과 숨김 시간을 설정합니다. */
    if (difficulty == 1)
    {
        blink_start_ms = -1;
        hide_after_ms = -1;
    }
    else if (difficulty == 2)
    {
        blink_start_ms = 5000;
        hide_after_ms = 10000;
    }
    else if (difficulty == 3)
    {
        blink_start_ms = 3000;
        hide_after_ms = 7000;
    }
    else
    {
        blink_start_ms = -1;
        hide_after_ms = 3000;
    }

    system("cls");

    printf("===== 20초 맞히기 게임 =====\n\n");
    printf("목표 시간: 20초\n");
    printf("허용 오차: ±500밀리초\n");
    printf("성공 범위: 00:19:501 ~ 00:20:500\n\n");

    printf("선택한 난이도: ");

    if (difficulty == 1)
        printf("엄청 쉬움\n");
    else if (difficulty == 2)
        printf("쉬움\n");
    else if (difficulty == 3)
        printf("보통\n");
    else
        printf("어려움\n");

    printf("\n아무 키나 누르면 측정이 시작됩니다.\n");
    printf("측정 중 아무 키나 누르면 시간이 멈춥니다.\n");

    if (difficulty == 1)
        printf("측정이 끝날 때까지 시간이 계속 표시됩니다.\n");
    else if (difficulty == 2)
        printf("5초부터 시간이 깜빡이고 10초부터 숨겨집니다.\n");
    else if (difficulty == 3)
        printf("3초부터 시간이 깜빡이고 7초부터 숨겨집니다.\n");
    else
        printf("3초가 지나면 시간이 완전히 숨겨집니다.\n");

    /* 시작 키 입력은 측정 시간에 포함하지 않습니다. */
    read_key_press();
    start_time = GameClock::now();

    while (1)
    {
        current_time = GameClock::now();

        elapsed_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                current_time - start_time).count();

        /* 기본적으로 시간을 표시합니다. */
        show_time = 1;

        /* 숨김 시간이 지나면 디지털 시간 전체를 숨깁니다. */
        if (hide_after_ms >= 0 && elapsed_ms >= hide_after_ms)
        {
            show_time = 0;
        }
        /* 깜빡임 시작 시간이 지나면 0.5초 간격으로 표시 여부를 바꿉니다. */
        else if (blink_start_ms >= 0 &&
                 elapsed_ms >= blink_start_ms)
        {
            if (((elapsed_ms - blink_start_ms) % 1000) >= 500)
                show_time = 0;
        }

        system("cls");

        printf("===== 20초 맞히기 게임 =====\n\n");

        if (show_time)
        {
            printf("목표 시간: 00:20:000\n\n");
            print_digital_accuracy_time(elapsed_ms, 0);
        }
        else
        {
            printf("목표 시간: 비공개\n\n");
            printf("시간을 확인하지 말고 20초를 맞혀보세요!\n");
        }

        printf("\n아무 키나 누르면 시간을 멈춥니다.\n");

        /* 키 입력이 들어오면 측정을 종료합니다. */
        if (_kbhit())
        {
            key = read_key_press();
            (void)key;

            current_time = GameClock::now();

            elapsed_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    current_time - start_time).count();

            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    /* 최종 결과에서는 시간을 다시 표시합니다. */
    system("cls");

    printf("===== 20초 맞히기 게임 결과 =====\n\n");

    print_digital_accuracy_time(elapsed_ms, 0);

    difference_ms = elapsed_ms - 20000;

    printf("\n측정 시간: %02lld:%02lld:%03lld\n",
           (elapsed_ms / 60000) % 100,
           (elapsed_ms / 1000) % 60,
           elapsed_ms % 1000);

    if (elapsed_ms >= 19501 && elapsed_ms <= 20500)
    {
        printf("\n성공! 목표 범위 시간을 맞혔습니다.\n");
    }
    else if (elapsed_ms < 19501)
    {
        printf("\n실패! 너무 일찍 멈췄습니다.\n");
    }
    else
    {
        printf("\n실패! 너무 늦게 멈췄습니다.\n");
    }

    if (difference_ms > 0)
        printf("오차 : %lld밀리초\n", difference_ms);
    else if (difference_ms < 0)
        printf("오차 : -%lld밀리초\n", -difference_ms);
    else
        printf("목표 시간과 정확히 일치합니다!\n");

    printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
    read_key_press();
}

/* 네 자리 또는 여섯 자리 숫자를 디지털 형태로 출력합니다. */
void print_digital_vault_code(const char code[], const int colors[], int length)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    /* 금고 숫자의 기본색은 흰색이며, 힌트가 있는 자리만 별도 색을 사용합니다. */
    WORD default_color = digital_white_color;
    int row;
    int i;

    /* 금고의 디지털 숫자는 프로그램 시작 당시의 숫자색을 기본으로 사용합니다. */

    for (row = 0; row < 5; row++)
    {
        for (i = 0; i < length; i++)
        {
            /* 위치까지 맞으면 초록색, 숫자만 맞으면 노란색으로 표시합니다. */
            if (colors[i] == 1)
                SetConsoleTextAttribute(
                    console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else if (colors[i] == 2)
                SetConsoleTextAttribute(
                    console,
                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else
                SetConsoleTextAttribute(console, default_color);

            print_digit_row(code[i] - '0', row);
            SetConsoleTextAttribute(console, default_color);

            if (i < length - 1)
                printf("  ");
        }
        printf("\n");
    }

    /* 다른 출력에는 사용자가 설정한 일반 글자색을 적용합니다. */
    SetConsoleTextAttribute(console, base_text_color);
}

/* 8번 모드: 네 자리 또는 중복 가능한 여섯 자리 디지털 비밀금고입니다. */
void play_digital_vault_game(void)
{
    int vault_type;
    int ch;

    while (1)
    {
        system("cls");

        printf("===== DIGITAL SECRET VAULT =====\n\n");
        printf("입장할 비밀금고를 선택하세요.\n\n");
        printf("1. 일반 금고 - 4자리 / 숫자 중복 불가\n");
        printf("2. 확장 금고 - 6자리 / 숫자 중복 가능\n\n");
        printf("선택: ");

        if (scanf("%d", &vault_type) != 1)
        {
            printf("\n잘못된 입력입니다. 1 또는 2를 입력하세요.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            wait_seconds(1.0);
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF) {}

        if (vault_type == 1)
        {
            play_digital_vault_mode(4, 0);
            return;
        }
        else if (vault_type == 2)
        {
            play_digital_vault_mode(6, 1);
            return;
        }

        printf("\n잘못된 선택입니다. 1 또는 2를 입력하세요.\n");
        wait_seconds(1.0);
    }
}

/* 선택한 자릿수와 중복 허용 여부에 따라 비밀금고 게임을 실행합니다. */
void play_digital_vault_mode(int code_length, int allow_duplicates)
{
    int digits[10];
    int i;
    int j;
    int temp;
    int ch;

    int attempts = 0;
    int is_correct;
    int valid;
    int correct_position;
    int correct_number;
    int matched[6] = { 0, 0, 0, 0, 0, 0 };
    int digit_colors[6] = { 0, 0, 0, 0, 0, 0 };

    char secret[7];
    char display[7] = "000000";
    char guess[8];

    /* 유효한 입력을 모두 저장하는 기록입니다. */
    std::vector<VaultAttempt> history;
    VaultAttempt current_attempt;

    if (allow_duplicates)
    {
        /* 6자리 금고는 각 자리를 독립적으로 뽑아 숫자 중복을 허용합니다. */
        for (i = 0; i < code_length; i++)
            secret[i] = (char)('0' + rand() % 10);
    }
    else
    {
        /* 4자리 금고는 0부터 9까지의 숫자를 섞어 중복 없이 선택합니다. */
        for (i = 0; i < 10; i++)
            digits[i] = i;

        /* Fisher-Yates 방식으로 숫자를 무작위로 섞습니다. */
        for (i = 9; i > 0; i--)
        {
            j = rand() % (i + 1);
            temp = digits[i];
            digits[i] = digits[j];
            digits[j] = temp;
        }

        for (i = 0; i < code_length; i++)
            secret[i] = (char)('0' + digits[i]);
    }

    secret[code_length] = '\0';
    display[code_length] = '\0';

    while (1)
    {
        system("cls");

        printf("===== DIGITAL SECRET VAULT =====\n\n");
        printf("%d자리 비밀번호를 맞혀 금고를 여세요!\n", code_length);
        printf("비밀번호는 0부터 9까지의 숫자로 구성됩니다.\n");

        if (allow_duplicates)
            printf("각 숫자는 중복될 수 있습니다.\n\n");
        else
            printf("각 숫자는 중복되지 않습니다.\n\n");

        printf("현재 금고 입력 번호\n\n");
        print_digital_vault_code(display, digit_colors, code_length);

        printf("\n색상 힌트: 초록색 = 위치까지 일치, 노란색 = 숫자만 일치\n");
        printf("\n시도 횟수: %d회\n", attempts);

        /* 이전에 입력한 모든 시도와 판정 결과를 표시합니다. */
        if (!history.empty())
        {
            printf("\n================ 이전 시도 기록 ================\n");
            printf("회차    입력 번호       위치 일치    숫자 일치\n");
            printf("------------------------------------------------\n");

            for (i = 0; i < (int)history.size(); i++)
            {
                printf("%3d회      %s             %d개          %d개\n",
                       i + 1,
                       history[i].guess,
                       history[i].correct_position,
                       history[i].correct_number);
            }

            printf("================================================\n");
        }

        printf("\n%d자리 번호 입력: ", code_length);

        /* 입력 버퍼 크기를 제한하고, 실제 자릿수는 아래에서 검증합니다. */
        if (scanf("%7s", guess) != 1)
            return;

        while ((ch = getchar()) != '\n' && ch != EOF) {}

        /* 입력한 값이 정확히 지정된 자릿수의 숫자인지 검사합니다. */
        valid = 1;

        for (i = 0; i < code_length; i++)
        {
            if (guess[i] == '\0' || guess[i] < '0' || guess[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (guess[code_length] != '\0')
            valid = 0;

        if (!valid)
        {
            printf("\n잘못된 입력입니다. 정확히 %d자리 숫자를 입력하세요.\n",
                   code_length);
            wait_seconds(1.0);
            continue;
        }

        /* 입력한 번호를 현재 디지털 표기에 반영합니다. */
        for (i = 0; i < code_length; i++)
            display[i] = guess[i];

        display[code_length] = '\0';
        attempts++;

        /* 비교 전에 색상과 일치 판정 배열을 초기화합니다. */
        is_correct = 1;
        correct_position = 0;
        correct_number = 0;

        for (i = 0; i < code_length; i++)
        {
            matched[i] = 0;
            digit_colors[i] = 0;

            if (guess[i] == secret[i])
            {
                correct_position++;
                matched[i] = 1;
                digit_colors[i] = 1; /* 초록색: 숫자와 위치 모두 일치 */
            }
            else
            {
                is_correct = 0;
            }
        }

        /*
         * 위치가 다른 숫자를 계산합니다.
         * matched 배열로 이미 사용한 비밀번호의 숫자를 표시하므로,
         * 중복 숫자가 있어도 하나의 비밀번호 숫자를 여러 번 세지 않습니다.
         */
        for (i = 0; i < code_length; i++)
        {
            if (guess[i] != secret[i])
            {
                for (j = 0; j < code_length; j++)
                {
                    if (!matched[j] && guess[i] == secret[j])
                    {
                        correct_number++;
                        matched[j] = 1;
                        digit_colors[i] = 2; /* 노란색: 숫자만 일치 */
                        break;
                    }
                }
            }
        }

        /* 이번 시도의 번호와 힌트를 기록에 추가합니다. */
        for (i = 0; i < code_length; i++)
            current_attempt.guess[i] = guess[i];

        current_attempt.guess[code_length] = '\0';
        current_attempt.correct_position = correct_position;
        current_attempt.correct_number = correct_number;
        history.push_back(current_attempt);

        system("cls");

        printf("===== DIGITAL SECRET VAULT =====\n\n");
        printf("현재 금고 입력 번호\n\n");
        print_digital_vault_code(display, digit_colors, code_length);

        printf("\n색상 힌트: ");
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO info;
            WORD default_color =
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

            if (GetConsoleScreenBufferInfo(console, &info))
                default_color = info.wAttributes;

            SetConsoleTextAttribute(
                console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("초록색");

            SetConsoleTextAttribute(
                console,
                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 노란색");

            SetConsoleTextAttribute(console, default_color);
            printf("\n\n");
        }

        printf("초록색: 숫자와 위치 모두 일치 / 노란색: 숫자만 일치\n");
        printf("\n시도 횟수: %d회\n", attempts);
        printf("숫자와 위치가 모두 일치하는 숫자: %d개\n", correct_position);
        printf("숫자만 일치하는 숫자: %d개\n", correct_number);

        /* 방금 입력한 시도를 포함하여 전체 기록을 표시합니다. */
        printf("\n================ 전체 시도 기록 ================\n");
        printf("회차    입력 번호       위치 일치    숫자 일치\n");
        printf("------------------------------------------------\n");

        for (i = 0; i < (int)history.size(); i++)
        {
            printf("%3d회      %s             %d개          %d개\n",
                   i + 1,
                   history[i].guess,
                   history[i].correct_position,
                   history[i].correct_number);
        }

        printf("================================================\n");

        if (is_correct)
        {
            printf("\n====================================\n");
            printf("          VAULT OPEN!\n");
            printf("====================================\n\n");

            printf("축하합니다! 비밀금고를 열었습니다!\n");
            printf("비밀번호: %s\n", secret);
            printf("총 시도 횟수: %d회\n", attempts);
            break;
        }
        else
        {
            printf("\n비밀번호가 틀렸습니다.\n");
            printf("다시 시도해 주세요.\n");
            wait_seconds(1.0);
        }
    }

    printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
    read_key_press();
}

/* 9번 모드: 입력한 초부터 0초까지 디지털 숫자로 카운트다운합니다. */
void play_timer_mode(void)
{
    int total_seconds;
    int remaining_seconds;
    int hours;
    int minutes;
    int seconds;
    long time_number;
    int ch;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    WORD default_color =
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD timer_color =
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    std::chrono::steady_clock::time_point start_time;

    /* 현재 콘솔의 기본 글자색을 저장합니다. */
    if (GetConsoleScreenBufferInfo(console, &console_info))
        default_color = console_info.wAttributes;

    system("cls");
    printf("===== 디지털 타이머 =====\n\n");
    printf("타이머 시간을 초 단위로 입력하세요. (1~359999초)\n");
    printf("입력 시간은 최대 99시간 59분 59초입니다.\n\n");
    printf("초 입력: ");

    if (scanf("%d", &total_seconds) != 1)
    {
        printf("잘못된 입력입니다. 숫자를 입력해 주세요.\n");
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
        read_key_press();
        return;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }

    if (total_seconds < 1 || total_seconds > 359999)
    {
        printf("\n1초 이상 359999초 이하로 입력해 주세요.\n");
        printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
        read_key_press();
        return;
    }

    /* steady_clock을 사용하여 시스템 시각 변경과 관계없이 시간을 측정합니다. */
    start_time = std::chrono::steady_clock::now();

    for (remaining_seconds = total_seconds;
         remaining_seconds >= 0;
         remaining_seconds--)
    {
        /* 남은 초를 시:분:초 형식으로 변환합니다. */
        hours = remaining_seconds / 3600;
        minutes = (remaining_seconds % 3600) / 60;
        seconds = remaining_seconds % 60;
        time_number = hours * 10000L + minutes * 100L + seconds;

        system("cls");
        printf("===== DIGITAL TIMER =====\n\n");
        printf("남은 시간\n\n");

        set_text_color(timer_color);
        print_digital_time(time_number);
        SetConsoleTextAttribute(console, default_color);

        if (remaining_seconds == 0)
            break;

        /* 매초 일정한 시점을 기준으로 다음 숫자를 표시합니다. */
        std::this_thread::sleep_until(
            start_time + std::chrono::seconds(total_seconds - remaining_seconds + 1));
    }

    system("cls");
    printf("===== DIGITAL TIMER =====\n\n");
    printf("타이머 종료!\n\n");

    set_text_color(timer_color);
    print_digital_time(0);
    SetConsoleTextAttribute(console, default_color);

    /* 카운트다운이 끝나면 종료 알림음을 세 번 재생합니다. */
    Beep(880, 300);
    Beep(988, 300);
    Beep(1047, 600);

    printf("\n타이머가 종료되었습니다.\n");
    printf("\n아무 키나 누르면 메인 메뉴로 돌아갑니다.\n");
    read_key_press();
}

