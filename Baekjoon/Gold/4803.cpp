#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

void Init(int N);
void DFS(int start, int parent);

const int MaxSize = 501;

vector<int> graph[MaxSize];
bool visited[MaxSize];
bool isCycleTree = false;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, a, b;
    int result, idx = 1;

    while (true) {
        cin >> N >> M;
        if (N == 0 && M == 0) break;

        Init(N);
        result = 0;

        for (int i = 0; i < M; i++) {
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for (int i = 1; i <= N; i++) {
            if (visited[i]) continue;
            isCycleTree = false;
            DFS(i, -1);
            if (!isCycleTree) result += 1;
        }

        if (result == 0) cout << "Case " << idx++ << ": No trees.\n";
        else if (result == 1) cout << "Case " << idx++ << ": There is one tree.\n";
        else cout << "Case " << idx++ << ": A forest of " << result << " trees.\n";
    }
}

void Init(int N) {
    for (int i = 1; i <= N; i++)
        graph[i].clear();
    fill(visited, visited + N + 1, false);
}

void DFS(int start, int parent) {
    visited[start] = true;

    for (auto node : graph[start]) {
        if (visited[node]) {
            if(node != parent) isCycleTree = true;
            continue;
        }
        else DFS(node, start);
    }
}