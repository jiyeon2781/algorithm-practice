#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1000001;
int dp[MaxSize] = { 0, 0, 1, 1 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;

    for (int i = 4; i <= N; i++) {
        dp[i] = dp[i - 1] + 1;
        if (i % 2 == 0) dp[i] = min(dp[i / 2] + 1, dp[i]);
        if (i % 3 == 0) dp[i] = min(dp[i / 3] + 1, dp[i]);
    }
    cout << dp[N];
}