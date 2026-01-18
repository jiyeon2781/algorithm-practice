#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

void Start();
bool IsPossible(int x, int y);
void Bomb(int x, int y);
void Move();

const int MaxSize = 12;
const int MaxWidthSize = 6;
const int MaxDir = 4;

char map[MaxSize][MaxWidthSize];
bool visited[MaxSize][MaxWidthSize];
bool bombVisited[MaxSize][MaxWidthSize];

int dirX[MaxDir] = { 0, 0, 1, -1 };
int dirY[MaxDir] = { 1, -1, 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;

    for (int i = 0; i < MaxSize; i++) {
        cin >> str;
        for (int j = 0; j < MaxWidthSize; j++) {
            map[i][j] = str[j];
        }
    }

    Start();

    return 0;
}

void Start() {
    int count = 0;
    // 1. 이미 뿌요는 떨어진 상태
    bool isEnd = true;
    while (true) {
        // Init
        fill(visited[0], visited[0] + MaxSize * MaxWidthSize, false);
        isEnd = true;

        for (int i = 0; i < MaxSize; i++) {
            for (int j = 0; j < MaxWidthSize; j++) {
                if (map[i][j] != '.' && !visited[i][j] && IsPossible(i, j)) {
                    isEnd = false;
                    Bomb(i, j);
                    // 2. 연쇄 터지기 시작
                }
            }
        }

        if (isEnd)
            break;
        count += 1;
        Move();
    // 3. 중력 영향으로 이동
    // 4. 연쇄할 뿌요가 있다면 2번으로 돌아감
    }

    // 연쇄 카운트 출력
    cout << count;
}

bool IsPossible(int x, int y) {
    int cnt = 0;
    char puyo = map[x][y];
    queue<pair<int, int>> que;
    que.push({ x, y });
    visited[x][y] = true;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();
        cnt += 1;

        for (int i = 0; i < MaxDir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first >= MaxSize || next.second >= MaxWidthSize || next.first < 0 || next.second < 0)
                continue;
            if (visited[next.first][next.second] || map[next.first][next.second] != puyo)
                continue;
            que.push(next);
            visited[next.first][next.second] = true;
        }
    }

    return cnt >= 4 ? true : false;
}

void Bomb(int x, int y) {
    char puyo = map[x][y];
    queue<pair<int, int>> que;
    que.push({ x, y });
    fill(bombVisited[0], bombVisited[0] + MaxSize * MaxWidthSize, false);

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();
        map[cur.first][cur.second] = '.';

        for (int i = 0; i < MaxDir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first >= MaxSize || next.second >= MaxWidthSize || next.first < 0 || next.second < 0)
                continue;
            if (bombVisited[next.first][next.second] || map[next.first][next.second] != puyo)
                continue;
            que.push(next);
            bombVisited[next.first][next.second] = true;
        }
    }
}

void Move() {
    for (int i = 0; i < MaxWidthSize; i++) {
        queue<char> que;
        for (int j = 0; j < MaxSize; j++) {
            if (map[j][i] == '.')
                continue;
            que.push(map[j][i]);
            map[j][i] = '.';
        }

        for (int j = MaxSize - que.size(); j < MaxSize; j++) {
            map[j][i] = que.front();
            que.pop();
        }
    } 
}
