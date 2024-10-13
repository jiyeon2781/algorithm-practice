#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int BinarySearch(int start,int end, int value, vector<int>& nums);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> nums;
    int N, num;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> num;
        nums.push_back(num);
    }

    vector<int> sortedNums(nums);
    sort(sortedNums.begin(), sortedNums.end());
    sortedNums.erase(unique(sortedNums.begin(), sortedNums.end()), sortedNums.end());
    // 정렬 및 중복 제거

    for (auto element : nums) 
        cout << BinarySearch(0, sortedNums.size() - 1, element, sortedNums) << ' ';
}

int BinarySearch(int start, int end, int value, vector<int>& nums) {
    while (start <= end) {
        int mid = (start + end) / 2;
        if (value == nums[mid]) return mid;
        else if (value > nums[mid]) start = mid + 1;
        else end = mid - 1;
    }
    return -1;
}