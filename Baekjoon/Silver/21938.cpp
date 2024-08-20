#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_MAP_CNT 1001
#define DIRECTION 4

using namespace std;

void BFS(int x, int y, int T, int N, int M);

int dirX[DIRECTION] = { 0, 0, 1, -1 };
int dirY[DIRECTION] = { 1, -1, 0, 0 };

int pixels[MAX_MAP_CNT][MAX_MAP_CNT];
bool visited[MAX_MAP_CNT][MAX_MAP_CNT] = { false, };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    int R, G, B;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> R >> G >> B;
            pixels[i][j] = (R + G + B) / 3; // calculate pixel
        }
    }

    int T, result = 0;
    cin >> T;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (pixels[i][j] >= T && !visited[i][j]) {
                BFS(i, j, T, N, M);
                result += 1;
            }
        }
    }

    cout << result;
}

void BFS(int x, int y, int T, int N, int M) {
    queue<pair<int, int>> que;
    que.push({ x, y });
    visited[x][y] = true;

    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;
        que.pop();

        for (int i = 0; i < DIRECTION; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
            if (visited[nextX][nextY] || pixels[nextX][nextY] < T) continue;
            que.push({ nextX, nextY });
            visited[nextX][nextY] = true;
        }
    }
}