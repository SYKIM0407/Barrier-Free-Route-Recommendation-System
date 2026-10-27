#include <stdio.h>

#define ROWS 16
#define COLS 16
#define INF 99999

typedef struct {
    int areaMap[ROWS][COLS];
    int dangerMap[ROWS][COLS];      // 위험도 등급
    int slopeMap[ROWS][COLS];       // 경사도 등급
    int obstacleMap[ROWS][COLS];    // 장애물 등급
    int widthMap[ROWS][COLS];       // 폭 등급
    int statusMap[ROWS][COLS];       // 통제 반영
} RouteMap;

typedef struct {
    int row;
    int col;
} Position;

/* ---------- 기본 함수 ---------- */

void printAreaName(int id) {
    switch(id) {
        case 1: printf("혜화역 4번출구"); break;
        case 2: printf("혜화역 4번출구에서 올사 방향 골목"); break;
        case 3: printf("올사"); break;
        case 4: printf("혜화역 4번출구에서 혜화동 로터리 방향 길"); break;
        case 5: printf("혜화동 로터리"); break;
        case 6: printf("혜화동 로터리에서 올사 방향 길"); break;
        case 7: printf("성균관대 정문 옆 샛길"); break;
        case 8: printf("성균관대 정문 앞 큰길"); break;
        case 9: printf("성균관대 정문"); break;
        case 10: printf("명륜당 앞"); break;
        case 11: printf("명륜당 언덕길"); break;
        case 12: printf("국제관 옆 오르막길"); break;
        case 13: printf("학생회관 옆 오르막길"); break;
        case 14: printf("금잔디 광장"); break;
        case 15: printf("혜화동 로터리에서 혜화로 방향 길"); break;
        case 16: printf("혜화로 횡단보도"); break;
        case 17: printf("혜화초 부근"); break;
        case 18: printf("혜화초 앞 로터리"); break;
        case 19: printf("혜화초 로터리에서 새마을금고 방향 길"); break;
        case 20: printf("명륜 새마을금고 앞"); break;
        case 21: printf("성균관대 정문에서 새마을금고 방향 길"); break;
        case 22: printf("쪽문 새마을금고 앞 골목"); break;
        case 23: printf("쪽문 엘리베이터 방향 오르막길"); break;
        case 24: printf("쪽문 엘리베이터"); break;
        case 25: printf("경영관 입구"); break;
        default: printf("갈 수 없는 길"); break;
    }
}

/* ---------- 구역 간 안내멘트 ---------- */

