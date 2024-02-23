#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

pair<int, long long> CompareCardNumberCount(pair<int, long long> current, pair<int, long long> result);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    long long num;
    cin >> N;
    priority_queue<long long> que;

    while (N--) {
        cin >> num;
        que.push(num);
    }

    pair<int, long long> result = { 0, 0 }; // 결과가 저장될 pair 변수
    pair<int, long long> current = { 1, que.top() }; // while문에서 사용될 현재까지의 count, num
    que.pop();

    while (!que.empty()) {
        if (current.second == que.top()) {
            current.first += 1;
            que.pop();
            continue;
        }

        result = CompareCardNumberCount(current, result);

        current = { 1, que.top() };
        que.pop();
    }

    result = CompareCardNumberCount(current, result);

    cout << result.second;

    return 0;
}

pair<int, long long> CompareCardNumberCount(pair<int, long long> current, pair<int, long long> result) {
    if (result.first < current.first) {
        result.first = current.first;
        result.second = current.second;
    }
    else if (result.first == current.first && result.second > current.second) result.second = current.second;
    return result;
}