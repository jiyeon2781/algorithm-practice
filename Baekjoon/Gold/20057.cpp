#include <iostream>
#include <algorithm>

using namespace std;

void Start();
void Tornado(int dir);
void SetSand(int x, int y, int sand);

const int MaxSize = 500;
const int Dir = 4;

int map[MaxSize][MaxSize];
int N;
int result = 0;

pair<int, int> cur;

int dirX[Dir] = { 0, 1, 0, -1 };
int dirY[Dir] = {-1, 0 , 1, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    Start();
    cout << result;
}

void Start() {
    cur = { N / 2, N / 2 };
    int dir = 0; // 바람의 방향
    int cnt = 0; // 동일한 칸의 개수로 몇번 이동했는지 횟수
    int path = 1; // 칸의 개수

    while (true) {
        if (cnt == 2 && path != N - 1)
        {
            path += 1;
            cnt = 0;
        }

        for (int i = 0; i < path; i++) {
            Tornado(dir);
            cur = { cur.first + dirX[dir], cur.second + dirY[dir] };
        }

        dir = (dir + 1) % Dir;
        cnt += 1;

        if (cur.first == 0 && cur.second == 0) break;
    }
}

void Tornado(int dir) {
    // 토네이도 시전
    // 현재 방향을 기준으로 퍼센트 선정
    // 남은 비율은 알파칸에 저장

    int y_sum = map[cur.first + dirX[dir]][cur.second + dirY[dir]];

    if (y_sum == 0)
        return;

    map[cur.first + dirX[dir]][cur.second + dirY[dir]] = 0;

    int remain = y_sum;
    int next = 0;
    if (dir == 0 || dir == 2) {
        // 1 %
        next = (int)y_sum * ((float)1 / 100);
        SetSand(cur.first + 1, cur.second, next);
        SetSand(cur.first - 1, cur.second, next);
        remain -= next * 2;
        // 7 %
        next = (int)y_sum * ((float)7 / 100);
        SetSand(cur.first + 1, cur.second + dirY[dir], next);
        SetSand(cur.first - 1, cur.second + dirY[dir], next);
        remain -= next * 2;
        // 2 %
        next = (int)y_sum * ((float)2 / 100);
        SetSand(cur.first + 2, cur.second + dirY[dir], next);
        SetSand(cur.first - 2, cur.second + dirY[dir], next);
        remain -= next * 2;
        // 10 %
        next = (int)y_sum * ((float)10 / 100);
        SetSand(cur.first + 1, cur.second + dirY[dir] * 2, next);
        SetSand(cur.first - 1, cur.second + dirY[dir] * 2, next);
        remain -= next * 2;
        // 5 %
        next = (int)y_sum * ((float)5 / 100);
        SetSand(cur.first, cur.second + dirY[dir] * 3, next);
        remain -= next;
    }
    else {
        // 1 % 
        next = (int)y_sum * ((float)1 / 100);
        SetSand(cur.first, cur.second + 1, next);
        SetSand(cur.first, cur.second - 1, next * 1);
        remain -= next * 2;
        // 7 %
        next = (int)y_sum * ((float)7 / 100);
        SetSand(cur.first + dirX[dir], cur.second + 1, next);
        SetSand(cur.first + dirX[dir], cur.second - 1, next);
        remain -= next * 2;
        // 2 %
        next = (int)y_sum * ((float)2 / 100);
        SetSand(cur.first + dirX[dir], cur.second + 2, next);
        SetSand(cur.first + dirX[dir], cur.second - 2, next);
        remain -= next * 2;
        // 10 %
        next = (int)y_sum * ((float)10 / 100);
        SetSand(cur.first + dirX[dir] * 2, cur.second + 1, next);
        SetSand(cur.first + dirX[dir] * 2, cur.second - 1, next);
        remain -= next * 2;
        // 5 %
        next = (int)y_sum * ((float)5 / 100);
        SetSand(cur.first + dirX[dir] * 3, cur.second, next);
        remain -= next;
    }

    SetSand(cur.first + dirX[dir] * 2, cur.second + dirY[dir] * 2, remain);
}

void SetSand(int x, int y, int sand) {
    if (x < 0 || x >= N || y < 0 || y >= N)
        result += sand;
    else map[x][y] += sand;
}