#include"LightBot.h"

int main()
{
	int stageWNB = 5; // 스테이지의 총 개수
	stage* stageinf = (stage*)malloc(sizeof(stage) * stageWNB);
	player* playerinf = (player*)malloc(sizeof(player) * stageWNB);
	dataManage(stageinf, playerinf);
	stage* counts = stageinf;  // 플레이어의 진행중인 스테이지를 저장
	player* countp = playerinf;
	int life = 5; // 플레이어의 시도 가능한 횟수.
	int idx = 0;  // 방향의 인덱스를 세기 위한 변수
	char fncBuf1[13] = {'\0'};// 함수 버퍼
	char fncBuf2[13] = { '\0' };
	starttext();
	if (LightbotPlay(counts, countp, fncBuf1, fncBuf2, stageWNB, &life))
	{
		endtext(counts, 1, &life);
	}
	else
	{
		endtext(counts, 0, &life);
	}
	return 0;
}

