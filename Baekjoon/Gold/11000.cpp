#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<pair<int, int>> lists;
    int s, t;
    while (N--) {
        cin >> s >> t;
        lists.push_back({ s, t });
    }

    sort(lists.begin(), lists.end());

    priority_queue <int, vector<int>, greater<int>> que;
    for (pair<int, int> lecture : lists) {
        if (que.empty()) {
            que.push(lecture.second);
            continue;
        }
        if (que.top() <= lecture.first) que.pop();
        que.push(lecture.second);
    }

    cout << que.size(); // 강의실이 필요한 최소 개수
}