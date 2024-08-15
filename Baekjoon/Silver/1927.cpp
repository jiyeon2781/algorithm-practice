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
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cin >> N;
    while (N--) {
        cin >> num;

        if (num == 0) {
            if (minHeap.empty()) cout << "0\n";
            else {
                cout << minHeap.top() << "\n";
                minHeap.pop();
            }
        }
        else minHeap.push(num);
    }
}