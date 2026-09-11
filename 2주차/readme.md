# 게임프로그래밍 2주차 수업(0911)

---

## C언어에서 입력 버퍼 비우는 방법

1. getchar(); 를 추가하기
2. fflush(stdin); 추가하기 (gcc는 불가능) 표준 fflush함수는 출력버퍼를 비운다. VC에서는 확장해서 사용하므로 동작하지만 gcc는 안된다.
3. tcflush(0, TCIFLUSH); 추가하기
4. rewind(stdio); 추가하기 rewind함수는 매개변수로 들어온 스트림을 초기화하는데 사용
5. __fpurge(stdin); (리눅스에서만 동작) stdio_ext.h 추가
6. fgets(string, sizeof(string), stdin); 문자열 입력을 scanf가 아니라 fgets로 받는다. 그러나 입력시 사이즈를 오버하면 똑같은 문제가 발생한다.그리고 사이즈를 오버하지 않더라도 문자열 끝에 개행문자가 추가된다.그래서 다음 줄에string[strlen(string)-1] = '\0'; 로 강제로 널문자를 넣어준다.개인적으로 제일 많이 사용하는 방식
7. scanf("%*c", c); %*c는 입력은 받지만 저장은 안한다. 즉 비어있는 \n를 날려버린다.
8. scanf("%c", &c);에서 %c 앞에 공백을 추가하기 : scanf(" %c", &c);
