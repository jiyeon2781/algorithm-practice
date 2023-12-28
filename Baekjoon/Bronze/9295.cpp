#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, num1, num2;
    cin >> tc;
    for (int i = 1; i <= tc; i++) {
        cin >> num1 >> num2;
        cout << "Case " << i << ": " << num1 + num2 << "\n";
    }

    return 0;
}