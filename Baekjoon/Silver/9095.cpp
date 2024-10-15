#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 11;
int dp[MaxSize + 1];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, N;
    cin >> tc;

    dp[1] = 1, dp[2] = 2, dp[3] = 4;
    for (int i = 4; i <= MaxSize; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    while (tc--) {
        cin >> N;
        cout << dp[N] << "\n";
    }
}
