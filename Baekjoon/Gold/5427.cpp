#include <iostream>
#include <algorithm>
#include <queue>

#define MAX_MAP_CNT 1001

using namespace std;

struct Node {
    int depth; // 이동 거리
    char ch; // 기호
};

void BFS(int N, int M);

char map[MAX_MAP_CNT][MAX_MAP_CNT]; // 지도
Node cost[MAX_MAP_CNT][MAX_MAP_CNT]; // cost가 이동거리 계산 및 visited 역할까지 겸함

int dirX[4] = { 0, 0, -1, 1 };
int dirY[4] = { 1, -1, 0, 0 };

int result = -1;

queue<pair<int, int>> que;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;

    int N, M;
    pair<int, int> start;
    

    while (tc--) {
        cin >> M >> N;
        result = -1;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> map[i][j];
                if (map[i][j] == '*') que.push({ i, j });
                else if (map[i][j] == '@') start = { i, j };

                cost[i][j].ch = map[i][j];
                cost[i][j].depth = 0;
            }
        }

        que.push(start); 
        // 불이 다 이동하고 사람 이동
        // => 불이 붙으려는 칸도 고려해야 하므로

        BFS(N, M);

        if (result == -1) cout << "IMPOSSIBLE\n";
        else cout << result << "\n";
    }
}

void BFS(int N, int M) {
    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;

        que.pop();

        int curDepth = cost[curX][curY].depth;
        int curChar = cost[curX][curY].ch;

        if (cost[curX][curY].ch == '@') {
            if (curX == 0 || curX == N-1 || curY == 0 || curY == M-1) { // 탈출 가능한 위치일 때
                result = cost[curX][curY].depth + 1;
                break;
            }
        }

        for (int i = 0; i < 4; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            int nextDepth = curDepth + 1;

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
            if (map[nextX][nextY] != '.') continue;
            // 이동할 수 없는 곳인지(벽, 불, 사람)
            if (cost[nextX][nextY].depth != 0) continue; 
            // 이미 지나간 자리인지 => @가 먼저 이동한 자리여도 불이 붙든 말든 다시 재방문하지 않으므로

            cost[nextX][nextY].depth = nextDepth;
            cost[nextX][nextY].ch = curChar;
            que.push({ nextX, nextY });
        }
    }
}