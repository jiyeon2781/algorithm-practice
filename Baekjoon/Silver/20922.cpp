#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxNum = 200001;

int numCnt[MaxNum];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> nums;
    int num;

    for (int i = 0; i < N; i++) {
        cin >> num;
        nums.push_back(num);
    }

    int start = 0, end = 0, result = 0, cnt = 0;

    for (start = 0; start < N; start++) {
        while (end < N && numCnt[nums[end]] < K) { // K 이상 숫자 개수가 나왔을 때 break
            numCnt[nums[end]] += 1;
            cnt += 1;
            end += 1;
        }
        result = max(result, cnt);
        numCnt[nums[start]] -= 1;
        cnt -= 1;
    }
    cout << result;
}
