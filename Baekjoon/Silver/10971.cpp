#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

void Backtracking(int start, int cur, int cost, int depth, int max);

const int MaxSize = 11;

int result = 99999999;

int W[MaxSize][MaxSize];
bool visited[MaxSize];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> W[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        Backtracking(i, i, 0, 0, N);
        fill(visited, visited + MaxSize, false);
    }

    cout << result;

    return 0;
}

void Backtracking(int start, int cur, int cost, int depth, int max) {
    if (depth == max && start == cur) {
        if (cost < result)
            result = cost;
        return;
    }

    for (int i = 0; i < max; i++) {
        if (W[cur][i] == 0 || visited[i] || cost > result)
            continue;
        visited[i] = true;
        Backtracking(start, i, cost + W[cur][i], depth + 1, max);
        visited[i] = false;

    }
}