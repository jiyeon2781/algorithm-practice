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
    priority_queue<int> numbers;
    cin >> N;

    while (N--) {
        cin >> num;
        numbers.push(num);
    }

    while (!numbers.empty()) {
        cout << numbers.top() << "\n";
        numbers.pop();
    }

    return 0;
}
