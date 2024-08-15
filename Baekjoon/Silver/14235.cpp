#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num, present;
    cin >> N;

    priority_queue<int> presents;
    
    while (N--) {
        cin >> num;

        if (num != 0) {
            for (int i = 0; i < num; i++) {
                cin >> present;
                presents.push(present);
            }
            continue;
        }

        if (presents.empty()) cout << "-1\n";
        else {
            cout << presents.top() << "\n";
            presents.pop();
        }
    }
}