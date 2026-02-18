#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isBallHere[4];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M;
    cin >> M;

    isBallHere[1] = true;
    int a, b;

    while (M--) {
        cin >> a >> b;
        bool temp = isBallHere[a];
        isBallHere[a] = isBallHere[b];
        isBallHere[b] = temp;
    }

    for (int i = 1; i <= 3; i++) {
        if (isBallHere[i]) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << "-1\n";

    return 0;
}
