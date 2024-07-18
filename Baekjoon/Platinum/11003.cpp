#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    deque<pair<int, int>> deq;
    int N, L, A;
    cin >> N >> L;

    for (int i = 1; i <= N; i++)
    {
        cin >> A;

        while (!deq.empty() && deq.back().second > A) deq.pop_back(); // 현재 값보다 마지막 값이 크면 마지막 원소 제거
        if (!deq.empty() && deq.front().first < i - L + 1) deq.pop_front(); // 현재 범위를 벗어난 원소 제거

        deq.push_back({ i, A });
        cout << deq.front().second << ' ';
    }
} 