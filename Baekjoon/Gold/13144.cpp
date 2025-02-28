#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 100001;

int numCnt[MaxSize];

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

    int start = 0, end = 0;
    long long result = 0;
    for (start = 0; start < N; start++) {
        while (end < N && numCnt[nums[end]] == 0) numCnt[nums[end++]] += 1;
        result += (end - start);
        numCnt[nums[start]] -= 1;
    }
    cout << result;
}