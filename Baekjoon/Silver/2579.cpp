#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 301;

int score[MaxSize];
int dp[MaxSize][3];
// [현재 계단 위치][연속으로 밟은 계단의 개수 -> 1, 2만 사용]

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) 
        cin >> score[i];

    dp[1][1] = score[1];
    dp[2][1] = score[2];
    dp[2][2] = score[2] + score[1];

    for (int i = 2; i <= N; i++) {
        dp[i][1] = max(dp[i - 2][1], dp[i-2][2]) + score[i];
        dp[i][2] = dp[i - 1][1] + score[i];
    }

    cout << max(dp[N][1], dp[N][2]);
}