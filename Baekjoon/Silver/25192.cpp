#include <iostream>
#include <algorithm>
#include <set>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, result = 0;
    string str;
    set<string> chatHash;

    cin >> N;
    while (N--) {
        cin >> str;

        if (str == "ENTER") {
            result += chatHash.size();
            chatHash.clear();
            continue;
        }

        chatHash.insert(str);
    }

    result += chatHash.size();
    cout << result;
}