#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int MaxSize = 32001;

vector<int> problems[MaxSize];
int indegree[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    int a, b;

    while (M--) {
        cin >> a >> b;
        problems[a].push_back(b);
        indegree[b] += 1;
    }

    priority_queue<int, vector<int>, greater<int>> que;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] != 0) continue;
        que.push(i);
    }

    vector<int> result;
    while (!que.empty()) {
        int cur = que.top();
        que.pop();
        result.push_back(cur);

        for (auto element : problems[cur]) {
            indegree[element] -= 1;
            if (indegree[element] == 0) que.push(element);
        }
    }

    for (auto element : result) cout << element << ' ';
}