#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 101;

long long dp[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int T, num;
    cin >> T;
    dp[1] = 1, dp[2] = 1, dp[3] = 1;
    for (int i = 4; i < MaxSize; i++) 
        dp[i] = dp[i - 2] + dp[i - 3];

    while (T--) {
        cin >> num;
        cout << dp[num] << "\n";
    }
}
