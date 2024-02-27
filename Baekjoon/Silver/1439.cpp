#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int countZero = 0, countOne = 0;
    string num;
    cin >> num;
    char prevChar = '2';
    for (char ch : num) {
        if (prevChar == ch) continue;

        if (ch == '1') {
            countOne += 1;
            prevChar = '1';
        }
        else if (ch == '0') {
            countZero += 1;
            prevChar = '0';
        }
    }
    cout << min(countOne, countZero);
    return 0;
}
