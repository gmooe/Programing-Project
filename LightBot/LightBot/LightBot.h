typedef struct {
	int num; // 스테이지 넘버
	int row; // 행 길이
	int col; // 열 길이
	int startP; // 플레이어 시작좌표
	int* field; // 필드 구성. 각 칸에 저장되는 숫자는 그 칸의 높이를 뜻함
	int* lightfld;  // 동적할당을 받은 후 플레이어가 불을 밝혀야 될 필드의 좌표에 1을 저장함. 불이 켜진 상태는 2.
}stage;
typedef struct {
	int player;  // 플레이어 좌표
	int drct; // 현재 플레이어의 방향을 저장
	int high;    // 플레이어 높이
	char printplayer;// 출력되는 플레이어의 모습 저장
}player;

void stgeditor(stage* counts, player* countp, char move, char* coor, int n);  // 스테이지 제작에 사용하는 함수
int specialinput(char* buf, char* fbuf1, char* fbuf2);  // 행동에는 포함되지 않는 입력을 받는 함수
void action(stage* counts, player* countp, char* buf, char* fbuf1, char* fbuf2, int* idx);  // 행동에 포함되는 입력을 받는 함수
void printfield(stage* counts, player* countp);  // 필드 전체를 출력하는 함수
void dataManage(stage* stageinf, player* playerinf);
void starttext();
int LightbotPlay(stage* counts, player* countp, char* fncBuf1, char* fncBuf2, int stageWNB, int* life);
void endtext(stage* counts, int result, int* life);