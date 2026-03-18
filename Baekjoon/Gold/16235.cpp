#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void SpringAndSummer();
void EatFoodAndDeleteTree(int x, int y);
void FallAndWinter();
void BornTree(int x, int y);
int CountTrees();

const int MaxSize = 11;
const int Dir = 8;

int N, M, K;

deque<int> maps[MaxSize][MaxSize];
int A[MaxSize][MaxSize];
int current[MaxSize][MaxSize];

int dirX[Dir] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirY[Dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            current[i][j] = 5;
        }
    }

    int x, y, z;

    while (M--) {
        cin >> x >> y >> z;
        maps[x][y].push_back(z);
    }

    while (K--) {
        SpringAndSummer();
        FallAndWinter();
    }

    cout << CountTrees();

    return 0;
}

void SpringAndSummer() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            EatFoodAndDeleteTree(i, j);
        }
    }
}

void EatFoodAndDeleteTree(int x, int y) {
    // 어린 나무부터 처리 -> 정렬
    sort(maps[x][y].begin(), maps[x][y].end());

    deque<int> afterTrees;
    int cnt = 0;

    for (int tree : maps[x][y]) {
        if (tree <= current[x][y]) {
            current[x][y] -= tree;
            afterTrees.push_back(tree + 1);
        }
        else {
            cnt += (tree / 2);
        }
    }

    current[x][y] += cnt;
    maps[x][y] = afterTrees;
}

void FallAndWinter() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {

            for (int cur : maps[i][j]) {
                if (cur % 5 != 0)
                    continue;
                BornTree(i, j);
            }

            current[i][j] += A[i][j];
        }
    }
}

void BornTree(int x, int y) {
    // 번식 -> 8방향
    for (int i = 0; i < Dir; i++) {
        int nextX = dirX[i] + x;
        int nextY = dirY[i] + y;
        if (nextX <= 0 || nextX > N || nextY <= 0 || nextY > N)
            continue;
        
        maps[nextX][nextY].push_front(1);
    }
}

int CountTrees() {
    int cnt = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cnt += maps[i][j].size();
        }
    }

    return cnt;
}