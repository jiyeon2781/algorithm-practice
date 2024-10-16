#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1001;
int dp[MaxSize][3];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    int r, g, b;

    cin >> r >> g >> b;
    
    dp[0][0] = r;
    dp[0][1] = g;
    dp[0][2] = b;

    for (int i = 1; i < N; i++) {
        cin >> r >> g >> b;
        dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + r;
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + g;
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + b;
    }

    int result = dp[N-1][0];
    for (int i = 1; i < 3; i++) {
        if (result > dp[N - 1][i]) result = dp[N - 1][i];
    }
    cout << result;
}