#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int MaxSize = 100001;

void BFS(int start, int end);

int map[MaxSize];
int path[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;

    BFS(N, K);

    int idx = K;
    cout << map[K] - 1 << "\n";
    stack<int> st;

    while (idx != -1) {
        st.push(idx);
        idx = path[idx];
    }

    while (!st.empty()) {
        cout << st.top() << ' ';
        st.pop();
    }
}

void BFS(int start, int end) {
    queue<int> que;
    que.push(start);
    map[start] = 1;
    path[start] = -1;

    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        
        if (cur == end) return;

        if (map[cur + 1] == 0 && cur + 1 >= 0 && cur + 1 <= MaxSize) {
            map[cur + 1] = map[cur] + 1;
            path[cur + 1] = cur;
            que.push(cur + 1);
        }
        if (map[cur - 1] == 0 && cur - 1 >= 0 && cur - 1 <= MaxSize) {
            map[cur - 1] = map[cur] + 1;
            path[cur - 1] = cur;
            que.push(cur - 1);
        }
        if (map[cur * 2] == 0 && cur * 2 >= 0 && cur * 2 <= MaxSize) {
            map[cur * 2] = map[cur] + 1;
            path[cur * 2] = cur;
            que.push(cur * 2);
        }
    }
}
