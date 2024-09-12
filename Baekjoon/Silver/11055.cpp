#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1001;

int dp[MaxSize];
int nums[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, result = 0;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> nums[i];

        if (i == 1) {
            dp[i] = nums[i];
            result = nums[i];
            continue;
        }

        for (int j = i - 1; j >= 1; j--) {
            if (nums[j] < nums[i] && dp[i] < dp[j]) // 이전 값 중 현재 숫자보다 작으면서 합이 저장된 값보다 클 때
                dp[i] = dp[j];
        }

        dp[i] += nums[i];

        if (result < dp[i]) result = dp[i];
    }

    cout << result;
}