const char* getRouteDirection(int fromId, int toId) {
    if(fromId == 1 && toId == 2) return "올사 방향 골목으로";
    if(fromId == 1 && toId == 4) return "혜화동 로터리 방향으로";

    if(fromId == 2 && toId == 1) return "혜화역 4번출구 방향으로";
    if(fromId == 2 && toId == 3) return "올사 앞으로";

    if(fromId == 3 && toId == 2) return "혜화역 방향 골목으로";
    if(fromId == 3 && toId == 6) return "혜화동 로터리 방향으로";
    if(fromId == 3 && toId == 7) return "올리브영 왼쪽 샛길 방향으로";
    if(fromId == 3 && toId == 8) return "올리브영 오른쪽 큰길 방향으로";

    if(fromId == 4 && toId == 1) return "혜화역 4번출구 방향으로";
    if(fromId == 4 && toId == 5) return "혜화동 로터리 방향으로";

    if(fromId == 5 && toId == 4) return "혜화역 방향으로";
    if(fromId == 5 && toId == 6) return "올사 방향으로";
    if(fromId == 5 && toId == 15) return "혜화로(우체국 골목) 방향으로";

    if(fromId == 6 && toId == 3) return "올사 방향으로";
    if(fromId == 6 && toId == 5) return "혜화동 로터리 방향으로";

    if(fromId == 7 && toId == 3) return "올사 방향으로";
    if(fromId == 7 && toId == 10) return "성균관대 명륜당 방향으로";

    if(fromId == 8 && toId == 3) return "올사 방향으로";
    if(fromId == 8 && toId == 9) return "성균관대 정문 방향으로";

    if(fromId == 9 && toId == 8) return "정문 앞 큰길 방향으로";
    if(fromId == 9 && toId == 10) return "성균관대 명륜당 방향으로";
    if(fromId == 9 && toId == 21) return "새마을금고 방향으로";

    if(fromId == 10 && toId == 7) return "정문 옆 샛길 방향으로";
    if(fromId == 10 && toId == 9) return "성균관대 정문 방향으로";
    if(fromId == 10 && toId == 11) return "성균관대 언덕길 방향으로";

    if(fromId == 11 && toId == 10) return "명륜당 방향으로";
    if(fromId == 11 && toId == 12) return "국제관 오르막길 방향으로";

    if(fromId == 12 && toId == 11) return "명륜당 방향으로";
    if(fromId == 12 && toId == 13) return "학생회관 오르막길 방향으로";

    if(fromId == 13 && toId == 12) return "국제관 방향으로";
    if(fromId == 13 && toId == 14) return "금잔디 광장 방향으로";

    if(fromId == 14 && toId == 13) return "학생회관 방향으로";
    if(fromId == 14 && toId == 25) return "경영관 지하2층 출입문 방향으로";

    if(fromId == 15 && toId == 5) return "혜화동 로터리 방향으로";
    if(fromId == 15 && toId == 16) return "혜화로 횡단보도 방향으로";

    if(fromId == 16 && toId == 15) return "혜화동 로터리 방향으로";
    if(fromId == 16 && toId == 17) return "혜화초 방향으로";

    if(fromId == 17 && toId == 16) return "혜화로 횡단보도 방향으로";
    if(fromId == 17 && toId == 18) return "혜화초 앞 로터리 방향으로";

    if(fromId == 18 && toId == 17) return "혜화초 방향으로";
    if(fromId == 18 && toId == 19) return "새마을금고 방향으로";

    if(fromId == 19 && toId == 18) return "혜화초 앞 로터리 방향으로";
    if(fromId == 19 && toId == 20) return "명륜 새마을금고 앞으로";

    if(fromId == 20 && toId == 19) return "혜화초 로터리 방향으로";
    if(fromId == 20 && toId == 21) return "성균관대 정문 방향으로";
    if(fromId == 20 && toId == 22) return "쪽문 방향 골목으로";

    if(fromId == 21 && toId == 9) return "성균관대 정문 방향으로";
    if(fromId == 21 && toId == 20) return "새마을금고 방향으로";

    if(fromId == 22 && toId == 20) return "새마을금고 방향으로";
    if(fromId == 22 && toId == 23) return "쪽문 엘리베이터 오르막길 방향으로";

    if(fromId == 23 && toId == 22) return "명륜 새마을금고 방향으로";
    if(fromId == 23 && toId == 24) return "쪽문 엘리베이터 방향으로";

    if(fromId == 24 && toId == 23) return "언덕 아래로";
    if(fromId == 24 && toId == 25) return "경영관 1층 출입문 방향으로";

    if(fromId == 25 && toId == 14) return "금잔디 광장 방향으로";
    if(fromId == 25 && toId == 24) return "쪽문 엘리베이터 방향으로";

    return "앞쪽으로";
}

/* ---------- ADT 초기화 ---------- */

