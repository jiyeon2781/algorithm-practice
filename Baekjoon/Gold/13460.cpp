#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

int BFS(int N, int M, pair<int, int> r, pair<int, int> b);
pair<int, int> Moving(pair<int, int> start, int dir, pair<int, int> another, bool isRed);

struct Node {
    pair<int, int> r;
    pair<int, int> b;
    int cnt;
};

const int MaxSize = 11;
const int MaxCnt = 10;
const int Dir = 4;

char map[MaxSize][MaxSize];

int dirX[Dir] = { 0, 0, 1, -1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, M;
    cin >> N >> M;
    pair<int, int> startR, startB, hole;
    string str;
    
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < M; j++) {
            map[i][j] = str[j];

            if (str[j] == 'R') startR = { i, j };
            else if (str[j] == 'B') startB = { i, j };
            else continue;

            map[i][j] = '.';
        }
    }

    int  result = BFS(N, M, startR, startB);
    cout << result;
}

bool isBlueHole = false, isRedHole = false;

int BFS(int N, int M, pair<int, int> r, pair<int, int> b) {
    queue<Node> que;
    que.push({ r, b, 1 });

    while (!que.empty()) {
        pair<int, int> curR = que.front().r, curB = que.front().b;
        int cnt = que.front().cnt;
        que.pop();
        bool redFirst = true;

        if (cnt > MaxCnt) continue;

        for (int i = 0; i < Dir; i++) {
            // 초기화
            redFirst = true;
            isRedHole = false;
            isBlueHole = false;


            pair<int, int> nextR, nextB;

            //R,B의 각각 위치에 따른 움직임 결정
            if ((i == 0 && curR.second < curB.second) || (i == 1 && curR.second > curB.second)) redFirst = false;
            else if ((i == 2 && curR.first < curB.first) || (i == 3 && curR.first > curB.first)) redFirst = false;

            if (redFirst) {
                nextR = Moving(curR, i, curB, true);
                nextB = Moving(curB, i, nextR, false);
            }
            else {
                nextB = Moving(curB, i, curR, false);
                nextR = Moving(curR, i, nextB, true);
            }

            if (isBlueHole) continue;
            if (isRedHole) return cnt;
            que.push({ nextR, nextB, cnt+1 });
        }
    }
    return -1;
}

pair<int, int> Moving(pair<int, int> start, int dir, pair<int, int> another, bool isRed) {
    pair<int, int> cur = start;

    while (true) {
        if (map[cur.first][cur.second] == 'O') {
            if (isRed) isRedHole = true;
            else isBlueHole = true;
            break;
        }

        if (map[cur.first + dirX[dir]][cur.second + dirY[dir]] == '#' ||
            (cur.first + dirX[dir] == another.first && cur.second + dirY[dir] == another.second && map[another.first][another.second] != 'O'))
            break;

        cur.first += dirX[dir];
        cur.second += dirY[dir];
    }

    return cur;
}
