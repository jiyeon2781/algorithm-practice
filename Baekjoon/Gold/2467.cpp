#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define MAX_NUM 2000000001

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, number;
    cin >> N;
    vector<int> numbers;
    for (int i = 0; i < N; i++) {
        cin >> number;
        numbers.push_back(number);
    }

    int start = 0, end = N-1, curSum = 0;
    int result[2], minNum = MAX_NUM;

    while (start < end) {
        curSum = numbers[start] + numbers[end];
        if (abs(minNum) > abs(curSum)) {
            result[0] = numbers[start];
            result[1] = numbers[end];
            minNum = curSum;
        }
        if (curSum > 0) end -= 1;
        else if (curSum < 0) start += 1;
        else if (curSum == 0) break;
    }
    sort(result, result + 2);
    cout << result[0] << ' ' << result[1];
    return 0;
}
