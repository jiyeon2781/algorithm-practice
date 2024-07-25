#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void BFS(pair<int, int> start, vector<vector<int>> map, vector<vector<bool>> visited, vector<vector<int>> &result);

struct Node
{
    int x;
    int y;
    int dist;
};

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, num;
    cin >> N >> M;
    pair<int, int> start;

    vector<vector<int>> map(N, vector<int>(M, 0));
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> result(N, vector<int>(M, -1));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) {
            cin >> num;
            map[i][j] = num;

            if (num == 2 || num == 0) {
                if (num == 2) start = { i, j };
                result[i][j] = 0;
            }
        }
    }

    BFS(start, map, visited , result);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) {
            cout << result[i][j] << ' ';
        }
        cout << "\n";
    }
}

void BFS(pair<int, int> start, vector<vector<int>> map, vector<vector<bool>> visited, vector<vector<int>>& result)
{
    queue<Node> que;

    que.push({ start.first , start.second, 0 });
    visited[start.first][start.second] = true;

    while (!que.empty())
    {
        int curX = que.front().x;
        int curY = que.front().y;
        int curDist = que.front().dist;

        que.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];

            if (nextX < 0 || nextX >= map.size() || nextY < 0 || nextY >= map[0].size()) continue;
            if (visited[nextX][nextY] || map[nextX][nextY] == 0) continue;

            visited[nextX][nextY] = true;
            que.push({ nextX, nextY, curDist + 1 });
            result[nextX][nextY] = curDist + 1;
        }
    }
}