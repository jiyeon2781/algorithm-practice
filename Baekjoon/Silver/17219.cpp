#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    map<string, string> pwList;
    vector <string> splitPw;
    string pw, site;
    while (N--) {
        cin >> site >> pw;
        pwList[site] = pw;
    }

    while (M--) {
        cin >> site;
        cout << pwList[site] << "\n";
    }

    return 0;
}