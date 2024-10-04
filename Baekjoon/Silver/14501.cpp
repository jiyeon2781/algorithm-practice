#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 16;
int dp[MaxSize];
pair<int, int> work[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> work[i].first >> work[i].second;

    for (int i = N; i >= 1; i--) { // 역순
        if (i + work[i].first - 1 >= N + 1) {
            dp[i] = dp[i + 1];
            continue;
        }
        // 기간이 넘는다면 continue;
        dp[i] = max(dp[i+1], work[i].second + dp[i + work[i].first]);
    }
    cout << dp[1];
}