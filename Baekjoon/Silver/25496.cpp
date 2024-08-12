#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int P, N, jewelry;
    vector<int> jewelries;

    cin >> P >> N;
    while (N--) {
        cin >> jewelry;
        jewelries.push_back(jewelry);
    }

    sort(jewelries.begin(), jewelries.end());

    int cnt = 0;
    for (auto element : jewelries) {
        if (P >= 200) break;
        cnt += 1;
        P += element;
    }

    cout << cnt;
}