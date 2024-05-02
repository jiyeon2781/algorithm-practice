#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>

#define MAX_COUNT 51

using namespace std;

int BFS(int start, vector<int> graph[], vector<bool> visited);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int A, B;
    vector<int> graph[MAX_COUNT];
    vector<bool> visited(MAX_COUNT);
    while (true) {
        cin >> A >> B;
        if (A == -1 && B == -1) break;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    int minScore = MAX_COUNT;
    set<int> members;
    for (int i = 1; i <= N; i++) {
        fill(visited.begin(), visited.end(), false);
        int score = BFS(i, graph, visited);

        if (score < minScore) {
            members.clear();
            members.insert(i);
            minScore = score;
        }
        else if (score == minScore) members.insert(i);
    }

    cout << minScore << ' ' << members.size() << "\n";
    for (auto member : members) {
        cout << member << ' ';
    }
}

int BFS(int start, vector<int> graph[], vector<bool> visited) {
    int score = 0;
    queue<pair<int, int>> que;
    que.push({ start, 0 });
    visited[start] = true;
    int count = 0; 
    while (!que.empty()) {
        int cur = que.front().first;
        int depth = que.front().second;
        que.pop();
        count = depth;

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (visited[next]) continue;
            que.push({ next, depth + 1 });
            visited[next] = true;
        }
    }
    return count;
}