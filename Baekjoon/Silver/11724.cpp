#include <iostream>
#include <vector>
#include <stack>

#define MAX_NUM 1001

using namespace std;

vector<int> graph[MAX_NUM];
bool visited[MAX_NUM];
void DFS(int i);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, U, V, result = 0;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> U >> V;
        graph[U].push_back(V);
        graph[V].push_back(U);
    }

    for (int i = 1; i <= N; i++) {
        if (visited[i]) continue;
        DFS(i);
        result += 1;
    }
    cout << result << "\n";
    return 0;
}

void DFS(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;
    while (!st.empty()) {
        int curNode = st.top();
        st.pop();
        visited[curNode] = true;
        for (int i = 0; i < graph[curNode].size(); i++) {
            if (visited[graph[curNode][i]]) continue;
            st.push(graph[curNode][i]);
        }
    }
}