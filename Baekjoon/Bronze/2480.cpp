#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num;
    vector<int> nums;
    for (int i = 0; i < 3; i++) {
        cin >> num;
        nums.push_back(num);
    }

    sort(nums.begin(), nums.end(), greater<int>());

    int count = 1;
    for (int i = 1; i < 3; i++) {
        if (nums[i - 1] == nums[i]) {
            count += 1;
            num = nums[i];
        }
    }

    if (count == 3) cout << 10000 + (num * 1000);
    else if (count == 2) cout << 1000 + (num * 100);
    else cout << nums[0] * 100;
}