#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> nums;
    int num, sum = 0;
    for (int i = 0; i < 5; i++) {
        cin >> num;
        nums.push_back(num);
        sum += num;
    }
    sort(nums.begin(), nums.end());

    cout << sum / 5 << "\n" << nums[2];
} 