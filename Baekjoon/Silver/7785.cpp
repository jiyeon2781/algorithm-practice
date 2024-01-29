#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string name, state;
    map<string, string, greater<string>> members;

    while (n--) {
        cin >> name >> state;
        members[name] = state;
    } 

    for (pair<string,string> member : members) {
        if (member.second == "leave") continue;
        cout << member.first << "\n";
    }
    return 0;
}
