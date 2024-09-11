#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 91;
long long dp[MaxSize][2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    dp[1][1] = 1;
    for (int i = 2; i <= N; i++) { // 2 ~ N 까지 자리수
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1]; // 일의 자리 기준 이전 i의 0의 개수
        dp[i][1] = dp[i - 1][0]; // 일의 자리 기순 이전 i의 1의 개수
    }
    cout << dp[N][0] + dp[N][1];
}
