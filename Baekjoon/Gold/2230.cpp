#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define MAX_NUM 2000000001;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, num, result = MAX_NUM;
    cin >> n >> m;
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        cin >> num;
        numbers.push_back(num);
    }

    sort(numbers.begin(), numbers.end());
    int start = 0, end = 0, currentSub = 0;
    while (end < numbers.size() && start < numbers.size()) {
        currentSub = numbers[end] - numbers[start];
        if (currentSub < m) end++;
        else if (currentSub > m) {
            if (currentSub <= result) result = currentSub;
            start++;
        }
        else if (currentSub == m) {
            result = m;
            break;
        }
    }
    cout << result << "\n";
    return 0;
}