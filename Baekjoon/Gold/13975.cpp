#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, N, fileSize;
    cin >> tc;
    while (tc--) {
        cin >> N;
        priority_queue<long long ,vector<long long>, greater<long long>> que;

        while (N--) {
            cin >> fileSize;
            que.push(fileSize);
        }

        long long first, second, result = 0;

        while (!que.empty()) {
            if (que.size() <= 1) break;
            first = que.top();
            que.pop();
            second = que.top();
            que.pop();

            long long curNum = first + second;
            result += curNum;
            que.push(curNum);
        }
        cout << result << "\n";
    }

    return 0;
}
