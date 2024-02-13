#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

#define MAX_NUM 501

vector<int> graph[MAX_NUM];
bool visited[MAX_NUM];

int DFS(int start);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, a, b;
    cin >> N >> M;

    while (M--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cout << DFS(1) << "\n";

    return 0;
}

int DFS(int start) {
    stack<pair<int,int>> st;
    visited[1] = true;
    st.push({start, 0});
    int result = 0;

    while (!st.empty()) {
        int curNum = st.top().first;
        int depth = st.top().second;
        st.pop();

        for (int element : graph[curNum]) {
            if (visited[element] || depth >= 2) continue;
            visited[element] = true;
            st.push({element, depth + 1});
            result += 1;
        }
    }
    return result;
}