#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num;
    cin >> N;
    string input;
    queue<int> que;

    while (N--) {
        cin >> input;
        if (input == "push") {
            cin >> num;
            que.push(num);
        }
        else if (input == "pop") {
            if (que.empty()) cout << "-1\n";
            else {
                cout << que.front() << "\n";
                que.pop();
            }
        }
        else if (input == "size") cout << que.size() << "\n";
        else if (input == "empty") que.empty() ? cout << "1\n" : cout << "0\n";
        else if (input == "front") que.empty() ? cout << "-1\n" : cout << que.front() << "\n";
        else if (input == "back") que.empty() ? cout << "-1\n" : cout << que.back() << "\n";
    }
}