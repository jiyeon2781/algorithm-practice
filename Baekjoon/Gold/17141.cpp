#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void Backtracking(int cur, int start);
void BFS();
bool IsNotSpread();

const int INF = 999999999;
const int MaxSize = 51;
const int MaxVirusCnt = 11;

int N, M;
int result = INF, curMax = 0;


int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];

bool isVirus[MaxVirusCnt];
bool isSpread = false;

vector<pair<int, int>> virus, selected;
queue<pair<int, int>> que;
int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2)
                virus.push_back({ i, j });
                
           
        }
    }

    Backtracking(0, 0);

    if (result == INF)
        cout << -1;
    else
        cout << result;
    return 0;
}

void Backtracking(int cur, int start) {
    if (cur == M) {
        BFS();

        curMax = 0;
        if (!IsNotSpread()) {
            result = min(result, curMax);
        }
       
        return;
    }

    for (int i = start; i < virus.size(); i++) {
        if (isVirus[i])
            continue;

        isVirus[i] = true;
        selected.push_back(virus[i]);
        Backtracking(cur + 1, i + 1);
        selected.pop_back();
        isVirus[i] = false;
    }
}

bool IsNotSpread() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 1) {
                if (cost[i][j] == -1)
                    return true;
                curMax = max(curMax, cost[i][j]);
            }
        }
    }
    return false;
}

void BFS() {
    fill(cost[0], cost[0] + MaxSize * MaxSize, -1);

    for (auto& v : selected) {
        que.push(v);
        cost[v.first][v.second] = 0;
    }

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int nextX = cur.first + dirX[i];
            int nextY = cur.second + dirY[i];

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
                continue;
            if (cost[nextX][nextY] != -1 || map[nextX][nextY] == 1)
                continue;

            que.push({ nextX, nextY });
            cost[nextX][nextY] = cost[cur.first][cur.second] + 1;
        }
    }
}