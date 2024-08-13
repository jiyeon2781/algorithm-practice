#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_BOXES_CNT 1001

using namespace std;

bool CanTomatoesBeRiped(int N, int M); // 안익은 토마토 존재 유무
void BFS(int N, int M);

int boxes[MAX_BOXES_CNT][MAX_BOXES_CNT]; // 격자 모양 박스
int cost[MAX_BOXES_CNT][MAX_BOXES_CNT]; // 토마토가 익어가는 날짜
bool visited[MAX_BOXES_CNT][MAX_BOXES_CNT]; // 방문 여부

queue<pair<int, int>> que;

int dirX[4] = { 0, 0, -1, 1 };
int dirY[4] = { 1, -1, 0, 0 };

int result = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M, N;
    vector<pair<int, int>> tomatoes;

    cin >> M >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> boxes[i][j];
            if (boxes[i][j] == 1) 
                que.push({ i, j }); // 토마토를 모두 queue에 저장해 BFS가 한 번만 진행되게끔 구현
        }
    }

    BFS(N, M);

    if (!CanTomatoesBeRiped(N, M)) result = -1;

    cout << result;
}

bool CanTomatoesBeRiped(int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (cost[i][j] == 0 && boxes[i][j] == 0) return false;
        }
    }
    return true;
}

void BFS(int N, int M) {
    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;

        que.pop();

        for (int i = 0; i < 4; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
            if (visited[nextX][nextY] || boxes[nextX][nextY] != 0) continue;
            // 이미 방문했거나, 토마토가 익었을 때

            cost[nextX][nextY] = cost[curX][curY] + 1;
            if (result < cost[nextX][nextY]) result = cost[nextX][nextY];
            visited[nextX][nextY] = true;
            que.push({ nextX, nextY});
        }
    }
}