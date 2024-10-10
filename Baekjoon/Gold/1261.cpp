#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x;
    int y;
    int cost;
};

struct compare {
    bool operator() (const Node& a, const Node& b) {
        return a.cost < b.cost;
    }
};

void Dijkstra(int N, int M);

const int MaxSize = 101;
const int INF = 100001;
const int Dir = 4;

int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];

int dirX[Dir] = { 0, 0, -1, 1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, M;
    cin >> N >> M;

    string str;
    for (int i = 0; i < M; i++) {
        cin >> str;
        for (int j = 0; j < N; j++) {
            map[i][j] = str[j] - '0';
        }
    }
    Dijkstra(N, M);
    cout << cost[M - 1][N - 1];
}

void Dijkstra(int N, int M) {
    priority_queue<Node, vector<Node>, compare> que;
    fill(cost[0], cost[0] + MaxSize * MaxSize, INF);
    cost[0][0] = 0;
    que.push({ 0, 0, 0 });

    while (!que.empty()) {
        Node cur = que.top();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            int nextX = cur.x + dirX[i];
            int nextY = cur.y + dirY[i];
            if (nextX < 0 || nextX >= M || nextY < 0 || nextY >= N) continue;

            int nextCost = map[nextX][nextY] == 1 ? cur.cost + 1 : cur.cost;

            if (nextCost >= cost[nextX][nextY]) continue;
            cost[nextX][nextY] = nextCost;
            que.push({ nextX, nextY, nextCost });
        }
    }
}