#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

void DFS(int x, int y);

const int MaxSize = 51;

int map[MaxSize][MaxSize];
int idx[MaxSize][MaxSize];

int dirX[4] = { 0, 0, 1, -1 };
int dirY[4] = { 1, -1, 0, 0 };

int N, L, R;
bool isOpen;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> L >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> map[i][j];
    }

    int result = 0;

    while (true) {
        fill(idx[0], idx[0] + MaxSize * MaxSize, 0);

        int curIdx = 1;
        isOpen = false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (idx[i][j] != 0) continue;
                idx[i][j] = curIdx++;
                DFS(i, j);
            }
        }
        if (!isOpen) break;
        result += 1;
    }

    cout << result;
}

void DFS(int x, int y) {
    stack<pair<int, int>> curSt;
    stack<pair<int, int>> visitedNodeSt;
    curSt.push({ x, y });
    visitedNodeSt.push({ x, y });
    pair<int, int> result = {1, map[x][y]}; // cnt, sum

    while (!curSt.empty()) {
        pair<int, int> cur = curSt.top();
        curSt.pop();

        for (int i = 0; i < 4; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N) continue;
            if (idx[next.first][next.second] != 0) continue;

            int sub = abs(map[cur.first][cur.second] - map[next.first][next.second]);
            if (sub < L || sub > R) continue;
            idx[next.first][next.second] = idx[x][y];
            curSt.push(next);
            visitedNodeSt.push(next);
            result.first += 1;
            result.second += map[next.first][next.second];
        }
    }

    int re = result.second / result.first;

    while (!visitedNodeSt.empty()) {
        auto corp = visitedNodeSt.top();
        visitedNodeSt.pop();

        if (map[corp.first][corp.second] != re) isOpen = true; // 국경선 open 여부
        map[corp.first][corp.second] = re;
    }
}