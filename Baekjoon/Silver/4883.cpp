#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int Max = 100001;
const int Col = 3;

int graph[Max][Col];
int dp[Max][Col];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, idx = 1;

    while (true) {
        cin >> N;

        if (N == 0) break;
        
        fill(graph[0], graph[0] + Max * Col, 0);
        fill(dp[0], dp[0] + Max * Col, 0);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < Col; j++) {
                cin >> graph[i][j];
            }
        }

        dp[0][0] = graph[0][1];
        dp[0][1] = graph[0][1];
        dp[0][2] = graph[0][2] + dp[0][1];

        int minNum1, minNum2;
        for (int i = 1; i < N; i++) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + graph[i][0];

            minNum1 = min(dp[i - 1][0], dp[i - 1][1]);
            minNum2 = min(dp[i - 1][2], dp[i][0]);
            dp[i][1] = min(minNum1, minNum2) + graph[i][1];

            minNum1 = min(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = min(minNum1, dp[i][1]) + graph[i][2];
        }

        cout << idx++ << ". " << dp[N - 1][1] << "\n";
    }
}