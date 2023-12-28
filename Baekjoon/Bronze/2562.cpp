#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int maxNum = 0, maxIdx = 0;
    int curNum;
    for (int i = 1; i < 10; i++) {
        cin >> curNum;
        if (maxNum > curNum) continue;
        maxNum = curNum;
        maxIdx = i;
    }
    cout << maxNum << "\n" << maxIdx << "\n";

    return 0;
}