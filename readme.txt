<<<<<<< HEAD
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"LightBot.h"
#define PI 3.141592653589793
typedef struct {
	int row; // 행 길이
	int col; // 열 길이
	int* field; // 필드 구성. 각 칸에 저장되는 숫자는 그 칸의 높이를 뜻함
	int* LightBlock;  // 플레이어가 불을 밝혀야 될 블록의 좌표
}stage;

void printfield(int row, int col, int player, int drct, char printdrct, int high, int* field);
int main()
{
	int row = 5;     // 행 길이
	int col = 5;     // 열 길이
	int *field = (int*)calloc(row*col, sizeof(int));  // 필드 구성. 각 칸에 저장되는 숫자는 그 칸의 높이를 뜻함
	double x = 0; //  방향(drct)을 결정짓는 매개변수
	int player = 0;  // 플레이어 좌표
	char printdrct = '>';// 플레이어의 방향을 출력할 때 사용할 문자  
	int drct = ((double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5);    // 플레이어 방향
	int high = 0;    // 플레이어 높이
	char buf[13];    // 사용자 행동 입력 버퍼
	//printf("%d, %f\n", drct, x);
	printfield(row, col, player, drct, printdrct, high, field);
	printf("\n");
	scanf("%s", buf);
	printf("\n\n\n\n");
	char* read = NULL;  // 버퍼를 읽을 때 사용할 포인터
	read = buf;
	while (*read != '\0')
	{
		switch (*read)
		{
		case '1': // move 1 block;
			if (field + player + drct < field || field + player + drct > field + row * col - 1 || (drct == 1 && (player+1)%row == 0) || (drct == -1 && player % row == 0)) // 방향이 필드 밖을 향한다면
			{ // 아무것도 안하기
			}
			else if (*(field + player + drct) != high) // 플레이어의 방향이 높이가 다른 칸을 향한다면
			{ // 아무것도 안하기
			}
			else
			{
				player = player + drct; // 플레이어가 향한 방향으로 한 칸 이동
			}
			break;
		case '2': // 왼쪽으로 회전
			x = x - PI / 2.0; 
			drct = (double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5;
			if (drct == 1)
			{
				printdrct = '>';
			}
			else if (drct == col)
			{
				printdrct = 'v';
			}
			else if (drct == -1)
			{
				printdrct = '<';
			}
			else
			{
				printdrct = '^';
			}
			break;
		case '3':  // 오른쪽으로 회전
			x = x + PI / 2.0;
			drct = (double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5;
			if (drct == 1)
			{
				printdrct = '>';
			}
			else if (drct == col)
			{
				printdrct = 'v';
			}
			else if (drct == -1)
			{
				printdrct = '<';
			}
			else
			{
				printdrct = '^';
			}
			break;
		case '4':  // jump
			if (*(field + player + drct) == high + 1) // 만약 앞 칸의 높이가 1 높다면 그 곳으로 점프
			{
				player = player + drct;
				high = high + 1;
			}
			else if(*(field + player + drct) > high) // 만약 앞 칸의 높이가 플레이어 높이보다 낮다면 그 곳으로 점프
			{
				player = player + drct;
				high = *(field + player + drct);
			}
			break;
		case '5': // 불켜기
			break;
		}
		printf("%d, %f, %f\n", drct, x, (double)col * sin(x) + cos(x) + sin(x) * 0.5 + cos(x) * 0.5);
		read++;
	}
	printfield(row, col, player, drct, printdrct, high, field);
	return 0;
}
void printfield(int row, int col, int player, int drct, char printdrct, int high, int* field)
{
	int i;
	for (i = 0; i < row * col; i++)
	{
		if (i % row == 0 && i >= row) // i가 row(가로의 개수)의 배수이고, 가로의 개수 보다 크거나 같을 때만 줄 넘기기( 0 에서의 작동 방지 )
		{
			printf("\n\n");
		}
		if (i == player)  // 플레이어의 좌표에 출력
		{
			printf(" %c%c%c ", ' ',printdrct, ' ');
		}
		else
		{
			printf(" %c%d%c ", ' ', *(field+ i), ' ');
		}
	}
	return;
}
=======
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"LightBot.h"
#define PI 3.141592653589793
typedef struct {
	int row; // 행 길이
	int col; // 열 길이
	int* field; // 필드 구성. 각 칸에 저장되는 숫자는 그 칸의 높이를 뜻함
	int* LightBlock;  // 플레이어가 불을 밝혀야 될 블록의 좌표
}stage;

void printfield(int row, int col, int player, int drct, char printdrct, int high, int* field);
int main()
{
	int row = 5;     // 행 길이
	int col = 5;     // 열 길이
	int *field = (int*)calloc(row*col, sizeof(int));  // 필드 구성. 각 칸에 저장되는 숫자는 그 칸의 높이를 뜻함
	double x = 0; //  방향(drct)을 결정짓는 매개변수
	int player = 0;  // 플레이어 좌표
	char printdrct = '>';// 플레이어의 방향을 출력할 때 사용할 문자  
	int drct = ((double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5);    // 플레이어 방향
	int high = 0;    // 플레이어 높이
	char buf[13];    // 사용자 행동 입력 버퍼
	//printf("%d, %f\n", drct, x);
	printfield(row, col, player, drct, printdrct, high, field);
	printf("\n");
	scanf("%s", buf);
	printf("\n\n\n\n");
	char* read = NULL;  // 버퍼를 읽을 때 사용할 포인터
	read = buf;
	while (*read != '\0')
	{
		switch (*read)
		{
		case '1': // move 1 block;
			if (field + player + drct < field || field + player + drct > field + row * col - 1 || (drct == 1 && (player+1)%row == 0) || (drct == -1 && player % row == 0)) // 방향이 필드 밖을 향한다면
			{ // 아무것도 안하기
			}
			else if (*(field + player + drct) != high) // 플레이어의 방향이 높이가 다른 칸을 향한다면
			{ // 아무것도 안하기
			}
			else
			{
				player = player + drct; // 플레이어가 향한 방향으로 한 칸 이동
			}
			break;
		case '2': // 왼쪽으로 회전
			x = x - PI / 2.0; 
			drct = (double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5;
			if (drct == 1)
			{
				printdrct = '>';
			}
			else if (drct == col)
			{
				printdrct = 'v';
			}
			else if (drct == -1)
			{
				printdrct = '<';
			}
			else
			{
				printdrct = '^';
			}
			break;
		case '3':  // 오른쪽으로 회전
			x = x + PI / 2.0;
			drct = (double)col * sin(x) + cos(x) + sin(x)* 0.5 + cos(x) * 0.5;
			if (drct == 1)
			{
				printdrct = '>';
			}
			else if (drct == col)
			{
				printdrct = 'v';
			}
			else if (drct == -1)
			{
				printdrct = '<';
			}
			else
			{
				printdrct = '^';
			}
			break;
		case '4':  // jump
			if (*(field + player + drct) == high + 1) // 만약 앞 칸의 높이가 1 높다면 그 곳으로 점프
			{
				player = player + drct;
				high = high + 1;
			}
			else if(*(field + player + drct) > high) // 만약 앞 칸의 높이가 플레이어 높이보다 낮다면 그 곳으로 점프
			{
				player = player + drct;
				high = *(field + player + drct);
			}
			break;
		case '5': // 불켜기
			break;
		}
		printf("%d, %f, %f\n", drct, x, (double)col * sin(x) + cos(x) + sin(x) * 0.5 + cos(x) * 0.5);
		read++;
	}
	printfield(row, col, player, drct, printdrct, high, field);
	return 0;
}
void printfield(int row, int col, int player, int drct, char printdrct, int high, int* field)
{
	int i;
	for (i = 0; i < row * col; i++)
	{
		if (i % row == 0 && i >= row) // i가 row(가로의 개수)의 배수이고, 가로의 개수 보다 크거나 같을 때만 줄 넘기기( 0 에서의 작동 방지 )
		{
			printf("\n\n");
		}
		if (i == player)  // 플레이어의 좌표에 출력
		{
			printf(" %c%c%c ", ' ',printdrct, ' ');
		}
		else
		{
			printf(" %c%d%c ", ' ', *(field+ i), ' ');
		}
	}
	return;
}
>>>>>>> 70bf8d0747a696f4ecc9b9edd12092dd15eb16c7
