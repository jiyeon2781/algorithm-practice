#include <iostream>
#include <vector>
#include <stack>

#define MAX_NUM 100001

using namespace std;

vector<int> graph[MAX_NUM];
int result[MAX_NUM];
bool visited[MAX_NUM];

void DFS(int start);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, node1, node2;

    cin >> N;
    for (int i = 1; i < N; i++) {
        cin >> node1 >> node2;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    DFS(1);

    for (int i = 2; i <= N; i++) {
        cout << result[i] << "\n";
    }
    return 0;
}

void DFS(int start) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int curNode = st.top();
        st.pop();
        visited[curNode] = true;
        for (int i = 0; i < graph[curNode].size(); i++) {
            if (result[graph[curNode][i]] == 0) result[graph[curNode][i]] = curNode;
            if (visited[graph[curNode][i]]) continue;
            st.push(graph[curNode][i]);
        }
    }
}