#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int num;
    int cnt;
};

int Calculate(int cur, bool isRow);
int CurrentRowCalculate(int row, int curCnt);
int CurrentColumnCalculate(int column, int curCnt);

const int MaxSize = 101;

int map[MaxSize][MaxSize];

int r, c, k;

bool compare(Info a, Info b) {
    if (a.cnt == b.cnt)
        return a.num < b.num;
    return a.cnt < b.cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> r >> c >> k;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> map[i][j];
        }
    }

    int resultTime = 0, curR = 3, curC = 3;
    while (resultTime <= 100) {
        if (map[r][c] == k)
            break;

        if (curR >= curC) {
            // R 연산
            curC = Calculate(curR, true);
        }
        else {
            // C 연산
            curR = Calculate(curC, false);
        }


        resultTime += 1;
    }

    if (resultTime > 100)
        cout << "-1";
    else
        cout << resultTime;

    return 0;
}


int Calculate(int cur, bool isRow) {
    int maxCnt = 0;
    for (int i = 1; i <= cur; i++) {
        int cnt = isRow ? CurrentRowCalculate(i, cur) : CurrentColumnCalculate(i, cur);
        maxCnt = max(cnt, maxCnt);
    }
    return maxCnt;
}

int cnt[MaxSize];
int CurrentRowCalculate(int row, int curCnt) {
    fill(cnt, cnt + MaxSize, 0);

    for (int i = 1; i <= curCnt; i++) {
        if (map[row][i] == 0)
            continue;
        cnt[map[row][i]] += 1;
    }

    vector<Info> vec;
    for (int i = 1; i < MaxSize; i++) {
        if (cnt[i] == 0)
            continue;
        vec.push_back({ i, cnt[i] });
    }
    sort(vec.begin(), vec.end(), compare);

    int curIdx = 1;

    for (int i = 1; i <= vec.size(); i++) {
        if (curIdx >= MaxSize)
            break;
        map[row][curIdx++] = vec[i - 1].num;
        map[row][curIdx++] = vec[i - 1].cnt;
    }

    for (int i = curIdx; i < MaxSize; i++) {
        map[row][i] = 0;
    }

    return curIdx - 1;
}

int CurrentColumnCalculate(int column, int curCnt) {
    fill(cnt, cnt + MaxSize, 0);

    for (int i = 1; i <= curCnt; i++) {
        if (map[i][column] == 0)
            continue;
        cnt[map[i][column]] += 1;
    }

    vector<Info> vec;
    for (int i = 1; i < MaxSize; i++) {
        if (cnt[i] == 0)
            continue;
        vec.push_back({ i, cnt[i] });
    }
    sort(vec.begin(), vec.end(), compare);

    int curIdx = 1;

    for (int i = 1; i <= vec.size(); i++) {
        if (curIdx >= MaxSize)
            break;
        map[curIdx++][column] = vec[i - 1].num;
        map[curIdx++][column] = vec[i - 1].cnt;
    }

    for (int i = curIdx; i < MaxSize; i++) {
        map[i][column] = 0;
    }

    return curIdx - 1;
}

