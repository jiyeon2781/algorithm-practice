#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, p;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        cin >> p;
        string resultName = "", currentName;
        int maxPrice = 0, currentPrice;
        for (int j = 0; j < p; j++) {
            cin >> currentPrice >> currentName;
            if (currentPrice > maxPrice) {
                maxPrice = currentPrice;
                resultName = currentName;
            }
        }
        cout << resultName << "\n";
    }

    return 0;
}

