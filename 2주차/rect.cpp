#include <stdio.h>
void draw_square(int size);
int main(void)
{
	int n;
	printf("정사각형그리기\n\n");
	printf("정사각형의길이(최대37)를\n");
	printf("입력하고Enter>");
	
	scanf("%d", &n);
	
	if (n < 1 || n > 37)
    {
        printf("1부터 37까지 입력하세요.\n");
        return 1;
    }
    
	draw_square(n);
	
	return 0;
}
void draw_square(int size)
{
	int i, j;
	
	unsigned char a=0xa6;
	unsigned char b[7]; 
	for(i=1;i<7;i++)
		b[i]=0xa0+i;
		
	printf("%c%c",a, b[3]);
for(i=0;i<size;i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	for(i=0;i<size;i++)
	{
	printf("%c%c", a, b[2]);
	for(j=0;j<size;j++)
		printf(" ");	//디버깅: 공백이 2칸이라 가로로 두 배 긴 공간이 생겼었음 
	printf("%c%c",a, b[2]);
	printf("\n");
	}
	printf("%c%c", a, b[6]);
	for(i=0;i<size;i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}

