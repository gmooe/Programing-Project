#include "LightBot.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

void dataManage(stage* stageinf, player* playerinf)
{
	int stageWNB = 5;   // 스테이지의 총 개수
	for (int rpt = 0; rpt < stageWNB; rpt++)
	{
		stageinf[rpt].num = rpt;
		stageinf[rpt].row = 8;
		stageinf[rpt].col = 8;
		stageinf[rpt].startP = 0;
		stageinf[rpt].field = (int*)calloc(stageinf[rpt].row * stageinf[rpt].col, sizeof(int));
		stageinf[rpt].lightfld = (int*)calloc(stageinf[rpt].row * stageinf[rpt].col, sizeof(int));
	}
	for (int rpt = 0; rpt < stageWNB; rpt++)
	{
		playerinf[rpt].player = 0;
		playerinf[rpt].drct = 1;
		playerinf[rpt].high = 0;
	}
	stageinf[0].startP = 8 * 3 + 2; stgeditor(&stageinf[0], &playerinf[0], 2, "53", 1);// stage 1  
	stageinf[1].startP = 8 * 3 + 1; stgeditor(&stageinf[1], &playerinf[1], 1, "3031323334353637", 1); stgeditor(&stageinf[1], &playerinf[1], 2, "5354", 0); // stage 2
	stageinf[2].startP = 8 * 3 + 1; stgeditor(&stageinf[2], &playerinf[2], 1, "10121416313335375052545671737577", 2); stgeditor(&stageinf[2], &playerinf[2], 2, "53", 0); // stage 3
	stageinf[3].startP = 8 * 4 + 1; stgeditor(&stageinf[3], &playerinf[3], 1, "24", 1); stgeditor(&stageinf[3], &playerinf[3], 1, "23", 2); stgeditor(&stageinf[3], &playerinf[3], 1, "33", 3);
	stgeditor(&stageinf[3], &playerinf[3], 1, "43", 4); stgeditor(&stageinf[3], &playerinf[3], 1, "5363646566", 5); stgeditor(&stageinf[3], &playerinf[3], 2, "646566", 0); // stage 4
	stageinf[4].startP = 8 * 7 + 0; stgeditor(&stageinf[4], &playerinf[4], 1, "2021222324252627505152535455565702122232425262720515253545556575", 1);
	stgeditor(&stageinf[4], &playerinf[4], 2, "22522555", 0); // stage 5
}

void starttext()
{
	printf("Light Bot 게임에 오신것을 환영합니다!");
	Sleep(2000);
	system("cls");
	printf("게임을 시작하려면 아무 입력을 눌러주세요.");
	getchar();
	while (getchar() != '\n') {}
}

