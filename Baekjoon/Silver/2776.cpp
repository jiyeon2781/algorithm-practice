#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, N, M, num;
    cin >> tc;
    while (tc--) {
        cin >> N;
        set<int> notebook;
        for (int i = 0; i < N; i++) {
            cin >> num;
            notebook.insert(num);
        }

        cin >> M;
        while (M--) {
            cin >> num;
            if (notebook.find(num) == notebook.end()) cout << "0\n";
            else cout << "1\n";
        }
    }
}