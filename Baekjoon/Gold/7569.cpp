#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxSize = 101;
const int Dir = 6;

struct Node {
    int x;
    int y;
    int z;
};

void BFS(queue<Node> que, int M, int N, int H);
bool CanTomatoesBeRiped(int M, int N, int H);

int cost[MaxSize][MaxSize][MaxSize];
int result = 1;

int dirX[Dir] = { 1, -1, 0, 0, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1, 0, 0 };
int dirZ[Dir] = { 0, 0, 0, 0, 1, -1 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M, N, H;
    cin >> M >> N >> H;

    queue<Node> que;

    for (int i = 0; i < H; i++) { // z
        for (int j = 0; j < N; j++) { // x
            for (int k = 0; k < M; k++) { // y
                cin >> cost[i][j][k];
                if (cost[i][j][k] == 1) que.push({ j, k, i });
            }
        }
    }

    BFS(que, M, N, H);

    if (CanTomatoesBeRiped(M, N, H)) cout << result - 1;
    else cout << -1;
}

void BFS(queue<Node> que, int M, int N, int H) {
    while (!que.empty()) {
        Node cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            int nextX = cur.x + dirX[i];
            int nextY = cur.y + dirY[i];
            int nextZ = cur.z + dirZ[i];

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M || nextZ < 0 || nextZ >= H) continue;
            if (cost[nextZ][nextX][nextY] != 0) continue;
            que.push({ nextX, nextY, nextZ });
            cost[nextZ][nextX][nextY] = cost[cur.z][cur.x][cur.y] + 1;
            if (result < cost[nextZ][nextX][nextY]) result = cost[nextZ][nextX][nextY];
        }
    }
}

bool CanTomatoesBeRiped(int M, int N, int H) { // 안익은 토마토 존재 유무
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                if (cost[i][j][k] == 0) return false;
            }
        }
    }
    return true;
}