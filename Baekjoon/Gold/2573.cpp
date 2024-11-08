#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void BFS(pair<int, int> start, int N, int M);

const int MaxSize = 301;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    int cnt = 0;
    while (true) {
        int cur = 0;
        fill(visited[0], visited[0] + MaxSize * MaxSize, false);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 0 || visited[i][j]) continue;

                if (cur >= 1) {
                    cout << cnt;
                    return 0;
                }

                BFS({ i, j }, N, M);
                cur += 1;
            }
        }
        cnt += 1;
        if (cur == 0) break;
    }

    cout << 0;
}

void BFS(pair<int, int> start, int N, int M) {
    queue<pair<int, int>> que;
    que.push(start);
    visited[start.first][start.second] = true;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        int meltCnt = 0;
        for (int i = 0; i < 4; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };

            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;
            if (visited[next.first][next.second]) continue;
            if (map[next.first][next.second] == 0) {
                meltCnt += 1;
                continue;
            }

            que.push(next);
            visited[next.first][next.second] = true;
        }
        map[cur.first][cur.second] -= meltCnt;
        if (map[cur.first][cur.second] < 0) map[cur.first][cur.second] = 0;
    }
}