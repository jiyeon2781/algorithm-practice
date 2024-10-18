#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int cost;
    int cnt;
};

void Init(int N, int M);
int BFS(pair<int, int> start, pair<int, int> end, int N, int M);

const int MaxSize = 1001;
const int Dir = 4;

int map[MaxSize][MaxSize];
Node cost[MaxSize][MaxSize];

int dirX[Dir] = { 0, 0, 1, -1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < M; j++) map[i][j] = str[j] - '0';
    }

    int startRes = BFS({ 0, 0 }, { N - 1, M - 1 }, N, M); // (0, 0) -> (N-1, M-1)
    int endRes = BFS({ N - 1, M - 1 }, { 0, 0 }, N, M); // (N-1, M-1) -> (0, 0)
    // 시작점 근처나 끝점 근처에 벽이 있는 경우가 존재하므로, 두 가지를 모두 비교해봐야 함

    if (startRes == -1 && endRes == -1) cout << -1;
    else {
        if (startRes == -1) cout << endRes;
        else if (endRes == -1) cout << startRes;
        else cout << min(startRes, endRes);
    }
}

void Init(int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cost[i][j] = { 0, 0 };
    }
}

int BFS(pair<int, int> start, pair<int, int> end, int N, int M) {
    queue<pair<int, int>> que;
    Init(N, M);
    que.push(start);
    cost[start.first][start.second] = { 1, 0 };

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        if (cur == end) return cost[cur.first][cur.second].cost;
        
        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;
            if (cost[next.first][next.second].cost != 0) continue;

            if (map[next.first][next.second] == 1) {
                if (cost[cur.first][cur.second].cnt == 1) continue;
                cost[next.first][next.second].cnt = 1;
            }

            cost[next.first][next.second].cnt += cost[cur.first][cur.second].cnt;
            cost[next.first][next.second].cost = cost[cur.first][cur.second].cost + 1;
            que.push(next);
        }
    }

    return -1;
}