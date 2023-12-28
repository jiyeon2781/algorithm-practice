#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, currentNum, resultNum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> currentNum;
        if (i == n - 1) resultNum += currentNum;
        else resultNum += (currentNum - 1);
    }

    cout << resultNum << "\n";

    return 0;
}