#include <iostream>
#include <algorithm>

using namespace std;

void Backtracking(int idx, int N);
int CountBrokenEggs(int N);

const int MaxSize = 9;

pair<int, int> eggs[MaxSize];
int result = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> eggs[i].first >> eggs[i].second;
    }

    Backtracking(0, N);

    cout << result;
}

void Backtracking(int idx, int N) {
    if (idx == N) {
        result = max(CountBrokenEggs(N), result);
        return;
    }

    if (eggs[idx].first <= 0 || CountBrokenEggs(N) == N-1) {
        // 내 계란이 깨졌거나, 내 계란 빼고 모두 깨졌을 때
        Backtracking(idx + 1, N);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (i == idx || eggs[i].first <= 0) continue;
        // 나 자신이거나 상대 계란이 이미 깨져있을 때

        eggs[i].first -= eggs[idx].second;
        eggs[idx].first -= eggs[i].second;

        Backtracking(idx + 1, N);

        eggs[i].first += eggs[idx].second;
        eggs[idx].first += eggs[i].second;
    }
}

int CountBrokenEggs(int N) { // 깨진 계란의 개수
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (eggs[i].first <= 0) cnt += 1;
    }
    return cnt;
}