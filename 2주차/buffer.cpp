#include <stdio.h>

int main(){
	char string[20];
	char c;
	
	scanf("%s", string);
    scanf(" %c", &c);	//%c 앞에 공백을 추가하여 white space를 구분자로 인식 
    
    printf("%s\n", string);
    printf("!!%c!!\n", c);
    
    return 0;
}
