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

    vector<int> nums;
    vector<int> visited(N, false);
    for (int i = 0; i < N; i++) {
        cin >> num;
        nums.push_back(num);
    }

    sort(nums.begin(), nums.end());

    int result = 0, idx = 0;
    for (int i = 0; i < N; i += 2) {
        if (i + 1 == N) {
            if (!visited[i]) {
                result += nums[i];
                visited[i] = true;
            }
            break;
        }

        if (nums[i] > 0 || nums[i + 1] > 0) {
            if (nums[i] > 0) idx = i;
            else if (nums[i + 1] > 0) {
                idx = i + 1;
                if (!visited[i]) {
                    result += nums[i];
                    visited[i] = true;
                }
            }
            break;
        }

        visited[i] = true;
        visited[i + 1] = true;
        int cur = nums[i] * nums[i + 1];
        int cur2 = nums[i] + nums[i + 1];
        result += cur > cur2 ? cur : cur2;
    }

    for (int i = N - 1; i >= idx; i -= 2) {
        if (i == idx) {
            if (!visited[i]) result += nums[i];
            break;
        }

        if (nums[i] < 0 || nums[i - 1] < 0) {
            if (!visited[i]) result += nums[i];
            if (!visited[i - 1]) result += nums[i - 1];
            break;
        }

        if (visited[i] || visited[i - 1]) continue;
        int cur = nums[i] * nums[i - 1];
        int cur2 = nums[i] + nums[i - 1];
        result += cur > cur2 ? cur : cur2;
    }

    cout << result;
}