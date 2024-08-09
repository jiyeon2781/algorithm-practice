#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM 9

using namespace std;

void Backtracking(int index, int depth, int M);

vector<int> nums;
vector<int> result;
vector<bool> existIdx(MAX_NUM, false);

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

    Backtracking(0, 0, M);
}  

void Backtracking(int index, int depth, int M) {
    if (depth == M) {
        for (auto element : result) cout << element << ' ';
        cout << "\n";
        return;
    }

    int prev = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (existIdx[i] || prev == nums[i] || nums[index] > nums[i]) continue;
        // nums[index] > nums[i] : 비내림차순을 위한 조건

        result.push_back(nums[i]);
        prev = nums[i];
        int idx = result.size() - 1;
        existIdx[i] = true;

        Backtracking(i, depth + 1, M);
        result.erase(result.begin() + idx);
        existIdx[i] = false;
    }
}
