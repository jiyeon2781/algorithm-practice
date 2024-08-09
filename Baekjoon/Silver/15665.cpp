#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Backtracking(int depth, int M);

vector<int> nums;
vector<int> result;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, input;

    cin >> N >> M;

    while (N--) {
        cin >> input;
        nums.push_back(input);
    }
    sort(nums.begin(), nums.end());

    Backtracking(0, M);
}

void Backtracking(int depth, int M) {
    if (depth == M) {
        for (auto element : result) cout << element << ' ';
        cout << "\n";
        return;
    }

    int prev = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (prev == nums[i]) continue;

        result.push_back(nums[i]);
        prev = nums[i];
        int idx = result.size() - 1;

        Backtracking( depth + 1, M);
        result.erase(result.begin() + idx);
    }
}
