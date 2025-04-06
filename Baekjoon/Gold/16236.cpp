#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x, y;
    int time;
};

struct Shark {
    int x, y;
    int size;
};

bool Compare(Node a, Node b) {
    if (a.time == b.time) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
    return a.time < b.time;
}

void InitVisited(int N);
int Moving(int N);
vector<Node> SearchEatFishes(int N);

const int MaxSize = 21;
const int Dir = 4;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

Shark shark;

int dirX[Dir] = { -1, 0, 0, 1 };
int dirY[Dir] = { 0, -1, 1, 0 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 9) {
                shark = { i, j, 2 };
                map[i][j] = 0;
            }
        }
    }

    int resultTime = Moving(N);
    cout << resultTime;
}

void InitVisited(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }
}

int Moving(int N) { // 상어의 움직임
    int resultTime = 0;
    int eatCount = 0;

    while (true) {
        InitVisited(N);
        visited[shark.x][shark.y] = true;

        vector<Node> fishes = SearchEatFishes(N);
        // 같은 거리의 먹이가 여러개 있을 때를 고려해 vector에 먹이들 저장
        // 조건 : 가장 위, 가장 좌측 물고기 선택

        sort(fishes.begin(), fishes.end(), Compare);
        if (fishes.size() == 0) break;

        Node firstEatFish = fishes[0];
        map[firstEatFish.x][firstEatFish.y] = 0;
        resultTime += firstEatFish.time;
        eatCount += 1;

        if (eatCount == shark.size) {
            eatCount = 0;
            shark.size += 1;
        }

        shark.x = firstEatFish.x, shark.y = firstEatFish.y;
    }

    return resultTime;
}

vector<Node> SearchEatFishes(int N) { // 가까운 먹이들 탐색(BFS)
    queue<Node> que;
    vector<Node> fishes;

    que.push({shark.x, shark.y, 0});

    while (!que.empty()) {
        int curX = que.front().x;
        int curY = que.front().y;
        int curTime = que.front().time;
        que.pop();

        for (int i = 0; i < Dir; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            int nextTime = curTime + 1;

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
            if (map[nextX][nextY] > shark.size || visited[nextX][nextY]) continue;

            if (shark.size > map[nextX][nextY] && map[nextX][nextY] != 0) 
                fishes.push_back({ nextX, nextY, nextTime });
            else que.push({ nextX, nextY, nextTime });

            visited[nextX][nextY] = true;
        }
    }
    return fishes;
}