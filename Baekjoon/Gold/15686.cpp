#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

void MinDistance(int depth, int idx ,int M);
int CalDistance(pair<int, int> h, pair<int, int> chick);

const int MaxSize = 51;

bool visited[MaxSize][MaxSize];

vector<pair<int, int>> chicken;
vector<pair<int, int>> home;

int result = 10000000;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, cur;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> cur;
            if (cur == 2) chicken.push_back({ i, j });
            else if (cur == 1) home.push_back({ i, j });
        }
    }

    MinDistance(0, 0, M);
    cout << result;
}

int CalDistance(pair<int, int> h, pair<int, int> chick) {
    return abs(h.first - chick.first) + abs(h.second - chick.second);
}

vector<pair<int, int>> afterChick;

void MinDistance(int depth, int idx, int M) { // backtracking
    if (depth == M) {
        int curSum = 0, minDist = 0;
        for (auto curHome : home) {
            minDist = 10000000;
            for (auto curChick : afterChick) {
                int cal = CalDistance(curHome, curChick);
                if (cal < minDist) minDist = cal;
            }
            curSum += minDist;
        }

        if (curSum < result) result = curSum;
        return;
    }

    for (int i = idx; i < chicken.size() ;i++) {
        if (visited[chicken[i].first][chicken[i].second]) continue;
        visited[chicken[i].first][chicken[i].second] = true;
        afterChick.push_back({ chicken[i].first , chicken[i].second });
        MinDistance(depth + 1, i + 1, M);
        afterChick.pop_back();
        visited[chicken[i].first][chicken[i].second] = false;
    }
}