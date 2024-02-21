#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#define NODE_COUNT 51

using namespace std;

vector<int> tree[NODE_COUNT];
bool visited[NODE_COUNT];

int DFS(int root, int removedNode);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N , parent ,root = 0,node;
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        cin >> parent;
        if (parent != -1) {
            tree[parent].push_back(i);
            continue;
        }
        root = i;
    }

    cin >> node;
    int result = DFS(root, node);
    cout << result;
    
    return 0;
}


int DFS(int root, int removedNode) {
    int count = 0;
    stack<int> st;
    if (root == removedNode) return 0;
    // root 노드가 삭제될 때
    st.push(root);

    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        if (tree[cur].size() == 0 || (tree[cur].size() == 1 && tree[cur][0] == removedNode)) {
            // 자식 노드가 없거나 자식 노드가 삭제된 노드일 때 
            count += 1;
            continue;
        }

        for (int i = 0; i < tree[cur].size(); i++) {
            if (visited[tree[cur][i]] || tree[cur][i] == removedNode) continue;
            visited[tree[cur][i]] = true;
            st.push(tree[cur][i]);
        }
    }
    return count;

}