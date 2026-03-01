#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct Info {
    int z, x, y;
    int cost;
};

void Rotation(int idx);
void Backtracking(int depth);
void AddBoard(int idx, int secIdx);
int BFS();

const int MaxSize = 5;
const int RotationCnt = 4;
const int DirCnt = 6;

int section[MaxSize][MaxSize][MaxSize]; // 각 칸 별 저장된 정보
int board[MaxSize][MaxSize][MaxSize]; // BFS를 통해 돌릴 맵
int cost[MaxSize][MaxSize][MaxSize]; // 최단 거리 기록
bool isExist[MaxSize]; // Backtracking 시 이미 보드에 존재하는지 여부

int temp[MaxSize][MaxSize];

int minCnt = 999999999;

int dirX[DirCnt] = { 1, -1, 0, 0, 0, 0 };
int dirY[DirCnt] = { 0, 0, 1, -1, 0, 0 };
int dirZ[DirCnt] = { 0, 0, 0, 0, 1, -1 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            for (int k = 0; k < MaxSize; k++) {
                cin >> section[i][j][k];
            }
        }
    }

    Backtracking(0);
    if (minCnt == 999999999)
        cout << -1;
    else
        cout << minCnt;
    return 0;
}

// 90도 회전
void Rotation(int idx) {
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            temp[i][j] = section[idx][MaxSize - 1 - j][i];
        }
    }
    
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            section[idx][i][j] = temp[i][j];
        }
    }
}

void AddBoard(int idx, int secIdx) {
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            board[idx][i][j] = section[secIdx][i][j];
        }
    }
}

// 쌓는 형식
void Backtracking(int depth) {
    if (minCnt == 12) // 최단 거리는 12이므로 12일때 종료
        return;

    if (depth == MaxSize) {
        // 최단거리 확인 및 갱신
        if (board[0][0][0] == 0 || board[4][4][4] == 0)
            return;
        int cnt = BFS();
        if (cnt != -1)
            minCnt = min(cnt, minCnt);

        // PrintBoard();
        return;
    }

    for (int i = 0; i < MaxSize; i++) {
        if (isExist[i])
            continue;

        // 각 회전별 저장 및 Backtracking 진행
        isExist[i] = true;


        for (int j = 0; j < RotationCnt; j++) {
            Rotation(i);
            AddBoard(depth, i);
            Backtracking(depth + 1);
        }

        isExist[i] = false;
    }
}

// 최단 거리 구하기
int BFS() {
    memset(cost, 0, sizeof(cost));
    queue<Info> que;
    que.push({ 0,0,0,1 });
    cost[0][0][0] = 1;
    int cnt = 0;

    while (!que.empty()) {
        Info cur = que.front();
        que.pop();
        
        if (cur.x == 4 && cur.y == 4 && cur.z == 4)
            return cost[cur.z][cur.x][cur.y] - 1;

        for (int i = 0; i < DirCnt; i++) {
            Info next = { cur.z + dirZ[i], cur.x + dirX[i], cur.y + dirY[i], cost[cur.z][cur.x][cur.y] + 1 };
            if (next.x < 0 || next.x >= MaxSize || next.y < 0 || next.y >= MaxSize || next.z < 0 || next.z >= MaxSize)
                continue;
            if (cost[next.z][next.x][next.y] > 0)
                continue;
            if (board[next.z][next.x][next.y] == 0)
                continue;
            cost[next.z][next.x][next.y] = next.cost;
            que.push(next);
        }
    }

    return -1;
 }
