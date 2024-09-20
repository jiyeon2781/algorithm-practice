#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num, sum = 0, minNum = 100;
    for (int i = 0; i < 7; i++) {
        cin >> num;
        if (num % 2 == 0) continue;
        sum += num;
        if (minNum > num) minNum = num;
    }
    
    if (sum == 0) cout << "-1";
    else cout << sum << "\n" << minNum;
} 