#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 41;

int dp[MaxSize];
// 좌석 개수 당 나오는 경우의 수
// example> 1좌석 = 1, 2좌석 = 2, 3좌석 = 3, 4좌석 = 5 ...

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, vip, num;
    cin >> N >> vip;

    vector<int> vips;
    for (int i = 0; i < vip; i++) {
        cin >> num;
        vips.push_back(num);
    }
    
    int result = 1;

    dp[0] = 1; // 0명이 앉게 되었을 때 0으로 지정하면 곱셈으로 인해 결과값이 0이 됨
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= N; i++) dp[i] = dp[i - 1] + dp[i - 2];
    
    int start = 1;
    bool isEndNum = false;

    // vip 단위로 좌석을 끊어서 경우의 수 합계를 구함
    for (auto vipNum : vips) {
        result *= dp[vipNum - start];
        start = vipNum + 1;
        if (vipNum == N) isEndNum = true;
    }
    if (!isEndNum) result *= dp[N - start + 1];
    cout << result;
}