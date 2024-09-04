#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void Sorting(int N);

const int MaxSize = 32001;

vector<int> heights[MaxSize];
int indegree[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, A, B;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> A >> B;
        heights[A].push_back(B);
        indegree[B] += 1;
    }

    Sorting(N);
}

void Sorting(int N) { // topological sorting
    queue<int> que;
    
    for (int i = 1; i <= N; i++)
        if (indegree[i] == 0) que.push(i);

    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        cout << cur << ' ';
        for (int i = 0; i < heights[cur].size(); i++) {
            int next = heights[cur][i];
            indegree[next] -= 1;
            if (indegree[next] == 0) que.push(next);
        }
    }
}