#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    priority_queue<int, vector<int>, greater<int>> humans;
    int N, num;

    cin >> N;
    while (N--) {
        cin >> num;
        humans.push(num);
    }

    int end = 0, result = 0;

    while (!humans.empty()) {
        end += humans.top();
        result += end;
        humans.pop();
    }
    cout << result;
}