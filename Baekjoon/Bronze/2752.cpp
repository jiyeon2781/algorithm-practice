#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    priority_queue<int, vector<int>, greater<int>> que;
    int N;
    for (int i = 0; i < 3; i++) {
        cin >> N;
        que.push(N);
    }

    while (!que.empty()) {
        cout << que.top() << ' ';
        que.pop();
    }
}