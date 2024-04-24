#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#define MAX_SIZE 1001

using namespace std;

void DFS(int start);

vector<int> graph[MAX_SIZE];
vector<bool> visited(MAX_SIZE);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, N, num;
    cin >> tc;

    while (tc--) {
        cin >> N;

        for (int i = 0; i <= N; i++) graph[i].clear();
        fill(visited.begin(), visited.end(), false);

        for (int i = 1; i <= N; i++) {
            cin >> num;
            graph[i].push_back(num);
        }

        int result = 0;

        for (int i = 1; i <= N; i++) {
            if (visited[i]) continue;
            DFS(i);
            result += 1;
        }
        cout << result << "\n";
    }
}

void DFS(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int cur = st.top();
        st.pop();

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (visited[next]) continue;
            st.push(next);
            visited[next] = true;
        }
    }
}