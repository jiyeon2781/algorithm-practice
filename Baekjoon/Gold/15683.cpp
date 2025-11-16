#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int Dir = 4;
const int Max = 9;

void Start(int depth, int max);
void InitMap(int first[Max][Max], int second[Max][Max]);
void Draw(pair<int, int> start, int dir, bool isReturn, int depth); 
void Init();
int Count();

vector<vector<vector<int>>> lists =
{
    {{}},
    {{0}, {1}, {2}, {3}},
    {{0, 2}, {1, 3}},
    {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0},{3, 0, 1}},
    {{0, 1, 2, 3}}
};
// 1, 2, 3, 4, 5 CCTV Count

int dirX[Dir] = { -1, 0, 1, 0 };
int dirY[Dir] = { 0, 1, 0, -1 };
// 위, 오른쪽, 아래, 왼쪽

int map[Max][Max];
int temp[Max][Max];
int cctvIdx[Max][Max];

int N, M, result = 100;

vector<pair<int, int>> cctv;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] >= 1 && map[i][j] <= 5) {
                cctv.push_back({i,j});
            }
        }
    }

    Init();
    InitMap(temp, map);
    Start(0, cctv.size());
    cout << result;
    return 0;
}

void Start(int depth, int max) {
    if (depth == max) {
        // 계산 후 사각지대 값 갱신
        int cur = Count();
        if (cur < result) result = cur;
        return;
    }

    int size = lists[map[cctv[depth].first][cctv[depth].second]].size();
    int curIdx = map[cctv[depth].first][cctv[depth].second];

    for (int i = 0; i < size; i++) {
        // Backtracking
        for (int k = 0; k < lists[curIdx][i].size(); k++) {
            Draw({ cctv[depth].first, cctv[depth].second }, lists[curIdx][i][k], false, depth);
        }
        Start(depth + 1, max);
        for (int k = 0; k < lists[curIdx][i].size(); k++) {
            Draw({ cctv[depth].first, cctv[depth].second }, lists[curIdx][i][k], true, depth);
        }
    }
}

void InitMap(int first[Max][Max], int second[Max][Max]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            first[i][j] = second[i][j];
       }
    }
}

void Init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cctvIdx[i][j] = 0;
        }
    }
}

//temp를 기준으로 해당 방향으로 맵 draw
void Draw(pair<int, int> start, int dir, bool isReturn, int depth) {
    pair<int, int> cur = start;
    int idx = map[start.first][start.second];

    while (true) {
        pair<int, int> next = { cur.first + dirX[dir], cur.second + dirY[dir] };

        if (next.first >= N || next.first < 0 || next.second >= M || next.second < 0)
            break;
        if (temp[next.first][next.second] == 6)
            break;

        if (temp[next.first][next.second] == 0 && !isReturn && cctvIdx[next.first][next.second] == 0) {
            temp[next.first][next.second] = idx;
            cctvIdx[next.first][next.second] = depth + 1;

        }
        else if (temp[next.first][next.second] == idx && isReturn && cctvIdx[next.first][next.second] == depth + 1) {
            temp[next.first][next.second] = 0;
            cctvIdx[next.first][next.second] = 0;
        }

        cur = next;
    }
}

int Count() {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (temp[i][j] == 0)
                cnt += 1;
        }
    }
    return cnt;
}