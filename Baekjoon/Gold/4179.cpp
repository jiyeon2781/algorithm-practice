#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x;
    int y;
};

int BFS(queue<pair<Node ,char>> que, int R, int C, Node start);

const int MaxSize = 1001;
const int Dir = 4;

char map[MaxSize][MaxSize];
int dist[MaxSize][MaxSize];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int R, C;
    cin >> R >> C;

    queue<pair<Node, char>> que;
    Node start;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if (map[i][j] == 'F') {
                que.push({ { i, j }, 'F' });
                dist[i][j] = 1;
            }
            if (map[i][j] == 'J') start = { i, j };
        }
    }

    int result = BFS(que, R, C, start);

    if (result == -1) cout << "IMPOSSIBLE";
    else cout << result;
}

int BFS(queue<pair<Node, char>> que, int R, int C, Node start) {
    que.push({start , 'J'});
    dist[start.x][start.y] = 1;

    while (!que.empty()) {
        Node cur = que.front().first;
        char curCh = que.front().second;
        que.pop();

        if (curCh == 'J') {
            if (cur.x == R - 1 || cur.x == 0 || cur.y == C - 1 || cur.y == 0)
                return dist[cur.x][cur.y];
        }

        for (int i = 0; i < Dir; i++) {
            int nextX = cur.x + dirX[i];
            int nextY = cur.y + dirY[i];

            if (nextX < 0 || nextX >= R || nextY < 0 || nextY >= C) continue;
            if (dist[nextX][nextY] != 0 || map[nextX][nextY] == '#') continue;
            dist[nextX][nextY] = dist[cur.x][cur.y] + 1;
            que.push({ { nextX, nextY }, curCh});
        }
    }
    return -1;
}