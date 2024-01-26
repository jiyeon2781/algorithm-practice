#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_NUM 31

using namespace std;

char map[MAX_NUM][MAX_NUM][MAX_NUM];
bool visited[MAX_NUM][MAX_NUM][MAX_NUM];

int dirX[6] = {0, 1, 0, -1, 0, 0};
int dirY[6] = {0, 0, 1, 0, -1, 0};
int dirZ[6] = {1, 0, 0, 0, 0, -1};

struct Location {
    int l, r, c;
    int count;
};


int BFS(Location start, Location maxNum);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 빌딩에 갇혀서 탈출하고자 함
    // 각 칸에 인접한 6개의 칸(동,서,남,북,상,하)로 1분의 시간을 들여 이동 가능 -> 대갃건 이동 X
    // 출구까지 얼마나 걸릴까?

    int L, R, C;
    Location start, maxNum;

    char ch;
    while (true) {
        cin >> L >> R >> C;
        start = { 0, 0, 0, 0 };
        maxNum = { L, R, C };
        fill_n(&visited[0][0][0], sizeof(visited), false);
        fill_n(&map[0][0][0], sizeof(map), 0);

        if (L == 0 && R == 0 && C == 0) break;
        // L 빌딩의 층수, R과 C는 한 층의 행과 열의 개수
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < R; j++) {
                for (int k = 0; k < C; k++) {
                    cin >> ch;
                    map[i][j][k] = ch;
                    if (ch == 'S') start = { i, j, k, 0 };
                }
            }
        }

        int result = BFS(start, maxNum);
        if (result == -1) cout << "Trapped!\n";
        else cout << "Escaped in " << result << " minute(s).\n";
    }

    return 0;
}

int BFS(Location start, Location maxNum) {
    queue<Location> que;
    que.push(start);
    int count = 99999;
    while (!que.empty()) {
        Location cur = que.front();
        que.pop();

        if (map[cur.l][cur.r][cur.c] == 'E') return cur.count;

        for (int i = 0; i < 6; i++) {
            int nextX = cur.l + dirX[i];
            int nextY = cur.r + dirY[i];
            int nextZ = cur.c + dirZ[i];
            if (nextX < 0 || nextX >= maxNum.l || nextY < 0 || nextY >= maxNum.r || nextZ < 0 || nextZ >= maxNum.c) continue;
            if (map[nextX][nextY][nextZ] == '#' || visited[nextX][nextY][nextZ]) continue;
            que.push({ nextX, nextY, nextZ, cur.count + 1 });
            visited[nextX][nextY][nextZ] = true;
        }
    }
    return -1;
}