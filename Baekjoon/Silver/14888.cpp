#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void Backtracking(int depth, int value, int maxDepth);
int Cal(int oper, int num, int value);

const int MaxSize = 12;
const int MaxOperCnt = 4;

int N;
int nums[MaxSize];
int cnt[MaxOperCnt];
int minNum = 1000000001, maxNum = -1000000001;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < MaxOperCnt; i++) {
        cin >> cnt[i];
    }

    Backtracking(1, nums[0], N);
    cout << maxNum << "\n" << minNum;

    return 0;
}

void Backtracking(int depth, int value, int maxDepth) {
    if (depth == maxDepth) {
        minNum = min(value, minNum);
        maxNum = max(value, maxNum);
        return;
    }

    for (int i = 0; i < MaxOperCnt; i++) {
        if (cnt[i] <= 0)
            continue;
        cnt[i] -= 1;
        int result = Cal(i, nums[depth], value);
        // 연산자 우선순위 상관없이 계산 진행
        Backtracking(depth + 1, result, maxDepth);
        cnt[i] += 1;
        
    }
}

int Cal(int oper, int num, int value) {
    switch (oper) {
    case 0:
        return value + num;
    case 1:
        return value - num;
    case 2:
        return value * num;
    case 3:
        return value / num;
    }
}