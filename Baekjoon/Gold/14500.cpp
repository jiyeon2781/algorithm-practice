#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x, y;
    int depth;
    int sum;
};

int BFS(pair<int, int> start, int N, int M, int maxDepth);

const int MaxSize = 501;
const int Dir = 4;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int dirX[Dir] = { 0, 0, 1, -1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int shapeDirX[Dir] = { 1, 1, -1, -1 };
int shapeDirY[Dir] = { 1, -1, 1, -1 };
// ㅗ모양 처리 방향

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

    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) continue;
            int cur = BFS({ i, j }, N, M, 4);
            result = max(cur, result);
        }
    }
    cout << result;
}

int BFS(pair<int, int> start, int N, int M, int maxDepth) {
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);
    queue<Node> que;
    que.push({ start.first, start.second, 1, map[start.first][start.second] });

    int maxNum = 0;
    while (!que.empty()) {
        Node cur = que.front();
        que.pop();

        visited[cur.x][cur.y] = true;

        if (cur.sum > maxNum && cur.depth == maxDepth) maxNum = cur.sum;

        if (cur.depth == 2) {
            // ㅗ 모양 처리
            for (int i = 0; i < Dir; i++) {
                pair<int, int> next1 = { cur.x + shapeDirX[i], cur.y }, next2 = { cur.x, cur.y + shapeDirY[i] };
                if (next1.first < 0 || next1.first >= N || next1.second < 0 || next1.second >= M) continue;
                if (next2.first < 0 || next2.first >= N || next2.second < 0 || next2.second >= M) continue;
                if (visited[next1.first][next1.second] || visited[next2.first][next2.second]) continue;
                if (map[next1.first][next1.second] == 0 || map[next2.first][next2.second] == 0) continue;
                maxNum = max(cur.sum + map[next1.first][next1.second] + map[next2.first][next2.second], maxNum);
            }

            // ㅁ 모양 처리
            for (int i = 0; i < Dir; i++) {
                pair<int, int> prev = { cur.x + dirX[i], cur.y + dirY[i] };
                if (!visited[prev.first][prev.second]) continue;
                if (cur.x == prev.first) {
                    if (cur.x + 1 < N) maxNum = max(cur.sum + map[cur.x + 1][cur.y] + map[prev.first + 1][prev.second], maxNum);
                    else if (cur.x - 1 >= 0) maxNum = max(cur.sum + map[cur.x - 1][cur.y] + map[prev.first - 1][prev.second], maxNum);
                }
                else if (cur.y == prev.second) {
                    if (cur.y + 1 < M) maxNum = max(cur.sum + map[cur.x][cur.y + 1] + map[prev.first][prev.second + 1], maxNum);
                    else if (cur.y - 1 >= 0) maxNum = max(cur.sum + map[cur.x][cur.y - 1] + map[prev.first][prev.second - 1], maxNum);
                }
            }
        }

        for (int i = 0; i < Dir; i++) { 
            int nextX = cur.x + dirX[i], nextY = cur.y + dirY[i];
            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
            if (cur.depth >= maxDepth || visited[nextX][nextY] || map[nextX][nextY] == 0) continue;
            que.push({ nextX, nextY, cur.depth + 1, cur.sum + map[nextX][nextY] });
        }
    }
    return maxNum;
}