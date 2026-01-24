#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 10;
const int MaxInningCnt = 51;

void Backtracking(int depth);
int Score();
int PopCount(int x);

bool isSelected[MaxSize];
int nums[MaxInningCnt][MaxSize];
vector<int> order;

int N, result = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 1; j < MaxSize; j++) {
            cin >> nums[i][j];
        }
    }

    Backtracking(0);

    cout << result;
    return 0;
}


void Backtracking(int depth) {
    if (depth == MaxSize - 1) {
        int cur = Score();
        result = max(cur, result);
        return;
    }

    if (depth == 3)
    {
        isSelected[1] = true;
        order.push_back(1);
        Backtracking(depth + 1);
        order.pop_back();
        isSelected[1] = false;
    }
    else {
        for (int i = 1; i < MaxSize; i++) {
            if (isSelected[i] || i == 1)
                continue;

            isSelected[i] = true;
            order.push_back(i);
            Backtracking(depth + 1);
            order.pop_back();
            isSelected[i] = false;
        }
    }
    
}

int Score() {
    int out = 0, score = 0, bases = 0, curInning = 0, cur = 0;

    while (curInning < N) {
        int afterBall = nums[curInning][order[cur]];

        if (afterBall == 0) {
            out += 1;

            if (out >= 3) {
                out = 0;
                bases = 0;
                curInning += 1;
            }
        }
        else if (afterBall == 4) {
            score += PopCount(bases) + 1;
            bases = 0;
        }
        else {
            bases |= 1;
            bases <<= afterBall;

            int runs = bases >> 4;
            score += PopCount(runs);
            bases &= 14;
        }

        cur = (cur + 1) % (MaxSize - 1);
    }
    
    return score;
}

int PopCount(int x) {
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}