void initMap(RouteMap *m) {
    int area[ROWS][COLS] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0,19,19,18, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0,19,19, 0,18, 0, 0, 0, 0},
        {25,24,23,23,22, 0, 0,19,19, 0, 0,17,17, 0, 0, 0},
        {25, 0, 0, 0,22,20, 0,19, 0, 0, 0, 0,17, 0, 0, 0},
        {14,14,13, 0, 0,20,20,20, 0, 0, 0, 0,17, 0, 0, 0},
        { 0, 0,13, 0, 0, 0, 0,21, 0, 0, 0, 0,17,16, 0, 0},
        { 0, 0,12,12, 0, 0, 0,21, 0, 0, 0, 0, 0,15, 0, 0},
        { 0, 0, 0,12, 0, 0, 0,21, 0, 0, 0, 0, 0,15, 0, 0},
        { 0, 0, 0,12, 0, 0, 0,21, 0, 0, 0, 0, 0,15,15, 0},
        { 0, 0, 0,12,11, 0, 0,21,21, 0, 0, 0, 0, 0, 5, 5},
        { 0, 0, 0, 0,11, 0, 0, 0,21, 0, 0, 0, 0, 6, 5, 5},
        { 0, 0, 0, 0,10,10,10,10, 9, 0, 0, 0, 0, 6, 0, 4},
        { 0, 0, 0, 0, 0, 0, 7, 0, 8, 8, 0, 0, 6, 6, 0, 4},
        { 0, 0, 0, 0, 0, 0, 7, 7, 0, 8, 0, 6, 6, 0, 2, 1},
        { 0, 0, 0, 0, 0, 0, 0, 7, 7, 3, 3, 3, 0, 2, 2, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 0, 0},
    };

    int danger[ROWS][COLS] = {  // 위험도
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 3, 0, 0, 0, 0},
        { 1, 1, 3, 3, 3, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
        { 1, 0, 0, 0, 3, 3, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        { 1, 1, 2, 0, 0, 3, 3, 3, 0, 0, 0, 0, 1, 0, 0, 0},
        { 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 3, 0, 0},
        { 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2},
        { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 2, 2},
        { 0, 0, 0, 0, 1, 1, 1, 1, 3, 0, 0, 0, 0, 1, 0, 1},
        { 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        { 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 0, 1, 1, 0, 2, 2},
        { 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 0, 2, 2, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 0, 0},
    };

    int slope[ROWS][COLS] = {   // 경사도
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 0, 0, 0, 0},
        { 1, 3, 3, 3, 2, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0},
        { 1, 0, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0},
        { 1, 1, 3, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        { 0, 0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
        { 0, 0, 3, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        { 0, 0, 0, 3, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1},
        { 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
        { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
        { 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        { 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 0, 1, 1, 0, 1, 1},
        { 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 0, 1, 1, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
    };

    int obstacle [ROWS][COLS] = {   // 장애물
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0},
        { 1, 0, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0},
        { 1, 1, 2, 0, 0, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0},
        { 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0},
        { 0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0},
        { 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0},
        { 0, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 2, 0},
        { 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1},
        { 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 1},
        { 0, 0, 0, 0, 2, 2, 2, 2, 1, 0, 0, 0, 0, 2, 0, 1},
        { 0, 0, 0, 0, 0, 0, 3, 0, 1, 1, 0, 0, 2, 2, 0, 1},
        { 0, 0, 0, 0, 0, 0, 3, 3, 0, 1, 0, 2, 2, 0, 2, 1},
        { 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 2, 0, 2, 2, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0},
    };

    int width [ROWS][COLS] = {  // 폭
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0},
        { 1, 1, 1, 1, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0},
        { 1, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0},
        { 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0},
        { 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0},
        { 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0},
        { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0},
        { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 0},
        { 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2},
        { 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2},
        { 0, 0, 0, 0, 2, 2, 2, 2, 1, 0, 0, 0, 0, 2, 0, 2},
        { 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 0, 2, 2, 0, 2},
        { 0, 0, 0, 0, 0, 0, 3, 3, 0, 3, 0, 2, 2, 0, 1, 1},
        { 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 1, 1, 0, 1, 1, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
    };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            m->areaMap[i][j] = area[i][j];
            m->dangerMap[i][j] = danger[i][j];
            m->slopeMap[i][j] = slope[i][j];
            m->obstacleMap[i][j] = obstacle[i][j];
            m->widthMap[i][j] = width[i][j];
        }
    }
}


/* ---------- 이동 가능 구역 확인 ---------- */

int canMove(RouteMap *m, int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return 0;     // 배열 범위를 벗어나면 이동 불가
    if (m->areaMap[r][c] == 0) return 0;                        // 구역 ID가 0이면 통행 불가 구역
    if (m->statusMap[r][c] == 3) return 0;                      // 전면 통제하면 이동 차단
    return 1;
}

/* ---------- 해당 칸의 이동 비용(cost) 계산 ---------- */

int calculateCost(RouteMap *m, int r, int c, int dangerWeight, int slopeWeight, int obstacleWeight, int widthWeight) {
    int base = m->dangerMap[r][c] * dangerWeight
                + m->slopeMap[r][c] * slopeWeight
                + m->obstacleMap[r][c] * obstacleWeight
                + m->widthMap[r][c] * widthWeight;

    int penalty = 0;
    if (m->statusMap[r][c] == 1) penalty = 3;  // 위험 소폭 증가
    if (m->statusMap[r][c] == 2) penalty = 6;   // 일부 통제

    return base + penalty;
}

/* ---------- 추천 경로 지도 출력 ---------- */

void printRouteMap(RouteMap *m, Position path[], int pathCount) {
    int routeMark[ROWS][COLS] = {0};

    for (int i = 0; i < pathCount; i++) {
        routeMark[path[i].row][path[i].col] = 1;
    }

    printf("\n[추천 경로 지도]\n");
    printf("* = 추천 경로, # = 이동 불가\n\n");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (routeMark[i][j]) {
                printf(" * ");
            } else if (m->areaMap[i][j] == 0 || m->areaMap[i][j] == -1) {
                printf(" # ");
            } else {
                printf("%2d ", m->areaMap[i][j]);
            }
        }
        printf("\n");
    }
}

/* ---------- 사용자 위치 입력 관련 함수 ---------- */

void printLocationMenu() {
    printf("\n[이동 가능한 장소 목록]\n");

    for (int i = 1; i <= 25; i++) {
        printf("%2d. ", i);
        printAreaName(i);
        printf("\n");
    }
}

Position findFirstPositionById(RouteMap *m, int id) {
    Position pos = {-1, -1};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (m->areaMap[i][j] == id) {
                pos.row = i;
                pos.col = j;
                return pos;
            }
        }
    }

    return pos;
}

