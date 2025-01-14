#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

int BFS(pair<int, int> start, pair<int, int> end, int N, int M , int K);

const int MaxSize = 1001;
const int MaxDepth = 11;
const int dir = 4;

int map[MaxSize][MaxSize];
int cost[MaxDepth][MaxSize][MaxSize];

int dirX[dir] = { 0, 0, 1, -1 };
int dirY[dir] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.size(); j++) map[i][j] = str[j] - '0';
    }

    int result = BFS({ 0, 0 }, { N - 1, M - 1 }, N, M, K);

    cout << result;
}

int BFS(pair<int, int> start, pair<int, int> end, int N, int M, int K) {
    fill(cost[0][0], cost[0][0] + MaxDepth * MaxSize * MaxSize, 0);
    queue<pair<pair<int, int>, int>> que;
    que.push({start, K});
    cost[K][start.first][start.second] = 1;

    while (!que.empty()) {
        pair<int, int> cur = que.front().first;
        int depth = que.front().second;
        que.pop();

        if (cur.first == end.first && cur.second == end.second) return cost[depth][end.first][end.second];

        for (int i = 0; i < dir; i++) {
            pair<int, int> next = { cur.first + dirX[i] , cur.second + dirY[i] };

            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;

            if (map[next.first][next.second] == 0 && cost[depth][next.first][next.second] == 0) {
                cost[depth][next.first][next.second] = cost[depth][cur.first][cur.second] + 1;
                que.push({ next, depth });
            }
            else if (map[next.first][next.second] == 1 && depth > 0 && cost[depth - 1][next.first][next.second] == 0) {
                cost[depth - 1][next.first][next.second] = cost[depth][cur.first][cur.second] + 1;
                que.push({ next, depth - 1 });
            }
        }
    }
    return -1;
}