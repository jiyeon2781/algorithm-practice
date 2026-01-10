#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void InitSticker();
void Start();
void Init();
void Save();
bool IsPossible(int x, int y);
void Rotation();

int Result();

const int MaxSize = 41;
const int MaxStickerSize = 11;

int N, M, K;
// 세로, 가로, 스티커 개수
int R, C;
// 현재 스티커의 최대 행, 열

int paper[MaxSize][MaxSize];
int temp[MaxSize][MaxSize];
int sticker[MaxStickerSize][MaxStickerSize];
int tempSticker[MaxStickerSize][MaxStickerSize];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    while (K--) {
        cin >> R >> C;
        InitSticker();
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> sticker[i][j];
            }
        }
        // 1 : 스티커가 붙은 칸

        Start();
    }

    cout << Result();
    // 최종적으로 몇 칸이 채워졌는지 수를 출력

    return 0;
}

void InitSticker() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            sticker[i][j] = 0;
        }
    }
}

void Start() {
    Init();
    bool isPossible = false;

    for (int rot = 0; rot < 4; rot++) {
        // Rotation 값만큼 진행
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // 1. 스티커를 떼어내어 다른 스티커와 겹치지 않고 범위를 벗어나지 않게 붙일 자리를 찾음
                // 1-1. 위쪽부터 스티커를 채워 나가야함
                // 1-2. 위쪽도 여러 군데가 있으면 왼쪽부터 선택
                isPossible = IsPossible(i, j);
                // 2. 선택한 위치에 스티커 부착
                if (isPossible)
                    return;
            }
        }

        // 2-1. 전혀 붙일 곳이 없으면 스티커를 시계 방향으로 90도 회전 후 다시 붙일 자리를 찾음
        Rotation();
    }

    // 2-2. 회전 후에도 전혀붙일곳이 없으면 스티커 제거
}

void Init() { 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            temp[i][j] = paper[i][j];
        }
    }
}

void Save() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            paper[i][j] = temp[i][j];
        }
    }
}

bool IsPossible(int x, int y) {
    Init();

    for (int i = x; i < x + R; i++) {
        for (int j = y; j < y + C; j++) {
            if (sticker[i - x][j - y] == 0)
                continue;
            if (i >= N || j >= M)
                return false;
            if (temp[i][j] == 1)
                return false;
            temp[i][j] = sticker[i - x][j - y];
        }

    }

    Save();
    return true;
}

void Rotation() {
    int st = R;
    R = C;
    C = st;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            tempSticker[i][j] = sticker[C - j - 1][i];
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            sticker[i][j] = tempSticker[i][j];
        }
    }
}


int Result() {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (paper[i][j] == 1)
                count += 1;
        }
    }
    return count;
}