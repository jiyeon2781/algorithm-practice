#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

#define MAX_COUNT 20001

using namespace std;

map<int, int> BFS(vector<bool> visited);

vector<int> graph[MAX_COUNT];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, A, B;
    cin >> N >> M;

    vector<bool> visited(N + 1);

    while (M--) {
        cin >> A >> B;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    int resultNumber = 0, resultDistance = 0, resultCount = 0;

    map<int, int> result = BFS(visited);
    // 각 노드별 거리 저장

    for (pair<int, int> element : result)
    {
        if (element.second > resultDistance) {
            resultCount = 1;
            resultNumber = element.first;
            resultDistance = element.second;
        }
        else if (element.second == resultDistance)
        {
            resultCount += 1;
            if (resultNumber > element.first) resultNumber = element.first;
        }
    }

    cout << resultNumber << ' ' << resultDistance << ' ' << resultCount;
}  

map<int, int> BFS(vector<bool> visited)
{
    queue<pair<int, int>> que;
    que.push({ 1, 0 });
    visited[1] = true;

    map<int, int> result;

    while (!que.empty()) {
        int node = que.front().first;
        int dist = que.front().second;

        que.pop();
        result[node] = dist;

        for (int i = 0; i < graph[node].size(); i++) {
            int nextNode = graph[node][i];
            if (visited[nextNode]) continue;
            visited[nextNode] = true;
            que.push({ nextNode, dist + 1 });
        }
    }

    return result;
}