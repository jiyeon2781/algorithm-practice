#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 501;

int triangle[MaxSize][MaxSize];
int dp[MaxSize][MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) 
            cin >> triangle[i][j];
    }

    dp[0][0] = triangle[0][0];
    int result = dp[0][0];

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j <= i && triangle[i][j] + dp[i - 1][j] > dp[i][j]) dp[i][j] = triangle[i][j] + dp[i - 1][j]; // triangle[i][j] 기준 우측 대각선 위
            if (j >= 1 && triangle[i][j] + dp[i - 1][j - 1] > dp[i][j]) dp[i][j] = triangle[i][j] + dp[i - 1][j - 1]; // triangle[i][j] 기준 좌측 대각선 위
            if (dp[i][j] > result) result = dp[i][j];
        }
    }

    cout << result;
}
