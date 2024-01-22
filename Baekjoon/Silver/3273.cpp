#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num, x;
    cin >> N;

    vector<int> numbers;
    for (int i = 0; i < N; i++) {
        cin >> num;
        numbers.push_back(num);
    }
    cin >> x;
    int start = 0, end = N - 1, count = 0;
    sort(numbers.begin(), numbers.end());
    while (start < end) {
        int sum = numbers[start] + numbers[end];
        if (sum == x) count += 1;

        if (sum > x) end -= 1;
        else start += 1;
    }
    cout << count << "\n";
    
    return 0;
}