#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 1001;
int dp[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, num;
    cin >> N;
    vector<int> nums;

    for (int i = 0; i < N; i++) {
        cin >> num;
        nums.push_back(num);
    }

    fill(dp, dp + N, 1); // 수열의 시작 count인 1로 초기화
    int result = 0;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] <= nums[j]) continue;
            // 현재 값이 이전 값들보다 작거나 같으면 continue
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    cout << *max_element(dp, dp + N);
}
