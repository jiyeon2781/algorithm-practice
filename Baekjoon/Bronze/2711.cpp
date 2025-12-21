#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;

    int idx;
    string str;
    while (tc--) {
        cin >> idx >> str;
        cout << str.substr(0, idx-1) + str.substr(idx, str.size() - idx) << "\n";
    }
    
    return 0;
}