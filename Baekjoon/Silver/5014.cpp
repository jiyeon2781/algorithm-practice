#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void BFS(int start, int end, int max, int dir[2]);

const int MaxSize = 1000001;

int cost[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int F, S, G, U, D;
    cin >> F >> S >> G >> U >> D;
    
    int dir[2] = { U, -D };
    BFS(S, G, F, dir);
}

void BFS(int start, int end, int max, int dir[2]) {
    queue<int> que;
    que.push(start);
    int cur, next;

    while (!que.empty()) {
        cur = que.front();
        que.pop();

        if (cur == end) {
            cout << cost[cur];
            return;
        }

        for (int i = 0; i < 2; i++) {
            if (dir[i] == 0) continue;

            next = cur + dir[i];
            if (next <= 0 || next > max) continue;
            if (cost[next] != 0) continue;
            cost[next] = cost[cur] + 1;
            que.push(next);
        }
    }

    cout << "use the stairs";
}