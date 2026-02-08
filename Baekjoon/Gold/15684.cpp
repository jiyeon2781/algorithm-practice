#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

void Start();
bool Result();
void Backtracking(int depth, int maxDepth);
bool StartLadder(int num);

const int MaxHSize = 31;
const int MaxNSize = 11;

bool ladder[MaxHSize][MaxNSize];

int N, M, H;
bool isEnd = false;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> H;

    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        ladder[a][b] = true;
    }

    Start();

    return 0;
}

void Start() {
    int cur = 0;
    while (cur <= 3) {
        isEnd = false;
        Backtracking(0, cur);

        if (isEnd) {
            cout << cur;
            return;
        }
        cur += 1;
    }
    cout << -1;
}

void Backtracking(int depth, int maxDepth) {
    if (isEnd) 
        return;

    if (depth == maxDepth) {
        isEnd = Result();
        return;
    }

    // 가로선 추가
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j < N; j++) {
            if (ladder[i][j]) continue;
            // 이미 가로선 존재
            if (j > 1 && ladder[i][j - 1]) continue;
            if (j < N - 1 && ladder[i][j + 1]) continue;
            // 연속 가로선 X

            ladder[i][j] = true;
            Backtracking(depth + 1, maxDepth);
            ladder[i][j] = false;
        }
    }
}

bool Result() {
    // i번째가 i 인것인가?
    for (int i = 1; i <= N; i++) {
        if (!StartLadder(i)) {
            return false;
        }
    }
    return true;
}

bool StartLadder(int num) {
    int cur = num;

    for (int h = 1; h <= H; h++) {
        if (ladder[h][cur]) { // 오른쪽 가로선
            cur += 1;
        }
        else if (cur > 1 && ladder[h][cur - 1]) { // 왼쪽 가로선
            cur -= 1;
        }
    }

    return cur == num;
}