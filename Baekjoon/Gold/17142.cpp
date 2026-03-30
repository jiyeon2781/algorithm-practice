#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void Backtracking(int cur, int idx);
void BFS();
int MaxTime();

const int MaxSize = 51;
const int VirusMaxCnt = 11;
const int Dir = 4;
const int INF = 99999999;

int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];

int N, M, result = INF;

vector<pair<int, int>> virusList;
vector<pair<int, int>> activatedVirus;
bool isActivatedIdx[VirusMaxCnt];

int dirX[Dir] = { 0, 0, -1, 1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2)
                virusList.push_back({ i,j });
        }
    }

    Backtracking(0, 0);

    if (result == INF)
        cout << -1;
    else
        cout << result;

    return 0;
}

void Backtracking(int cur, int idx) {
    if (cur == M) {
        BFS();
        

        int curTime = MaxTime();
        if (curTime != -1)
            result = min(result, curTime);
        return;
    }

    for (int i = idx; i < virusList.size() ; i++) {
        if (isActivatedIdx[i])
            continue;

        isActivatedIdx[i] = true;
        activatedVirus.push_back(virusList[i]);
        Backtracking(cur + 1, i + 1);
        activatedVirus.pop_back();
        isActivatedIdx[i] = false;
    }
}

void BFS() {
    fill(cost[0], cost[0] + MaxSize * MaxSize, -1);
    queue<pair<int, int>> que;

    for (auto v : activatedVirus) {
        cost[v.first][v.second] = 0;
        que.push(v);
    }

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (cost[next.first][next.second] != -1 || map[next.first][next.second] == 1)
                continue;
            cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
            que.push(next);
        }
    }
}

int MaxTime() {
    int maxNum = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0) {
                if (cost[i][j] == -1)
                    return -1;
                maxNum = max(maxNum, cost[i][j]);
            }
        }
    }
    return maxNum;
}