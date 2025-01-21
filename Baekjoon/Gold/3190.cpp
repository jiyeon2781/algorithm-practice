#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

int MovingSnake(pair<int, int> start, int N);

const int MaxSize = 101;

int map[MaxSize][MaxSize];

int dirX[4] = { 0, 1, 0, -1 };
int dirY[4] = { 1, 0, -1 ,0 };
// 오른쪽, 밑, 왼쪽, 위

queue<pair<int, char>> que;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;
    
    int x, y;

    while (K--) {
        cin >> x >> y;
        map[x - 1][y - 1] = 1;
    }

    int L;
    cin >> L;
    int sec;
    char ch;

    while (L--) {
        cin >> sec >> ch;
        que.push({ sec, ch });
    }

    int result = MovingSnake({ 0, 0 }, N);
    cout << result;
}

int MovingSnake(pair<int, int> start, int N) {
    int dir = 0;
    map[start.first][start.second] = 2;
    int time = 0;

    deque<pair<int, int>> snakeBody;
    snakeBody.push_front(start);

    pair<int, char> changeDir = que.front();
    que.pop();
    bool isApple = false;
    while (true) {
        isApple = false;

        if (time == changeDir.first) { // 방향 전환
            if (changeDir.second == 'D') dir = (dir + 1) % 4;
            else {
                if (dir == 0) dir = 3;
                else dir = (dir - 1);
            }

            if (!que.empty()) {
                changeDir = que.front();
                que.pop();
            }
        }

        // 뱀 이동
        int nextX = snakeBody.front().first + dirX[dir], nextY = snakeBody.front().second + dirY[dir];
        if (map[nextX][nextY] == 2 || nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) return time + 1; 
        // 벽에 부딪히거나 뱀의 몸을 만났을 때
        if (map[nextX][nextY] == 1) isApple = true;

        map[nextX][nextY] = 2;
        snakeBody.push_front({ nextX, nextY });

        if (!isApple) {
            pair<int, int> del = snakeBody.back();
            snakeBody.pop_back();
            map[del.first][del.second] = 0;
        }

        time += 1;
    }
    return -1;
}