#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<long long> numbers;
    string num;
    for (int i = 0; i < N; i++) {
        cin >> num;
        reverse(num.begin(), num.end());
        numbers.push_back(stoll(num));
    }

    sort(numbers.begin(), numbers.end());
    for (int i = 0; i < N; i++) {
        cout << numbers[i] << "\n";
    }
    return 0;
}