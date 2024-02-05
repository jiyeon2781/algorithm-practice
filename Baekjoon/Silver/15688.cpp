#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, num;
    vector<int> numbers;
    cin >> N;

    while (N--) {
        cin >> num;
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());

    for (int element : numbers) cout << element << "\n";

    return 0;
}