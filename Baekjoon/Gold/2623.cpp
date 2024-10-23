#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MaxSize = 1001;

vector<int> sequence[MaxSize];
int indegree[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, size, num, prev = 0;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> size;
        prev = 0;

        for (int j = 0; j < size; j++) {
            cin >> num;
            if (prev != 0) {
                sequence[prev].push_back(num);
                indegree[num] += 1;
            }
            prev = num;
        }
    }

    queue<int> que;

    for (int i = 1; i <= N; i++) {
        if (indegree[i] != 0) continue;
        que.push(i);
    }

    vector<int> result;
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        result.push_back(cur);

        for (auto element : sequence[cur]) {
            indegree[element] -= 1;
            if (indegree[element] == 0) que.push(element);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (indegree[i] > 0) { // 순서를 못정하는 경우
            cout << 0;
            return 0;
        }
    }

    for (auto element : result) cout << element << "\n";
}