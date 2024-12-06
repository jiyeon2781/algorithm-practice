#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void BFS(pair<int, int> start, int N);

const int MaxSize = 101;

int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int result = 101 * 101;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) cost[i][j] = 1;
        }
    }

    int idx = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 1 || visited[i][j]) continue;
            BFS({ i, j }, N);
        }
    }

    cout << result - 1;
}

void BFS(pair<int, int> start, int N) {
    queue<pair<int, int>> que, bridges;
    que.push(start);
    visited[start.first][start.second] = true;

    while (!que.empty()) { // 1 구역 먼저 방문 표시
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N) continue;
            if (visited[next.first][next.second]) continue;

            if (map[next.first][next.second] == 1) {
                visited[next.first][next.second] = true;
                que.push(next);
            }
            else if (map[next.first][next.second] == 0) {
                cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
                bridges.push(next); // 다리 놓을 첫 위치 시작
                continue;
            }
        }
    }


    while (!bridges.empty()) { // 0 구역 방문
        pair<int, int> cur = bridges.front();
        bridges.pop();

        
        for (int i = 0; i < 4; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N) continue;
            if (visited[next.first][next.second]) continue;

            if (map[next.first][next.second] == 1) result = min(result, cost[cur.first][cur.second]);
            else {
                if (cost[next.first][next.second] == 0 || cost[next.first][next.second] > cost[cur.first][cur.second] + 1) {
                    cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
                    bridges.push(next);
                }
            }
        }
    }
}