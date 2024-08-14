#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, cnt = 0; // stack 대신 count를 통해 구현
    string str, result = "YES";
    cin >> tc;
    while (tc--) {
        cin >> str;

        result = "YES";
        cnt = 0;

        for (char ch : str) {
            if (ch == '(') cnt += 1;
            else if (ch == ')') {
                if (cnt > 0) cnt -= 1;
                else {
                    result = "NO";
                    break;
                }
            }
        }

        if (cnt != 0) result = "NO";
        cout << result << "\n";
    }
}