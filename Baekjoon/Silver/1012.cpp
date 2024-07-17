#include <iostream>
#include <algorithm>
#include <queue>

#define MAX_MAP_SIZE 51
#define DIRECTION 4

using namespace std;

void BFS(pair<int, int> start, int N, int M);

int maps[MAX_MAP_SIZE][MAX_MAP_SIZE];
bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T, N, M, K;
    int x, y, result = 0;
    cin >> T;

    while (T--)
    {
        cin >> N >> M >> K;

        fill(maps[0], maps[0] + MAX_MAP_SIZE * MAX_MAP_SIZE, 0);
        fill(visited[0], visited[0] + MAX_MAP_SIZE * MAX_MAP_SIZE, false);
        result = 0;
        
        while (K--)
        {
            cin >> x >> y;
            maps[x][y] = 1; // 배추가 심어져 있는 땅
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++) {
                if (maps[i][j] == 1 && !visited[i][j])
                {
                    BFS({i, j}, N, M);
                    result += 1;
                }
            }
        }

        cout << result << "\n";
    }
}

void BFS(pair<int, int> start, int N, int M) {
    queue<pair<int, int>> que;
    que.push(start);
    
    while (!que.empty())
    {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < DIRECTION; i++)
        {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first >= N || next.first < 0 || next.second >= M || next.second < 0) continue;
            // 맵의 크기 범위를 넘을 때
            if (visited[next.first][next.second] || maps[next.first][next.second] == 0) continue;
            // 배추로 심은 땅이 아니거나 이미 방문했을 때

            visited[next.first][next.second] = true;
            que.push(next);
        }
    }
}