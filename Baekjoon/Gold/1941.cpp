#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void Backtracking(int x, int y, int depth);
bool IsSeatClose();

const int DirCnt = 4;
const int MaxSize = 5;
const int MaxDepth = 7;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];
bool closedVisited[MaxSize][MaxSize];

int dirX[DirCnt] = { 0, 0, 1, -1 };
int dirY[DirCnt] = { 1, -1, 0, 0 };

int sCnt = 0, resCnt = 0;

vector<pair<int,int>> corp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++)
            map[i][j] = cin.get();
        cin.get();
    }

    Backtracking(0, 0, 0);
    cout << resCnt;
}

bool IsSeatClose() { // 7명이 만들어졌을 때 인접한지 확인 (BFS)
    queue<pair<int, int>> que;
    que.push(corp[0]);
    int cnt = 1;

    fill(closedVisited[0], closedVisited[0] + 25, false);
    closedVisited[corp[0].first][corp[0].second] = true;

    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;
        que.pop();

        for (int i = 0; i < DirCnt; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            if (nextX < 0 || nextX >= MaxSize || nextY < 0 || nextY >= MaxSize) continue;
            if (closedVisited[nextX][nextY] || !visited[nextX][nextY]) continue;
            cnt += 1;
            que.push({ nextX, nextY });
            closedVisited[nextX][nextY] = true;
        }
    }

    if (cnt == MaxDepth) return true;
    else return false;
}

void Backtracking(int x, int y, int depth) { // 7명이 될때까지 Backtracking으로 조합
    if (depth == MaxDepth) {
        if (sCnt >= 4 && IsSeatClose()) resCnt += 1;
        return;
    }

    for (int i = x; i < MaxSize; i++) {
        int curY = (i == x ? y : 0);

        for (int j = curY; j < MaxSize; j++) {
            if (visited[i][j]) continue;
            visited[i][j] = true;
            corp.push_back({ i,j });
            if (map[i][j] == 'S') sCnt += 1;

            Backtracking(i, j, depth + 1);

            visited[i][j] = false;
            corp.pop_back();
            if (map[i][j] == 'S') sCnt -= 1;
        }
    }
}
