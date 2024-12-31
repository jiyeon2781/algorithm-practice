#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxSize = 201;
const int MaxMoveCnt = 31;

int BFS(int W, int H, int K);
void Print(int W, int H);

struct Node {
    int x;
    int y;
    int move;
};

int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize][MaxMoveCnt];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int knightX[8] = { 1, 1, 2, 2, -1, -1, -2, -2 };
int knightY[8] = { 2, -2, 1, -1, 2 ,-2, 1, -1 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int K, W, H;
    cin >> K >> W >> H;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> map[i][j];
    }
   
    int result = BFS(W, H, K);
    cout << result;
}

int BFS(int W, int H, int K) {
    queue<Node> que;
    que.push({ 0, 0, K });
    cost[0][0][K] = 1;

    while (!que.empty()) {
        int curX = que.front().x, curY = que.front().y;
        int move = que.front().move;

        que.pop();

        if (curX == H - 1 && curY == W - 1) return cost[curX][curY][move] - 1;

        if (move > 0) {
            for (int i = 0; i < 8; i++) {
                int nextX = curX + knightX[i], nextY = curY + knightY[i];

                if (nextX < 0 || nextX >= H || nextY < 0 || nextY >= W) continue;
                if (map[nextX][nextY] == 1 || cost[nextX][nextY][move - 1] != 0) continue;

                cost[nextX][nextY][move - 1] = cost[curX][curY][move] + 1;
                que.push({ nextX, nextY, move - 1 });
            }
        }

        for (int i = 0; i < 4; i++) {
            int nextX = curX + dirX[i], nextY = curY + dirY[i];

            if (nextX < 0 || nextX >= H || nextY < 0 || nextY >= W) continue;
            if (map[nextX][nextY] == 1 || cost[nextX][nextY][move] != 0) continue;

            cost[nextX][nextY][move] = cost[curX][curY][move] + 1;
            que.push({ nextX, nextY, move });
        }
    }
    return -1;
}