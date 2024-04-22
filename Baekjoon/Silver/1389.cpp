#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_USER 101
#define MAX_RELATION_COUNT 500001

using namespace std;

int BFS(int start, int end, vector<int> visited, vector<int> graph[]);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, A, B;

    cin >> N >> M;

    vector<int> graph[MAX_USER];
    vector<int> visited(MAX_USER);

    while (M--) {
        cin >> A >> B;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    int maxUser = MAX_USER, maxCount = MAX_RELATION_COUNT;

    for (int i = 1; i <= N; i++) {
        int sumCount = 0;
        
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;
            fill(visited.begin(), visited.end(), false);
            auto curCount = BFS(i, j, visited, graph);
            sumCount += curCount;
        } 

        if (sumCount < maxCount) {
            maxCount = sumCount;
            maxUser = i;
        }
    }

    cout << maxUser;
}

int BFS(int start, int end, vector<int> visited, vector<int> graph[]) {
    queue<pair<int, int>> que;
    que.push({start, 0});
    visited[start] = true;

    while (!que.empty()) {
        int cur = que.front().first;
        int depth = que.front().second;
        que.pop();

        if (cur == end) return depth;

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (visited[next]) continue;
            visited[next] = true;
            que.push({next, depth + 1});
        }
    }
    return -1;
}