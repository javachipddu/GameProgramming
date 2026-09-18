# 게임프로그래밍 3주차 수업(0918)

C언어는 파일 단위로 컴파일한다. (정보처리기사)

<img width="628" height="351" alt="image" src="https://github.com/user-attachments/assets/ae50f5cb-3c7a-452e-9612-a68fd309df1f" />

모듈화

<img width="627" height="353" alt="image" src="https://github.com/user-attachments/assets/dbf2dcf5-16e8-44a3-a8d6-cb20fe9dec66" />

<img width="626" height="351" alt="image" src="https://github.com/user-attachments/assets/d5be5448-0d4e-417e-920d-0aa896a974fd" />

<img width="626" height="351" alt="image" src="https://github.com/user-attachments/assets/74526c7a-80c8-4603-8672-20a2e29a826b" />

select=getch()-48; 에서 48을 빼는 이유 : 키보드로 입력한 숫자가 문자(ASCII 코드)로 들어오기 때문이다.

getch()에서 ASCII코드인 49를 반환한다.

입력	ASCII 코드
'0'	48
'1'	49
'2'	50
'3'	51
...	...
'9'	57

select = 49 - 48 = 1

assignment statement

variable = expression
          literal(or constant)  a = 1
          variable              a = b
          operator              a = b + 1
          function              a = sum(1, 2) * 6
          
<img width="626" height="351" alt="image" src="https://github.com/user-attachments/assets/a251db66-9357-4fa4-847d-5230e26af298" />

random

seed 값, rand 함수의 프로토타입

vba(Visual Basic Application)

<img width="622" height="351" alt="image" src="https://github.com/user-attachments/assets/0992077b-eb61-4198-b96b-6d7db8742820" />

<img width="625" height="351" alt="image" src="https://github.com/user-attachments/assets/40f4c126-9072-4615-a6e2-f37149ef5eb6" />

<img width="628" height="349" alt="image" src="https://github.com/user-attachments/assets/88d0f612-f0cf-4e8c-83b8-9d0d7ab1a103" />

<img width="626" height="351" alt="image" src="https://github.com/user-attachments/assets/c5786481-99ab-40aa-8fbb-7224370d9599" />

<img width="624" height="352" alt="image" src="https://github.com/user-attachments/assets/0d966bd5-7d07-44c1-b46e-92c54c7e95fc" />

• 가변 인수를 사용하는 함수의 원형에는 고정적으로 사용할 매개 변수가
최소한 한 개가 있어야 하고, 이후에 콤마와 ...를 함께 정의해야 한다.
• printf와 scanf의 경우에는 고정적으로 사용할 매개 변수는 한 개이고, 이
는 형식 제어 문자열을 정의하는 부분
• 함수 원형에서 ...로 표시되는 가변 인수를 사용하려면 va_list라는 데이터
형을 이용하며 va_list 형은 헤더 파일 <stdarg.h>에 정의되어 있다.
• va_list 형은 가변 인수를 처리하는데 있어서 필요한 정보를 보관할 포인
터 변수를 정의하기 위해 사용

<img width="626" height="714" alt="image" src="https://github.com/user-attachments/assets/78603db5-2dca-4159-aa78-9bf551c69f80" />

<img width="625" height="708" alt="image" src="https://github.com/user-attachments/assets/abc0e2dd-a279-4630-b980-1d728062cfda" />

<img width="623" height="353" alt="image" src="https://github.com/user-attachments/assets/c921ccc6-9d32-41d4-8e4b-59448dec24e0" />


♠ 자체 → 2바이트
문자열 종료 표시 '\0' → 1바이트
────────────────────
총 3바이트
