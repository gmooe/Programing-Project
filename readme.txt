#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"LightBot.h"
int main()
{
	
	int player = 0;  // 플레이어 좌표
	int drct = 1;    // 플레이어 방향
	int row = 5;     // 행 길이
	int col = 5;     // 열 길이
	int field[5][5] = { 0 };  // 필드 구성
	char buf[16];    // 사용자 행동 입력 버퍼
	int i;
	for (i = 0; i < row * col; i++)  // 필드 출력
	{
		if (i % row == 0 && i >= 5)
		{
			printf("\n\n");
		}
		if (i == player)
		{
			printf("*\t");
		}
		else
		{
			printf("0\t");
		}
	}
	printf("\n");
	scanf("%s", buf);
	printf("\n\n\n\n");
	char* read = NULL;
	read = buf;
	while (*read != '\0')
	{
		switch (*read)  // 입력 받은 후 움직임 구현
		{
		case '1': // move 1 block;
			player = player + drct;
			break;
		case '2': // turn of the left
			break;
		}
		read++;
	}
	for (i = 0; i < row * col; i++) 움직인 후 출력
	{
		if (i % row == 0 && i >= 5)
		{
			printf("\n\n");
		}
		if (i == player)
		{
			printf("*\t");
		}
		else
		{
			printf("0\t");
		}
	}
}
