#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Memorization();
void Print(int a, int b, int c, int result);

const int MaxSize = 21;

int dp[MaxSize][MaxSize][MaxSize];


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c;

    Memorization();

    while (true) {
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) break;
        if (a <= 0 || b <= 0 || c <= 0) Print(a, b, c, 1);
        else if (a > 20 || b > 20 || c > 20) Print(a, b, c, dp[20][20][20]);
        else Print(a, b, c, dp[a][b][c]);
    }
}

void Memorization() {
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            dp[0][i][j] = 1;
            dp[i][0][j] = 1;
            dp[i][j][0] = 1;
        }
    }

    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            for (int k = 1; k < MaxSize; k++) {
                if (i < j && j < k) dp[i][j][k] = dp[i][j][k - 1] + dp[i][j - 1][k - 1] - dp[i][j - 1][k];
                else dp[i][j][k] = dp[i - 1][j][k] + dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1] - dp[i - 1][j - 1][k - 1];
            }
        }
    }
}

void Print(int a, int b, int c, int result) {
    cout << "w(" << a << ", " << b << ", " << c << ") = " << result << "\n";
}