#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void Backtracking(int N, int M, int depth, int max);
int BFS(int N, int M, queue<pair<int, int>> q);

const int MaxSize = 9;
const int Dir = 4;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];
int dirX[Dir] = { 0, 0, -1, 1 };
int dirY[Dir] = { 1, -1, 0, 0 };

queue<pair<int, int>> que;

int result = 0;
int maxCnt = 0;

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
            if (map[i][j] == 0) maxCnt += 1;
            if (map[i][j] == 2) que.push({ i, j });
        }
    }

    Backtracking(N, M, 0, 3);

    cout << result;
}

void Backtracking(int N, int M, int depth, int max) {
    if (depth == max) {
        int cnt = BFS(N, M, que);
        if (result < maxCnt - cnt) result = maxCnt - cnt;
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] != 0) continue;
            map[i][j] = 1;
            maxCnt -= 1;
            Backtracking(N, M, depth + 1, max);
            map[i][j] = 0;
            maxCnt += 1;
        }
    }
}

int BFS(int N, int M, queue<pair<int, int>> q) {
    int cnt = 0;
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;
            if (map[next.first][next.second] != 0 || visited[next.first][next.second]) continue;

            q.push(next);
            visited[next.first][next.second] = true;
            cnt += 1;
        }
    }
    return cnt;
}