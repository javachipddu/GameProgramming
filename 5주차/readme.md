# 게임프로그래밍 5주차 수업(1016)

<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/e33a2473-5be4-4237-b56d-72314a775deb" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/7615051d-719a-414a-9c1d-5f8fd84eed06" />
화면에 출력할 땐 문자열로 바꿔서 출력한다.
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/fbabf12b-186a-484b-9de8-b7dcb2ca1002" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/9a6f915b-c60b-4bd9-9e78-672b83b0a071" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/c480dfa5-e7d7-4571-af52-0cb44a1f868d" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/6fb442bc-ea3d-4a35-b91a-71230e375e15" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/e21e114c-f03c-4173-92dc-7a4da61e576a" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/4b8e2cbb-be75-441b-b41f-483e6914a031" />

## 꼬리재귀(Tail Recursion)

꼬리재귀는 재귀 함수가 자기 자신을 호출한 뒤, 그 결과를 추가로 계산하지 않고 바로 반환하는 재귀 방식이다.

쉽게 말하면, 재귀 호출이 함수의 마지막 작업인 경우이다.

### 1. 일반 재귀 vs. 꼬리재귀

예를 들어 팩토리얼 $n!$을 계산해 보자.

일반 재귀

python
```
def factorial(n):
    if n == 1:
        return 1
    return n * factorial(n - 1)
```

`factorial(n - 1)`이 반환된 후에 `n`과 곱셈을 수행해야 한다. 따라서 재귀 호출이 끝난 뒤에도 할 일이 남아 있다.

꼬리재귀

python
```
def factorial(n, acc=1):
    if n == 1:
        return acc
    return factorial(n - 1, n * acc)
```

여기서는 `n * acc`를 재귀 호출의 인자로 미리 계산하고, 재귀 호출의 결과를 그대로 반환한다.

### 2. 실행 과정 비교

$factorial(4)$를 계산한다고 가정하면 다음과 같다.

일반 재귀:

호출이 끝난 후 계산이 남음

4 × factorial(3)

3 × factorial(2)

2 × factorial(1)

1

반환하면서 곱셈 수행: 1 → 2 → 6 → 24

꼬리재귀:

누적 변수에 결과를 미리 저장

factorial(4, 1)

factorial(3, 4)

factorial(2, 12)

factorial(1, 24)

최종 결과: 24

### 3. 꼬리재귀의 장점

- 메모리 사용량 감소 가능: 컴파일러나 런타임이 꼬리 호출 최적화(TCO)를 지원하면 재귀 호출마다 스택 프레임을 쌓지 않을 수 있다.
- 반복문으로 변환하기 쉬움: 누적 변수를 활용하면 반복문과 유사한 구조로 구현할 수 있다.
- 재귀 호출의 결과를 후처리하지 않음: 함수의 흐름을 이해하고 최적화하기 쉬워진다.

단, 꼬리재귀라고 해서 항상 메모리를 적게 사용하는 것은 아니다. 예를 들어 Python은 일반적으로 꼬리 호출 최적화를 수행하지 않으므로, 위 코드도 재귀 깊이가 깊으면 `RecursionError`가 발생할 수 있다.

### 4. 핵심 차이 한눈에 보기

| 구분 | 일반 재귀 | 꼬리재귀 |
| --- | --- | --- |
| 재귀 호출 이후 추가 연산 | 있음 | 없음 |
| 대표 형태 | `return n * f(n-1)` | `return f(n-1, acc*n)` |
| 누적 변수 | 보통 불필요 | 자주 사용 |
| 꼬리 호출 최적화 | 적용하기 어려움 | 적용 가능 |

핵심 암기 포인트: `return n * factorial(n-1)`은 재귀 호출 뒤에 곱셈이 남아 있어 일반 재귀이고, `return factorial(n-1, n*acc)`는 호출 결과를 그대로 반환하므로 꼬리재귀이다.

<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/9c76d70c-37f5-4601-83c7-f08d683565bc" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/63c1d77c-4cdf-492d-aa95-6da9674e6d48" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/9afe30ac-4980-4111-b420-b3a199397a23" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/921c245b-ff60-4daa-91e4-33d2a396c693" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/0120e9cc-7bc9-4c7a-a986-5eaabeee7ae8" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/85a5e7e0-06d9-48e7-b1a0-11e134598f51" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/fc032cca-0f24-4720-a2a6-011f01ce2085" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/c12a60ff-a501-4dd4-ae77-13648d02c7c1" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/13ce3ac0-361b-4641-b04a-8c60b259354a" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/83921d6e-e95e-4c94-aff5-1388eea61650" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/77e66ca2-e708-47bd-9134-4ace34b6fca6" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/1964a64f-0386-4002-8968-55c6c083c7cd" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/d91546ca-aa4b-4db1-b4e3-27527fa03e58" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/905121f6-20f2-4909-925f-98ad8d075702" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/0c04fae6-38b6-421d-a98c-1def2f66e915" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/9df85a62-a4cd-461f-aa05-30908256088b" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/d80fca1e-bbd0-45fc-8941-cfc5bc8fc111" />
<img width="837" height="509" alt="image" src="https://github.com/user-attachments/assets/973d2849-e530-43c5-aa33-7f3156da20c2" />
