#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void Start();
void GrepShark();
void MoveSharks();
void InitNextMap();
void InitMap();
pair<int, int> MoveShark(pair<int ,int> start, int speed);

struct Shark {
    int speed;
    int dir;
    int size;
};

const int DirCnt = 4;
const int MaxSize = 101;

int R, C, M;

Shark map[MaxSize][MaxSize];
Shark nextMap[MaxSize][MaxSize];

int dirX[DirCnt] = { -1, 1, 0, 0 };
int dirY[DirCnt] = { 0, 0, 1, -1 };
// 위, 아래, 오른쪽, 왼쪽

int result = 0;
int humanIdx = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> C >> M;

    int r, c, s, d, z;
    // 상어의 정보들
    while (M--) {
        cin >> r >> c >> s >> d >> z;
        map[r][c] = { s, d - 1, z };
    }

    Start();

    return 0;
}

void Start() {
    while (humanIdx < C) {
        // 1. 낚시왕 이동
        humanIdx += 1;

        // 2. 낚시왕이 존재하는 열에 상어를 잡음(가장 가까운 곳, 행이 작은 곳)
        GrepShark();

        // 3. 상어 이동
        MoveSharks();
    }
    cout << result;
}

void GrepShark() {
    // 가장 가까운 열의 상어 잡음
    for (int i = 1; i <= R; i++) {
        if (map[i][humanIdx].size != 0) {
            // 상어 점수 추가 및 map 초기화
            result += map[i][humanIdx].size;
            map[i][humanIdx] = { 0, 0, 0 };
            return;
        }
    }
}

int curDir;

void MoveSharks() {
    InitNextMap();

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (map[i][j].size == 0) continue;

            Shark shark = map[i][j];
            curDir = shark.dir;

            int speed = shark.speed;

            // 최적화를 위해 speed를 주기로 계산
            if (shark.dir <= 1)
                speed %= (R - 1) * 2;
            else
                speed %= (C - 1) * 2;
            // ---

            pair<int, int> next = MoveShark({ i,j }, speed);

            if (nextMap[next.first][next.second].size < shark.size) {
                shark.dir = curDir;
                nextMap[next.first][next.second] = shark;
            }
        }
    }

    InitMap();
}

void InitNextMap() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            nextMap[i][j] = { 0, 0, 0 };
        }
    }
}

void InitMap() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            map[i][j] = nextMap[i][j];
        }
    }
}

pair<int, int> MoveShark(pair<int, int> start, int speed) {
    // 0, 1 (위, 아래)
    // 2, 3 (오른쪽, 왼쪽)

    pair<int, int> cur = start;
    while (speed > 0) {
        pair<int, int> next = { cur.first + dirX[curDir], cur.second + dirY[curDir] };

        if (next.first <= 0 || next.first > R || next.second <= 0 || next.second > C) {
            if (curDir == 0)
                curDir = 1;
            else if (curDir == 1)
                curDir = 0;
            else if (curDir == 2)
                curDir = 3;
            else if (curDir == 3)
                curDir = 2;
            next = { cur.first + dirX[curDir], cur.second + dirY[curDir] };
        }

        cur = next;
        speed -= 1;
    }

    return cur;
}