/* ---------- 최적 경로 추천 ---------- */

void recommendRoute(RouteMap *m, Position start, Position end, int dangerWeight, int slopeWeight, int obstacleWeight, int widthWeight) {
    int dist[ROWS][COLS];           // 출발지에서 이 칸까지 오는 데 드는 최소 비용
    int visited[ROWS][COLS];        // 이미 처리한 칸 표시
    Position prev[ROWS][COLS];      // 이전 구역 기록

    int dr[4] = {-1, 1, 0, 0};  // 행(row) 변화 → 상하 이동
    int dc[4] = {0, 0, -1, 1};  // 열(col) 변화 → 좌우 이동

    // 모든 배열 초기화
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dist[i][j] = INF;
            visited[i][j] = 0;
            prev[i][j].row = -1;
            prev[i][j].col = -1;
        }
    }

    dist[start.row][start.col] = 0;     // 출발지 0으로 설정

    for (int count = 0; count < ROWS * COLS; count++) {
        int min = INF;
        Position cur = {-1, -1};

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (!visited[i][j] && dist[i][j] < min) {   // 아직 방문하지 않았고 dist가 가장 작은 경우
                    min = dist[i][j];
                    cur.row = i;
                    cur.col = j;
                }
            }
        }

        if (cur.row == -1) break;
        visited[cur.row][cur.col] = 1;

        if (cur.row == end.row && cur.col == end.col) break;

        for (int k = 0; k < 4; k++) {
            int nr = cur.row + dr[k];
            int nc = cur.col + dc[k];

            if (canMove(m, nr, nc) && !visited[nr][nc]) {
                int newCost = dist[cur.row][cur.col]
                            + calculateCost(m, nr, nc, dangerWeight, slopeWeight, obstacleWeight, widthWeight);

                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    prev[nr][nc] = cur;
                }
            }
        }
    }

    if (dist[end.row][end.col] == INF) {
        printf("\n경로를 찾을 수 없습니다.\n");
        return;
    }

    Position path[ROWS * COLS];
    int pathCount = 0;

    Position cur = end;
    while (cur.row != -1 && cur.col != -1) {
        path[pathCount++] = cur;
        Position next = prev[cur.row][cur.col];
        cur = next;
    }

    int totalDanger = 0;
    int totalSlope = 0;
    int totalObstacle = 0;
    int totalWidth = 0;

    for (int i = pathCount - 1; i >= 0; i--) {
        int r = path[i].row;
        int c = path[i].col;

        totalDanger += m->dangerMap[r][c];
        totalSlope += m->slopeMap[r][c];
        totalObstacle += m->obstacleMap[r][c];
        totalWidth += m->widthMap[r][c];
    }

    printf("\n====================================\n");
    printf("        추천 경로 결과\n");
    printf("====================================\n");

    printf("총 Cost: %d\n", dist[end.row][end.col]);
    printf("위험도 합계: %d\n", totalDanger);
    printf("경사도 합계: %d\n", totalSlope);
    printf("장애물 합계: %d\n", totalObstacle);
    printf("폭 합계: %d\n", totalWidth);

    printf("\n[길 안내]\n");

    int prevId = -999;
    int step = 1;
    int prevR = -1;
    int prevC = -1;

    for (int i = pathCount - 1; i >= 0; i--) {
        int r = path[i].row;
        int c = path[i].col;
        int id = m->areaMap[r][c];

        if (id != prevId) {
            printf("%d. ", step++);
            
            if (i == pathCount - 1) {
                printAreaName(id);
                printf("에서 출발합니다. 안내를 시작합니다.\n");
            } else if (i == 0) {
                printAreaName(id);
                printf("에 도착합니다. 안내를 종료합니다.\n");
            } else {
                int prevAreaId = m->areaMap[prevR][prevC];
                printf("%s ", getRouteDirection(prevAreaId, id));
                printAreaName(id);
                printf(" 구역으로 이동합니다.\n");

                if (id == 5 || id == 18)
                    printf("    ※ 교차로 주변이므로 주의하세요.\n");
                if (id == 11 || id == 12 || id == 13 || id == 23)
                    printf("    ※ 경사가 가파르므로 주의하세요.\n");
                if (id == 16)
                    printf("    ※ 차량 통행에 주의하세요.\n");
                if (id == 24)
                    printf("    ※ 엘리베이터를 탑승하세요.\n");
            }
            prevId = id;
        }

        prevR = r;
        prevC = c;
    }

    printf("\n[경로 구역 요약]\n");

    prevId = -999;

    for (int i = pathCount - 1; i >= 0; i--) {
        int r = path[i].row;
        int c = path[i].col;
        int id = m->areaMap[r][c];

        if (id != prevId) {
            printf("-> ");
            printAreaName(id);
            printf("\n");
            prevId = id;
        }
    }

    printRouteMap(m, path, pathCount);
}

