#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxCount = 101;
const int MaxWeight = 100001;

int dp[MaxCount][MaxWeight];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;

    vector<pair<int, int>> items(1);
    
    int W, V;
    for (int i = 0; i < N; i++) {
        cin >> W >> V;
        items.push_back({ W, V });
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            if (items[i].first > j) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j - items[i].first] + items[i].second, dp[i - 1][j]);
        }
    }
    cout << dp[N][K];
}