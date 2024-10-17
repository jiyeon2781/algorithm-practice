#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num;
    cin >> N;

    vector<int> nums, twoSum;

    // a + b + c = k -> a + b = k - c원리 적용
    
    for (int i = 0; i < N; i++) {
        cin >> num;
        nums.push_back(num);
    }

    sort(nums.begin(), nums.end()); // 큰 수를 바로 찾기 위해 sort

    // a + b 부분 벡터에 저장
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            twoSum.push_back(nums[i] + nums[j]); 
        }
    }

    sort(twoSum.begin(), twoSum.end());

    for (int i = N - 1; i >= 0; i--) { // nums[i] ~ nums[0]
        for (int j = 0; j < i; j++) {
            auto result = binary_search(twoSum.begin(), twoSum.end(), nums[i] - nums[j]);
            if (!result) continue;
            cout << nums[i];
            return 0;
        }
    }
}