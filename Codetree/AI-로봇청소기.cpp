#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void Start(int L);
void MoveRobots();
pair<int, int> MoveRobot(pair<int, int> start);
void Clean();
void CleanCurrentRobot(int idx);
void InitTempMap();
int Sum(int dir, pair<int, int> cur);
void AddAndSpread();
int Count();

const int MaxSize = 31;
const int MaxRobotCnt = 51;
const int Dir = 4;

vector<pair<int, int>> robots;
vector<pair<int, int>> objects;

int map[MaxSize][MaxSize];
bool isRobotHere[MaxSize][MaxSize];
int temp[MaxSize][MaxSize];

int dirX[Dir] = { 0, 1, 0, -1 };
int dirY[Dir] = { 1, 0, -1, 0 };
// 오른쪽, 아래, 왼쪽, 위

int N, K, L;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K >> L;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if (map[i][j] == -1)
                objects.push_back({ i, j });
        }
    }

    int r, c;
    while (K--) {
        cin >> r >> c;
        robots.push_back({ r, c });
    }

    Start(L);

    return 0;
}


void Start(int L) {
    while (L--) {
        MoveRobots();
        // 1. 청소기 이동

        Clean();
        // 2. 청소

        AddAndSpread();
        // 3. 먼지 축적 및 먼지 확산

        cout << Count() << "\n";
        // 4. 출력
    }
}

void MoveRobots() {
    fill(isRobotHere[0], isRobotHere[0] + MaxSize * MaxSize, false);

    // 모든 로봇 위치 먼저 마킹
    for (int i = 0; i < robots.size(); i++)
        isRobotHere[robots[i].first][robots[i].second] = true;

    // 순서대로 이동
    for (int i = 0; i < robots.size(); i++) {
        if (map[robots[i].first][robots[i].second] > 0) continue;
        isRobotHere[robots[i].first][robots[i].second] = false; // 이동 전 해제
        pair<int, int> next = MoveRobot(robots[i]);
        if (next.first == -1) {
            // 이동할 오염된 공간이 없는 경우도 고려해야 함
            isRobotHere[robots[i].first][robots[i].second] = true;
            continue;
        }
        robots[i] = next;
        isRobotHere[next.first][next.second] = true;
    }
}

int cost[MaxSize][MaxSize];
pair<int, int> MoveRobot(pair<int, int> start) {
    // 이동거리가 가장 가까운 오염된 격자로 이동
    // BFS 진행
    fill(cost[0], cost[0] + MaxSize * MaxSize, -1);
    cost[start.first][start.second] = 0;
    queue<pair<int, int>> que;
    que.push(start);
    pair<int, int> result = { -1, -1 };
    int resultCost = -1;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++)
        {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first <= 0 || next.first > N || next.second <= 0 || next.second > N)
                continue;
            if (cost[next.first][next.second] >= 0 || map[next.first][next.second] == -1)
                continue;
            if (isRobotHere[next.first][next.second])
                continue;
            // 물건, 로봇이 있거나 경계의 밖일 때 or 이미 지나왔을 때

            // 먼지가 존재하는 경우
            if (map[next.first][next.second] > 0) {
                if (result.first == -1) {
                    resultCost = cost[cur.first][cur.second] + 1;
                    result = next;
                }
                else {
                    if (resultCost > cost[cur.first][cur.second] + 1) result = next;
                    else if (resultCost == cost[cur.first][cur.second] + 1) {
                        // 가까운 격자가 여러개 일 경우 -> R 작을 수록, C 작을 수록 선택
                        // 청소기가 있거나 물건이 있으면 넘겨야 함
                        if (result.first < next.first)
                            continue;
                        if (result.first == next.first && result.second < next.second)
                            continue;
                        result = next;
                    }
                }
            }

            que.push(next);
            cost[next.first][next.second] = cost[cur.first][cur.second] + 1;

        }
    }

    return { result.first, result.second };
}

void Clean() {
    for (int i = 0; i < robots.size(); i++) {
        CleanCurrentRobot(i);
    }
}

int dirs[4][3] = { {0, 1, 3}, {0, 1, 2}, {1, 2, 3}, {0, 2, 3 } };

void CleanCurrentRobot(int idx) {
    int maxSum = 0;
    int resultDir = 0;

    for (int i = 0; i < Dir; i++) {
        int curSum = Sum(i, robots[idx]);

        if (maxSum < curSum) {
            resultDir = i;
            maxSum = curSum;
        }
    }

    pair<int, int> cur = robots[idx];
    if (map[cur.first][cur.second] > 20) map[cur.first][cur.second] -= 20;
    else map[cur.first][cur.second] = 0;

    for (int i = 0; i < 3; i++) {
        pair<int, int> next = { cur.first + dirX[dirs[resultDir][i]], cur.second + dirY[dirs[resultDir][i]] };

        if (next.first <= 0 || next.first > N || next.second <= 0 || next.second > N)
            continue;
        if (map[next.first][next.second] == -1)
            continue;


        if (map[next.first][next.second] > 20) map[next.first][next.second] -= 20;
        else map[next.first][next.second] = 0;
    }
}


int Sum(int dir, pair<int, int> cur) {
    int sum = 0;
    sum = min(20, map[cur.first][cur.second]);

    for (int i = 0; i < 3; i++) {
        pair<int, int> next = { cur.first + dirX[dirs[dir][i]], cur.second + dirY[dirs[dir][i]] };

        if (next.first <= 0 || next.first > N || next.second <= 0 || next.second > N)
            continue;
        if (map[next.first][next.second] == -1)
            continue;
        sum += min(20, map[next.first][next.second]);
    }
    return sum;
}

void AddAndSpread() {
    InitTempMap();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (temp[i][j] == 0) {
                int sum = 0;
                for (int d = 0; d < Dir; d++) {
                    pair<int, int> next = { i + dirX[d], j + dirY[d] };
                    if (next.first <= 0 || next.first > N || next.second <= 0 || next.second > N)
                        continue;
                    if (temp[next.first][next.second] == -1)
                        continue;
                    sum += temp[next.first][next.second];
                }
                sum /= 10;
                map[i][j] = sum;
            }
        }
    }
}

void InitTempMap() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (map[i][j] > 0)
                map[i][j] += 5;
            temp[i][j] = map[i][j];
        }
    }
}

int Count() {
    int cnt = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (map[i][j] > 0)
                cnt += map[i][j];
        }
    }

    return cnt;
}