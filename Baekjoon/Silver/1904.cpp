#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1000001;
const int mod = 15746;
int dp[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= N; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    }

    cout << dp[N];
}