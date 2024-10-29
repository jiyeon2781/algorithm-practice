#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    map<string, bool> lists;
    set<string> result;
    string str;
    while (N--) {
        cin >> str;
        if (lists.find(str) == lists.end()) lists[str] = true;
    }

    while (M--) {
        cin >> str;
        if (lists[str]) result.insert(str);
    }

    cout << result.size() << "\n";
    for (auto element : result) {
        cout << element << "\n";
    }
}