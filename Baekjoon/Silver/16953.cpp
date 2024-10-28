#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <map>

using namespace std;

int BFS(long long start, long long end);

map<int, bool> isVisited;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long a, b;
    cin >> a >> b;

    int result = BFS(a, b);
    cout << result << "\n";
}

int BFS(long long start, long long end) {
    queue<pair<long long, int>> que;
    que.push({ start , 1});
    isVisited[start] = true;

    while (!que.empty()) {
        long long cur = que.front().first;
        int depth = que.front().second;
        que.pop();

        if (cur == end) return depth;

        // * 2
        long long next = cur * 2;
        if (!isVisited[next] && next <= end && next > 0) {
            isVisited[next] = true;
            que.push({ next, depth + 1 });
        }

        // + "1"
        next = cur * 10 + 1;
        if (!isVisited[next] && next <= end && next > 0) {
            isVisited[next] = true;
            que.push({ next, depth + 1 });
        }
    }
    return -1;
}