#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<int> lists;
    vector<bool> isPrime(N+1, true);

    if (N == 1) {
        cout << 0;
        return 0;
    }

    for (int i = 2; i <= N; i++) {
        if (!isPrime[i]) continue;
        for (long long j = (long long) i * i; j <= N; j += i) isPrime[j] = false;
        lists.push_back(i);
    }

    int start = 0, end = 0, sum = lists[0], cnt = 0;

    for (start = 0; start < lists.size(); start++) {
        while (sum < N && end < lists.size() - 1) sum += lists[++end];
        if (N == sum) cnt += 1;
        sum -= lists[start];
    }

    cout << cnt << "\n";
}