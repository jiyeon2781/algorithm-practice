#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxSize = 100001;

void BFS(int start, int end);

int cost[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;
    BFS(N, K);
    cout << cost[K];
}

void BFS(int start, int end) {
    queue<int> que;
    que.push(start);

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        if (cur == end) break;

        if (cost[cur - 1] == 0 && cur >= 1) {
            cost[cur - 1] = cost[cur] + 1;
            que.push(cur - 1);
        }

        if (cost[cur + 1] == 0 && cur + 1 <= MaxSize) {
            cost[cur + 1] = cost[cur] + 1;
            que.push(cur + 1);
        }

        if (cost[cur * 2] == 0 && cur * 2 >= 0 && cur * 2 <= MaxSize) {
            cost[cur * 2] = cost[cur] + 1;
            que.push(cur * 2);
        }
    }
}
