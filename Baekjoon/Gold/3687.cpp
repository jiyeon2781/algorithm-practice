#include <iostream>
#include <algorithm>

#define MAX_COUNT 101

using namespace std;

long long dp[MAX_COUNT] = { 0, 0, 1, 7, 4, 2, 6, 8, 10 };
int fireStickArray[6] = {1, 7, 4, 2, 0, 8};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int tc, n;
    string max;
    cin >> tc;

    // dynamic programming
    for (int i = 9; i < MAX_COUNT; i++) {
        for (int j = 2; j <= 7; j++) {
            long long cur = (dp[i - j] * 10) + fireStickArray[j - 2];
            j == 2 ? (dp[i] = cur) : (dp[i] = min(dp[i], cur));
            // 성냥개비 2 ~ 7 범위에서 최솟값 계산
        }
    }

    while (tc--)
    {
        cin >> n;

        max = "";

        // greedy algorithm
        for (int i = 0; i < n / 2; i++) max += "1";

        if (n % 2 == 1)
            max[0] = '7';
        // 최댓값 : 7,1로만 이루어짐 -> 자릿수가 많을수록 큰 숫자이므로

        cout << dp[n] << ' ' << max << "\n";
    }
}