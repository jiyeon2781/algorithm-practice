#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, num;
    cin >> N >> M;

    priority_queue<long long, vector<long long>, greater<long long>> que;

    while (N--) {
        cin >> num;
        que.push(num);
    }

    long long cur1, cur2;

    while (M--) {
        cur1 = que.top();
        que.pop();

        cur2 = que.top();
        que.pop();

        que.push(cur1 + cur2);
        que.push(cur1 + cur2);
    }

    long long result = 0;
    while (!que.empty()) {
        result += que.top();
        que.pop();
    }
    cout << result;
}