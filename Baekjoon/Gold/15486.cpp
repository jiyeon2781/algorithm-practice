#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 1500001;
int dp[MaxSize];


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<pair<int, int>> plan;
    int t, p;
    plan.push_back({ 0, 0 });

    for (int i = 1; i <= N; i++) {
        cin >> t >> p;
        plan.push_back({ t, p });
    }

    for (int i = 1; i <= N; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
        // 현재 날짜 최댓값 갱신
        if (i + plan[i].first > N + 1) continue; 
        // 기간이 지나면 continue
        dp[i + plan[i].first - 1] = max(dp[i - 1] + plan[i].second, dp[i + plan[i].first - 1]);
        // 상담 종료일 최댓값 갱신
    }

    cout << dp[N];
}