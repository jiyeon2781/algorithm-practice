#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> numbers(9, 0);
    int num;
    cin >> num;
    while (num > 0) {
        int cur = num % 10;
        if (cur == 6 || cur == 9) numbers[6] += 1;
        else numbers[cur] += 1;
        num /= 10;
    }

    if (numbers[6] % 2 == 0) numbers[6] /= 2;
    else numbers[6] = numbers[6] / 2 + 1;
    int idx = max_element(numbers.begin(), numbers.end()) - numbers.begin();
    int max = *max_element(numbers.begin(), numbers.end());
    cout << max;
    return 0;
}