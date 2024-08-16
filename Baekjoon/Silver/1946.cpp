#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int tc, N, cnt = 1;
    cin >> tc;
    pair<int, int> grade;
    vector<pair<int, int>> lists;

    while (tc--) {
        cin >> N;

        lists.clear();
        cnt = 1;

        while (N--) {
            cin >> grade.first >> grade.second;
            lists.push_back(grade);
        }

        sort(lists.begin(), lists.end(), compare);

        int maxInterviewScore = lists[0].second;

        for (int i = 1; i < lists.size(); i++) {
            if (lists[i].second < maxInterviewScore) {
                maxInterviewScore = lists[i].second;
                cnt += 1;
            }
        }

        cout << cnt << "\n";
    }
}