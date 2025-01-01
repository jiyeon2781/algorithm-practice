#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1000001;
const int mod = 1000000000;

int dp[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= abs(N); i++) {
        dp[i] = dp[i - 1] % mod + dp[i - 2] % mod;
    }

    if (N > 0) cout << 1 << "\n";
    else if (N == 0) cout << 0 << "\n";
    else {
        if (N % 2 == 0) cout << -1 << "\n";
        else cout << 1 << "\n";
    }
    cout << dp[abs(N)] % mod;
}