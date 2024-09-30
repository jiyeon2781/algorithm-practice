#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int BFS(int l, pair<int, int> start, pair<int, int> end);

const int MaxSize = 301;
const int DirectSize = 8;

int cost[MaxSize][MaxSize];

int dirX[DirectSize] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dirY[DirectSize] = {-1, 1, -2, 2, -2, 2, -1, 1};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int tc;
    cin >> tc;

    int l, result;
    pair<int, int> start, end;

    while (tc--) {
        cin >> l;
        cin >> start.first >> start.second >> end.first >> end.second;

        result = BFS(l, start, end);
        
        cout << result << "\n";
    }
}

int BFS(int l, pair<int, int> start, pair<int, int> end) {
    queue<pair<int, int>> que;

    que.push(start);
    fill(cost[0], cost[0] + MaxSize * MaxSize, -1);
    cost[start.first][start.second] = 0;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        if (cur == end) return cost[cur.first][cur.second];

        for (int i = 0; i < DirectSize; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };

            if (next.first < 0 || next.first >= l || next.second < 0 || next.second >= l) continue;
            if (cost[next.first][next.second] != -1)
                continue;
            cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
            que.push(next);
        }
    }

    return -1;
}