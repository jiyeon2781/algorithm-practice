#include <iostream>
#include <algorithm>

using namespace std;

const int MaxCount = 1000001;

int dp[MaxCount] = { 0, };
int traceback[MaxCount] = { 0, }; // 최솟값을 만드는 숫자를 역추적하기 위한 배열

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 2; i <= N; i++) {
        dp[i] = dp[i - 1] + 1;
        traceback[i] = i - 1;

        if (i % 3 == 0 && dp[i] > dp[i / 3] + 1) { // 3으로 나눠지고, 현재 값보다 3으로 나눈 값의 count가 작을 때
            dp[i] = dp[i / 3] + 1;
            traceback[i] = i / 3;
        }

        if (i % 2 == 0 && dp[i] > dp[i / 2] + 1) { // 2로 나눠지고, 현재 값보다 2로 나눈 값의 count가 작을 때
            dp[i] = dp[i / 2] + 1;
            traceback[i] = i / 2;
        }
    }

    cout << dp[N] << "\n";

    int cur = N;
    while (cur > 1) {
        cout << cur << ' ';
        cur = traceback[cur];
    }

    cout << 1;
}