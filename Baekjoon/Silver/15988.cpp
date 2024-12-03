#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1000001;
const int Mod = 1000000009;

long long dp[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i < MaxSize; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % Mod;
    }

    int tc, num;
    cin >> tc;

    while (tc--) {
        cin >> num;

        cout << dp[num] << "\n";
    }
}