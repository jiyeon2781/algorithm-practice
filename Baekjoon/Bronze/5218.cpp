#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string start, end;
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> start >> end;
        cout << "Distances: ";
        for (int i = 0; i < start.size(); i++) {
            int num = end[i] - start[i];
            if (num < 0) num += 26;
            cout << num << ' ';
        }
        cout << "\n";
    }
    
    return 0;
}