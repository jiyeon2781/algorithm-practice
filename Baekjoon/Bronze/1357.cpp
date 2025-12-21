#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string a, b;
    cin >> a >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string result = to_string(stoi(a) + stoi(b));
    reverse(result.begin(), result.end());
    cout << stoi(result);
    
    return 0;
}