/* ---------- 사용자 도로 상황 제보 ---------- */

void reportRoadStatus(RouteMap *m) {
    printf("\n도로 상황 제보가 있으신가요? (없으면 0 입력)\n");
    printf("구역 번호: ");
    int reportId;
    scanf("%d", &reportId);

    if (reportId == 0) return;

    printf("현재 도로 상황을 선택하세요.\n");
    printf("1. 위험 소폭 증가 (바로 옆 공사, 차도 인접 등)\n");
    printf("2. 일부 통제 (보도 폭 감소, 우회 필요)\n");
    printf("3. 전면 통제 (완전 통행 불가)\n");
    printf("선택: ");
    int reportStatus;
    scanf("%d, &reportStatus");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (m->areaMap[i][j] == reportId) {
                m->statusMap[i][j] = reportStatus;
            }
        }
    }
    printf("\n[도로 상황 반영 완료]\n");
}

/* ---------- main ---------- */

int main() {
    RouteMap map;
    initMap(&map);
    reportRoadStatus(&map);

    int startId, endId;
    Position start, end;

    int mode;
    int dangerWeight, slopeWeight, obstacleWeight, widthWeight;

    printf("====================================\n");
    printf(" Barrier-Free Route Recommendation\n");
    printf("====================================\n");

    printLocationMenu();

    printf("\n출발 위치 번호를 입력하세요: ");
    scanf("%d", &startId);

    printf("도착 위치 번호를 입력하세요: ");
    scanf("%d", &endId);

    start = findFirstPositionById(&map, startId);
    end = findFirstPositionById(&map, endId);

    if (start.row == -1 || end.row == -1) {
        printf("\n잘못된 위치 번호입니다. 1번부터 25번 사이의 장소 번호를 입력해야 합니다.\n");
        return 0;
    }

    printf("\n[출발지] ");
    printAreaName(startId);
    printf("\n[도착지] ");
    printAreaName(endId);
    printf("\n");

    printf("\n경로 추천 기준을 선택하세요.\n");
    printf("1. 안전 우선 경로\n");
    printf("2. 경사 적은 경로\n");
    printf("3. 균형 경로\n");
    printf("선택: ");
    scanf("%d", &mode);

    if (mode == 1) {
        dangerWeight = 5;
        slopeWeight = 1;
        obstacleWeight = 2;
        widthWeight = 1;
        printf("\n[선택 기준] 안전 우선 경로\n");
    } else if (mode == 2) {
        dangerWeight = 1;
        slopeWeight = 5;
        obstacleWeight = 2;
        widthWeight = 1;
        printf("\n[선택 기준] 경사 적은 경로\n");
    } else {
        dangerWeight = 2;
        slopeWeight = 2;
        obstacleWeight = 2;
        widthWeight = 2;
        printf("\n[선택 기준] 균형 경로\n");
    }

    recommendRoute(&map, start, end, dangerWeight, slopeWeight, obstacleWeight, widthWeight);

    return 0;
}