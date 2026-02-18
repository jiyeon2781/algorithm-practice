#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> alphabets = { 'a', 'e', 'i', 'o', 'u' };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    while (true) {
        getline(cin, str);

        if (str == "#")
            break;

        int cnt = 0;
        for (char ch : str) {
            if (find(alphabets.begin(), alphabets.end(), tolower(ch)) != alphabets.end()) {
                cnt += 1;
            }
        }

        cout << cnt << "\n";
    }

    return 0;
}
