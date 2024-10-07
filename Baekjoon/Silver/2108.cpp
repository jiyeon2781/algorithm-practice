#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

int Average(int sum);
int Middle();
int Mode();
int Range();

vector<int> nums;
map<int, int> cnt;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, num, sum = 0;
    cin >> N;

    while (N--) {
        cin >> num;
        sum += num;
        cnt[num] += 1;
        nums.push_back(num);
    }

    sort(nums.begin(), nums.end());

    cout << Average(sum) << "\n"; // 산술 평균
    cout << Middle() << "\n"; // 중앙값
    cout << Mode() << "\n"; // 최빈값
    cout << Range() << "\n"; // 범위
}

int Average(int sum) {
    double aver = (double) sum / (double) nums.size();
    return aver != 0 ? round(aver) : aver;
}

int Middle() {
    return nums[nums.size() / 2];
}

int Mode() {
    int max = 0;
    vector<int> idx;

    for (auto element : cnt) {
        if (element.second >= max) {
            if (element.second > max) {
                max = element.second;
                idx.clear();
            }
            idx.push_back(element.first);
        }
    }

    sort(idx.begin(), idx.end());

    if (idx.size() == 1) return idx[0];
    else return idx[1];
}

int Range() {
    return nums[nums.size() - 1] - nums[0];
}