int LightbotPlay(stage* counts, player* countp, char* fncBuf1, char* fncBuf2, int stageWNB, int* life)
{
	while (1)
	{
		countp->player = counts->startP;  // 다시 시작할 경우 초기 세팅값 리셋
		countp->drct = 1;               // 다시 시작할 경우 초기 세팅값 리셋
		int success = 1;
		int idx = 0;
		char buf[13];    // 사용자 행동 입력 버퍼
		system("cls");
		printfield(counts, countp);
		printf("\n\n");
		printf("              < stage %d >\n\n", counts->num + 1);
		printf("행동을 순서대로 입력해주세요! (최대 입력 개수: 12개)\n( 1. 방향으로 한 칸 이동 | 2. 왼쪽으로 회전 | 3. 오른쪽으로 회전 | 4. 방향으로 점프 | 5. 불 켜기 )\n");
		printf("( 6. function1 | 7. function2 | 8. function 입력 또는 사용하는 방법 출력! ( 8번 단일 입력 시 작동) | 9번 랜덤 위치 이동!  )\n");
		printf(".. 현재 f1의 기능: %s\n", fncBuf1);
		printf(".. 현재 f2의 기능: %s\n", fncBuf2);
		printf(".. Life: %d\n", *life);

		fgets(buf, 13, stdin);
		buf[strcspn(buf, "\n")] = '\0'; // \n을 \0으로 치환
		if (strlen(buf) == 12) // 만약 입력이 buf의 길이를 넘어서 \n이 저장이 안되었다면 입력 버퍼 비우기
		{
			while (getchar() != '\n') {}
		}
		if (specialinput(buf, fncBuf1, fncBuf2))
		{
			continue;
		}
		else
		{
			action(counts, countp, buf, fncBuf1, fncBuf2, &idx);
		}
		for (int si = 0; si < counts->col * counts->row; si++)
		{
			if (counts->lightfld[si] == 1)
			{
				success = 0;
			}
		}
		if (success)
		{
			if (stageWNB == 1 + counts->num)
			{
				break;
			}
			printf("\n\n\n");
			printf("               스테이지 %d 클리어!\n", counts->num + 1);
			printf("( 다음 스테이지로 넘어가려면 아무 입력이나 눌러주세요 ) \n");
			getchar();
			while (getchar() != '\n') {}
			counts = counts + 1;
			countp = countp + 1;
		}
		else
		{
			*life = *life - 1;
			if (!(*life)) // 생명이 0이 되면
			{
				break;
			}
			printf("\n\n\n");
			printf("( 다시 플레이 하려면 아무 입력이나 눌러주세요 ) \n");
			getchar();
			while (getchar() != '\n') {}
		}
	}
	if (*life)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void endtext(stage* counts, int result, int* life)
{
	if (result)
	{
		system("cls");
		printf("게임의 모든 스테이지를 클리어 하였습니다!\n\n");
		printf("- 클리어한 스테이지: %d개\n", counts->num + 1);
		printf("- 남은 생명: %d\n", *life);
	}
	else
	{
		system("cls");
		printf("--GAME OVER--\n\n");
		printf("클리어한 스테이지: %d개\n\n", counts->num);
		printf("게임을 종료하려면 아무 입력이나 눌러주세요.");
		getchar();
	}
	return 0;
}
void stgeditor(stage* counts, player* countp, char move, char* coor, int n) // move == 동작 번호, coor == 좌표 (인덱스 짝수 = x, 홀수 = y)  n은 몇 개만큼
{
	char x, y;
	char* read = coor;
	if (move == 1) // 높이 n 추가 
	{
		while (*read != '\0')
		{
			x = *read - '0';  // '0'을 빼서 정수 만들기
			y = *(read + 1) - '0';
			counts->field[y * counts->row + x] = counts->field[y * counts->row + x] + n; // n만큼 필드의 높이 추가
			read = read + 2;
		}
	}
	else if (move == 2) // 라이트 필드 추가 
	{
		while (*read != '\0')
		{
			x = *read - '0';  // '0'을 빼서 정수 만들기
			y = *(read + 1) - '0';
			counts->lightfld[y * counts->row + x]++;
			read = read + 2;
		}
	}
	return;
}
int specialinput(char* buf, char* fbuf1, char* fbuf2)
{
	char* read = buf;
	if (strlen(buf) == 1 && *read == '8') // 8 하나만 입력받았으면 함수 입력 or 설명서
	{
		char sInpChar;
		printf("( 1. function1 | 2. function2 | 3. function 사용법! )\n");
		sInpChar = getchar();
		while (getchar() != '\n') {}
		if (sInpChar == '1')
		{
			printf("function1의 기능을 순서대로 입력해주세요! (최대 입력 개수: 12개)\n");
			fgets(fbuf1, 13, stdin);
			fbuf1[strcspn(fbuf1, "\n")] = '\0';
			if (strlen(buf) == 12) // 만약 입력이 buf의 길이를 넘어서 \n이 저장이 안되었다면 입력 버퍼 비우기
			{
				while (getchar() != '\n') {}
			}
		}
		else if (sInpChar == '2')
		{
			printf("function2의 기능을 순서대로 입력해주세요! (최대 입력 개수: 12개)\n");
			fgets(fbuf2, 13, stdin);
			fbuf2[strcspn(fbuf2, "\n")] = '\0';
			if (strlen(buf) == 12) // 만약 입력이 buf의 길이를 넘어서 \n이 저장이 안되었다면 입력 버퍼 비우기
			{
				while (getchar() != '\n') {}
			}
		}
		else if (sInpChar == '3')
		{
			printf("\n");
			printf("함수 사용법 설명서..\n\n");
			printf(".. 8번을 단일 입력 후 원하는 함수의 번호를 입력하면 함수의 기능을 입력할 수 있는 버퍼가 나옵니다.\n");
			printf(".. 버퍼에 여려 행동들을 저장한 후 Enter를 누르면 저장할 수 있습니다.\n\n");
			printf("입력은 여러번 할 수 있습니다! 자유롭게 사용하세요!\n");
			getchar();
			while (getchar() != '\n') {}
		}
		else
		{
			return 1;  // 1을 반환 == action 함수가 동작하지 않음
		}
		return 1;
	}
	else
	{
		return 0;      // 0을 반환 == action 함수가 동작함
	}
}
void printfield(stage* counts, player* countp)
{
	char Aprance[3] = { ' ', '+', '*' }; // 라이트 필드의 생김새를 저장
	int rpt; // 반복제어변수
	for (rpt = 0; rpt < counts->row * counts->col; rpt++)
	{
		if (countp->printplayer == '*')
		{ // 실행함수에서 이미 문자를 저장받아왔기에 아무 실행도 하지 않음.
		}
		else if (countp->drct == 1)
		{
			countp->printplayer = '>';
		}
		else if (countp->drct == counts->row)
		{
			countp->printplayer = 'v';
		}
		else if (countp->drct == -1)
		{
			countp->printplayer = '<';
		}
		else if (countp->drct == -counts->row)
		{
			countp->printplayer = '^';
		}
		// 출력 시작 //
		if (rpt % counts->row == 0 && rpt >= counts->row) // rpt가 row(가로의 개수)의 배수이고, 가로의 개수 보다 크거나 같을 때( 0 에서의 작동 방지 )만 줄 넘기기
		{
			printf("\n\n");
		}
		if (rpt == countp->player && counts->lightfld[rpt]) // 출력해야되는 좌표가 플레이어의 좌표이고 동시에 라이트 필드라면,
		{
			printf(" %c%c%c ", Aprance[counts->lightfld[rpt]], countp->printplayer, Aprance[counts->lightfld[rpt]]);
		}
		else if (rpt == countp->player) // 출력해야되는 순서가 플레이어의 좌표라면
		{
			printf(" %c%c%c ", Aprance[counts->lightfld[rpt]], countp->printplayer, Aprance[counts->lightfld[rpt]]);
		}
		else if (counts->lightfld[rpt])  // 출력해야되는 순서의 필드가 라이트 필드라면
		{
			printf(" %c%d%c ", Aprance[counts->lightfld[rpt]], counts->field[rpt], Aprance[counts->lightfld[rpt]]);
		}
		else // 아무것도 아니라면
		{
			printf(" %c%d%c ", Aprance[counts->lightfld[rpt]], counts->field[rpt], Aprance[counts->lightfld[rpt]]);
		}
		if (countp->printplayer == '*' && rpt > countp->player) // 만약 외부에서 저장한 문자를 출력했을 경우 printplayer를 방향표시로 변환.
		{
			if (countp->drct == 1)
			{
				countp->printplayer = '>';
			}
			else if (countp->drct == counts->row)
			{
				countp->printplayer = 'v';
			}
			else if (countp->drct == -1)
			{
				countp->printplayer = '<';
			}
			else if (countp->drct == -counts->row)
			{
				countp->printplayer = '^';
			}
		}
	}
	return;
}
void action(stage* counts, player* playerinf, char* buf, char* fbuf1, char* fbuf2, int* idx)
{
	srand(time(NULL));
	int randcoor;
	int drctIdx[4] = { 1, counts->row, -1, -counts->row };  // 방향을 배열에 저장
	char* read = buf;
	char inpAlT;  // 상시 입력을 위한 변수
	char Sleepctr = 1;  // Sleep 함수를 제어하기 위한 변수
	while (*read != '\0')
	{
		switch (*read)
		{
		case '1': // 방향을 따라서 한 칸 움직이기
			if (counts->field + playerinf->player + playerinf->drct < counts->field || counts->field + playerinf->player + playerinf->drct > counts->field + counts->row * counts->col - 1 || (playerinf->drct == 1 && (playerinf->player + 1) % counts->row == 0) || (playerinf->drct == -1 && playerinf->player % counts->row == 0)) // 방향이 필드 밖을 향한다면
			{ // 아무것도 안하기
			}
			else if (*(counts->field + playerinf->player + playerinf->drct) != playerinf->high) // 플레이어의 방향이 높이가 다른 칸을 향한다면
			{ // 아무것도 안하기
			}
			else
			{
				playerinf->player = playerinf->player + playerinf->drct; // 플레이어가 향한 방향으로 한 칸 이동
			}
			break;
		case '2': // 왼쪽으로 회전
			*idx = (*idx + 3) % 4;
			playerinf->drct = drctIdx[*idx];
			break;
		case '3':  // 오른쪽으로 회전
			*idx = (*idx + 1) % 4;
			playerinf->drct = drctIdx[*idx];
			break;
		case '4':  // jump
			if (*(counts->field + playerinf->player + playerinf->drct) == playerinf->high + 1) // 만약 앞 칸의 높이가 1 높다면 그 곳으로 점프
			{
				playerinf->player = playerinf->player + playerinf->drct;
				playerinf->high = playerinf->high + 1;
			}
			else if (*(counts->field + playerinf->player + playerinf->drct) < playerinf->high) // 만약 앞 칸의 높이가 플레이어 높이보다 낮다면 그 곳으로 점프
			{
				playerinf->player = playerinf->player + playerinf->drct;
				playerinf->high = *(counts->field + playerinf->player + playerinf->drct);
			}
			else // 높이가 플레이어보다 두 칸 이상 높다면
			{// 아무것도 안하기
			}
			break;
		case '5': // 불켜기
			playerinf->printplayer = '*';
			if (counts->lightfld[playerinf->player] == 1)  // 만약 플레이어의 좌표가 라이트 필드에 있다면
			{
				counts->lightfld[playerinf->player] = 2;
			}
			else if (counts->lightfld[playerinf->player] == 2) // 만약 라이트 필드의 불이 켜져 있다면
			{
				counts->lightfld[playerinf->player] = 1;   // 불끄기
			}
			break;
		case '6':
			action(counts, playerinf, fbuf1, fbuf1, fbuf2, idx);  // action 함수의 버퍼 매개변수 자리에 function1의 버퍼를 주고 호출하기
			read++;
			continue;
		case '7':
			action(counts, playerinf, fbuf2, fbuf1, fbuf2, idx);  // action 함수의 버퍼 매개변수 자리에 function2의 버퍼를 주고 호출하기
			read++;
			continue;
		case '9':
			randcoor = rand() % counts->col * counts->row;
			playerinf->player = randcoor;
			break;
		}
		system("cls");
		printfield(counts, playerinf);
		printf(" (행동: %c)\n\n(멈추기: p | 빨리감기: f)\n", *read);
		if (Sleepctr)
		{
			Sleep(1000);
		}
		if (_kbhit())
		{
			inpAlT = _getch();
			if (inpAlT == 'p') // 만약 실행 도중 p를 누르면 멈추기
			{
				break;
			}
			else if (inpAlT == 'f') // 만약 실행 도중 f를 누르면 제어변수를 0으로 바꾸기
			{
				Sleepctr = 0;
			}
		}
		read++;
	}
}