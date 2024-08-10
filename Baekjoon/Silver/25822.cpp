#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_COUNT 100001
#define COIN_PRICE 0.99

using namespace std;

int dp[MAX_COUNT][3] = { 0, };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    float C;
    int N, cnt, maxCnt = 0, result = 0, freezeCount = 0;
    vector<int> cntDay;

    cin >> C >> N;
    
    freezeCount = min((int)(C / COIN_PRICE), 2);

    while (N--) {
        cin >> cnt;
        if (cnt > maxCnt) maxCnt = cnt;
        cntDay.push_back(cnt);
    }

    for (int i = 0; i <= freezeCount; i++) {
        if (cntDay[0] == 0 && i == 0) continue;
        dp[0][i] = 1;
    }

    for (int i = 1; i < cntDay.size(); i++) {
        if (cntDay[i] > 0) {
            for (int j = 0; j <= freezeCount; j++) {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
        else {
            for (int j = 1; j <= freezeCount; j++) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
        }
    }

    for (int i = 0; i < cntDay.size(); i++) {
        for (int j = 0; j <= freezeCount; j++) {
            result = max(result, dp[i][j]);
        }
    }
    cout << result << "\n" << maxCnt;
}