#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

const int MaxConputerCount = 101;

int DFS(int start);

vector<int> networks[MaxConputerCount];
bool visited[MaxConputerCount];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int comNum, pairNums;
    cin >> comNum >> pairNums;

    int com1, com2;
    while (pairNums--) {
        cin >> com1 >> com2;
        networks[com1].push_back(com2);
        networks[com2].push_back(com1);
    }
    cout << DFS(1);
}

int DFS(int start) {
    stack<int> st;
    int result = -1;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        result += 1;

        for (int i = 0; i < networks[cur].size(); i++) {
            if (visited[networks[cur][i]]) continue;
            visited[networks[cur][i]] = true;
            st.push(networks[cur][i]);
        }
    }
    return result;
}