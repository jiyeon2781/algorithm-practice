#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, number, result = 0;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> numbers;
    for (int i = 0; i < n; i++) {
        cin >> number;
        numbers.push(number);
    }

    while (numbers.size() >= 2) {
        int num1 = numbers.top();
        numbers.pop();
        int num2 = numbers.top();
        numbers.pop();
        int curSum = num1 + num2;
        result += curSum;
        numbers.push(curSum);
    }

    cout << result << "\n";
    return 0;
}