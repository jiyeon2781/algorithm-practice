#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int x;
    int y;
    int dir;
};

void Start();
int ModifyDir(int dir); 
int ReverseDir(int dir);
void SaveTaggerPath();
void MoveRunners();
void MoveRunner(int idx);
void MoveTagger(int idx);
int GrapRunners();
int GetDistance(Info runner);

const int MaxSize = 100;

vector<int> map[MaxSize][MaxSize]; // 도망자들 맵
bool tree[MaxSize][MaxSize]; // 나무 위치
vector<Info> runner = vector<Info>(1); // 도망자
vector<bool> isGraped = vector<bool>(1);
Info tagger; // 술래
vector<Info> path; // 술래 턴 전용 path

int n, m, h, k;

int dirX[4] = { -1, 1, 0, 0 };
int dirY[4] = { 0, 0, -1, 1 };
// 상, 하, 좌, 우

int result = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> h >> k;

    int x, y, d;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> d;
        int curDir = 1;
        if (d == 1) 
            curDir = 3;
        runner.push_back({ x, y, curDir });
        isGraped.push_back(false);
        map[x][y].push_back(i);
    }

    for (int i = 0; i < h; i++) {
        cin >> x >> y;
        tree[x][y] = true;
    }

    SaveTaggerPath();
    Start();

    return 0;
}

void SaveTaggerPath() {
    int sumCnt = 1, curCnt = 0, totalCnt = 0;
    Info cur = { n / 2 + 1, n / 2 + 1, 0 };
    path.push_back(cur);

    while (path.size() < n * n) {
        pair<int, int> next = { cur.x + dirX[cur.dir], cur.y + dirY[cur.dir] };
        int dir = cur.dir;

        if (curCnt == sumCnt - 1) {
            totalCnt += 1;

            if (totalCnt >= 2) {
                sumCnt += 1;
                totalCnt = 0;
            }

            curCnt = 0;
            dir = ModifyDir(dir);
        }
        else
            curCnt += 1;

        path.push_back({ next.first, next.second, dir });
        cur = { next.first, next.second, dir };
    }

    path[n * n - 1].dir = 1;

    vector<Info> reversePath = path;
    reversePath.pop_back();
    reverse(reversePath.begin(), reversePath.end());

    for (int i = 0; i < reversePath.size() - 1; i++) {
        int dr = reversePath[i + 1].x - reversePath[i].x;
        int dc = reversePath[i + 1].y - reversePath[i].y;
        if (dr == -1) reversePath[i].dir = 0;
        else if (dr == 1) reversePath[i].dir = 1;
        else if (dc == -1) reversePath[i].dir = 2;
        else if (dc == 1) reversePath[i].dir = 3;

        path.push_back(reversePath[i]);
    }
}

int ModifyDir(int dir) {
    int cur = 0;
    switch (dir) {
    case 0:
        cur = 3;
        break;
    case 1:
        cur = 2;
        break;
    case 2:
        cur = 0;
        break;
    case 3:
        cur = 1;
        break;
    }
    return cur;
}

int ReverseDir(int dir) {
    switch (dir) {
    case 0:
        return 1;
    case 1:
        return 0;
    case 2:
        return 3;
    case 3:
        return 2;
    }
    return dir;
}

void Start() {
    tagger = path[0];
    for (int i = 0; i < k; i++) {
        MoveRunners();
        MoveTagger(i);
        int cnt = GrapRunners();
        result += ((i + 1) * cnt);
    }
    cout << result;
}

void MoveRunners() {
    for (int i = 1; i <= m; i++) {
        // 술래와의 거리가 3 이하면 Move
        if (isGraped[i])
            continue;
        if (GetDistance(runner[i]) <= 3)
            MoveRunner(i);
    }
}

void MoveRunner(int idx) {
    Info cur = runner[idx];
    pair<int, int> next = { cur.x + dirX[cur.dir], cur.y + dirY[cur.dir] };
    if (next.first <= 0 || next.first > n || next.second <= 0 || next.second > n)
    {
        // dir 방향 전환
        runner[idx].dir = ReverseDir(cur.dir);
        // 다음으로 이동할 좌표 재계산
        next = { cur.x + dirX[runner[idx].dir], cur.y + dirY[runner[idx].dir] };
    }

    if (next.first == tagger.x && next.second == tagger.y)
        return;

    // 술래가 없으면 1칸 이동
    runner[idx].x = next.first;
    runner[idx].y = next.second;
    map[cur.x][cur.y].erase(find(map[cur.x][cur.y].begin(), map[cur.x][cur.y].end(), idx));
    map[next.first][next.second].push_back(idx);
}

void MoveTagger(int idx) {
    auto cur = (idx + 1) % (n * n * 2 - 2);
    tagger = path[cur];
}

int GrapRunners() {
    int cnt = 0;
    for (int i = 0; i <= 2; i++) {
        pair<int, int> next = { tagger.x + dirX[tagger.dir] * i, tagger.y + dirY[tagger.dir] * i };
        if (next.first <= 0 || next.first > n || next.second <= 0 || next.second > n)
            break;
        if (tree[next.first][next.second])
            continue;
        for (int j = 0; j < map[next.first][next.second].size(); j++) {
            int idx = map[next.first][next.second][j];
            isGraped[idx] = true;
            cnt += 1;
        }

        map[next.first][next.second].clear();
    }

    return cnt;
}

int GetDistance(Info runner) {
    return abs(tagger.x - runner.x) + abs(tagger.y - runner.y);;
}