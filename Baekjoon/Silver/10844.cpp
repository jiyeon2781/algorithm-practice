#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 101;
const int NumSize = 10;
const int modNum = 1000000000; // 오버플로 방지를 위한 mod
long long dp[MaxSize][NumSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;

    for (int i = 1; i < NumSize; i++) dp[1][i] = 1;
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < NumSize; j++) {
            if (j != 0) dp[i][j - 1] = (dp[i-1][j] + dp[i][j - 1]) % modNum;
            if (j != 9) dp[i][j + 1] = (dp[i-1][j] + dp[i][j + 1]) % modNum;
        }
    }

    int result = 0;
    for (int i = 0; i < NumSize; i++) 
        result = (result + dp[N][i]) % modNum;
    cout << result;
}