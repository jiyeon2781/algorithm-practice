#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void MoveVitamins(int dir, int speed);
void GiveVitamins();
void GetVitamins();
int Result();

const int MaxSize = 16;
const int Dir = 8;

int trees[MaxSize][MaxSize];
bool notCut[MaxSize][MaxSize];
vector<pair<int, int>> vitamins;

int dirX[Dir] = {0, -1, -1, -1, 0, 1, 1, 1};
int dirY[Dir] = {1, 1, 0, -1, -1, -1, 0, 1};
// → 시작으로 반시계 방향

int n, m, d, p;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> trees[i][j];
        }
    }

    for (int i = n - 2; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            vitamins.push_back({ i, j });
        }
    }

    while (m--) {
        cin >> d >> p;
        MoveVitamins(d - 1, p);
        GiveVitamins();
        GetVitamins();
    }

    cout << Result();

    return 0;
}

void MoveVitamins(int dir, int speed) {
    // 각 비타민 이동
    // 1. speed는 격자를 벗어나도 반대 방향으로 나오므로, mod를 통해 이동 가능
    for (int idx = 0; idx < vitamins.size(); idx++) {

        pair<int, int> next = { vitamins[idx].first + dirX[dir] * speed, vitamins[idx].second + dirY[dir] * speed };

        if (next.first < 0) {
            int cur = abs(next.first / n) + 1;
            next.first += (n * cur);
        }
        if (next.second < 0) {
            int cur = abs(next.second / n) + 1;
            next.second += (n * cur);
        }

        next.first %= n;
        next.second %= n;

        vitamins[idx] = { next.first, next.second };
    }
    // 2. vector 갱신
}

void GiveVitamins() {
    fill(notCut[0], notCut[0] + MaxSize * MaxSize, false);
    for (int idx = 0; idx < vitamins.size(); idx++) {
        // 1. 특수 영양제 1개씩 빼서 투입 후 높이 + 1
        pair<int, int> curVitamin = vitamins[idx];
        trees[curVitamin.first][curVitamin.second] += 1;
        notCut[curVitamin.first][curVitamin.second] = true;
    }

    for (int idx = 0; idx < vitamins.size(); idx++) {
        // 1. 특수 영양제 1개씩 빼서 투입 후 높이 + 1
        pair<int, int> curVitamin = vitamins[idx];
        // 2. 각 대각선으로 계산(이때는 경계 확인)
        int cnt = 0;

        for (int curDir = 1; curDir < Dir; curDir += 2) {
            pair<int, int> next = { curVitamin.first + dirX[curDir], curVitamin.second + dirY[curDir] };
            if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
                continue;
            // 2-1. 대각선이 경계를 넘어가면 continue;
            if (trees[next.first][next.second] < 1)
                continue;
            // 2-2. 대각선이 높이가 1 미만이면 continue;
            cnt += 1;
        }

        trees[curVitamin.first][curVitamin.second] += cnt;
    }
}

void GetVitamins() {
    vitamins.clear();

    // 1. 맵을 돌면서 높이가 2 이상인 리브로수를 2만큼 베서 특수 영양제 추가(push_back)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (trees[i][j] >= 2 && !notCut[i][j]) {
                trees[i][j] -= 2;
                vitamins.push_back({ i, j });
            }
        }
    }
}

int Result() {
    int cnt = 0;

    // 1. 남아있는 리브로수 높이 총 합
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (trees[i][j] > 0)
                cnt += trees[i][j];
        }
    }

    return cnt;
}