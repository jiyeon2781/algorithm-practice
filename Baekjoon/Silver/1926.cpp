#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_NUM 501

using namespace std;

bool visited[MAX_NUM][MAX_NUM];
bool pictures[MAX_NUM][MAX_NUM];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

struct Node {
    int x, y;
};

int BFS(int startX, int startY, int n, int m);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, number, count = 0, area = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> number;
            pictures[i][j] = number;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && pictures[i][j] == 1) {
                count += 1;
                int currentArea = BFS(i, j, n , m);
                if (area <= currentArea) area = currentArea;
            }
        }
    }
    cout << count << "\n" << area;
    return 0;
}

int BFS(int startX, int startY, int n, int m) {
    queue<Node> que;
    que.push({ startX ,startY });
    int count = 0;
    while (!que.empty()) {
        Node cur = que.front();
        que.pop();
        if (visited[cur.x][cur.y]) continue;
        count += 1;
        visited[cur.x][cur.y] = true;
        for (int i = 0; i < 4; i++) {
            int nextX = cur.x + dirX[i];
            int nextY = cur.y + dirY[i];
            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m && pictures[nextX][nextY] == 1) {
                que.push({ nextX, nextY });
            }
        }
    }
    return count;
}