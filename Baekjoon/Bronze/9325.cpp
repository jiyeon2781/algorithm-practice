#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, carPrice, optionCount;
    int currentOptionCount, currentOptionPrice;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        cin >> carPrice >> optionCount;
        for (int j = 0; j < optionCount; j++) {
            cin >> currentOptionCount >> currentOptionPrice;
            carPrice += currentOptionCount * currentOptionPrice;
        }
        cout << carPrice << "\n";
    }

    return 0;
}