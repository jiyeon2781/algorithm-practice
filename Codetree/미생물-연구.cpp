#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 16;
const int MaxCount = 51;
const int Dir = 4;

void Step1(int idx);
void BFS(int x, int y, int idx);

void Step2();
void Init();
bool TryMoveRegion(int cur, pair<int, int> start);
int MaxRegion();
bool MoveRegion(pair<int, int> start, pair<int, int> tempStart, int idx);
void DeleteRegion(pair<int, int> start, int idx);

void Step3();
void Neighbor(pair<int, int> start);

void Print();

int N, Q;
int r1, c1, r2, c2;
int Idx = 1;

int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int regionCount[MaxCount];
bool afterMoveRegion[MaxCount];
bool visitedRegion[MaxCount];
bool deletedRegion[MaxCount];

bool afterCalculate[MaxCount][MaxCount];

int dirX[Dir] = { 0, 0, 1, -1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;

    Idx = 1;
    while (Q--) {
        cin >> r1 >> c1 >> r2 >> c2;
        Step1(Idx);
        Step2();
        Step3();
        Idx += 1;
    }
    return 0;
}

void Step1(int idx) {
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);
    fill(visitedRegion, visitedRegion + MaxCount, false);
    fill(deletedRegion, deletedRegion + MaxCount, false);

    // 1. 미생물 투입 단계
    // 1-1. 좌측 하단 : (r1, c1), (r2, c2), 우측 상단  (r2, c2)인 직사각형 영역에 미생물 투입
    // 1-2. 영역 내 다른 미생물이 존재하면 새로 투입된 미생물이 그 영역 내 미생물을 잡아 먹음
    for (int r = r1; r < r2; r++) {
        for (int c = c1; c < c2; c++) {
            if (map[r][c] != 0)
                regionCount[map[r][c]] -= 1;
            map[r][c] = idx;
            regionCount[idx] += 1;
        }
    }

    // 1-3. 기존에 있던 미생물 무리 A가 새로 투입된 미생물 무리 B에게 잡아먹히면서 A무리가 차지한 영역이 둘 이상으로 나눠질 경우 A무리는 사라짐(BFS로 확인)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0 || visited[i][j])
                continue;
            if (visitedRegion[map[i][j]])
                deletedRegion[map[i][j]] = true;
            else {
                BFS(i, j, map[i][j]);
                visitedRegion[map[i][j]] = true;
            }
        }
    }

    for (int i = 0; i < MaxSize; i++) {
        if (deletedRegion[i])
            regionCount[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (deletedRegion[map[i][j]])
                map[i][j] = 0;
        }
    }
}

void BFS(int x, int y, int idx) {
    queue<pair<int, int>> que;
    que.push({ x, y });
    visited[x][y] = true;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (visited[next.first][next.second] || map[next.first][next.second] != idx)
                continue;
            visited[next.first][next.second] = true;
            que.push(next);
        }
    }
}

int temp[MaxSize][MaxSize];


void Step2() {
    fill(temp[0], temp[0] + MaxSize * MaxSize, 0);
    fill(afterMoveRegion, afterMoveRegion + MaxCount, false);

    // 2. 배양 용기 이동 단계
    // 2-1. 모든 미생물을 새로운 배양 용기로 이동
    while (true) {
        int cur = MaxRegion();
        // 2-2. 기존 배양 용기중 가장 넓은 영역 무리 선택 -> 두개 이상, 먼저 투입된 미생물 선택
        if (cur == -1)
            break;
        bool finished = false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (temp[i][j] == 0) {
                    bool tryMove = TryMoveRegion(cur, { i, j });
                    if (tryMove) {
                        finished = true;
                        break;
                    }
                }
            }
            if (finished)
                break;
        }

        if (!finished) {
            regionCount[cur] = 0;
            deletedRegion[cur] = true;
        }
        // 2-3. 선택된 미생물 무리 새 배양에 옮김 -> 기존 용기 형태 유지, 다른 미생물과 겹치면 안됨 -> x좌표가 작은 위치 & y좌표가 작은 위치
        
        // (영역의 좌측 하단을 저장하고, 해당 좌측 하단을 기준으로 계산해서 temp에 저장 하는 것이 좋아보임)
        // 2-4. 옮기는 과정에서 어떤 곳에 둘 수 없는 미생물 무리 존재 시 사라짐
    }
    
    Init();
}

int MaxRegion() {
    int result = -1;
    int max = 0;
    for (int i = 1; i <= Idx; i++) {
        if (max < regionCount[i] && !afterMoveRegion[i]) {
            max = regionCount[i];
            result = i;
        }
    }
    return result;
}

bool TryMoveRegion(int cur, pair<int, int> start) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == cur && !afterMoveRegion[cur])
            {
                bool result = MoveRegion({ i, j }, start, cur);
                if (result) {
                    afterMoveRegion[cur] = true;
                    return true;
                }
                    
            }
        }
    }
    return false;
}

bool MoveRegion(pair<int, int> start, pair<int, int> tempStart, int idx) {
    queue<pair<int, int>> que;
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);

    que.push(start);
    visited[start.first][start.second] = true;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        int tempX = cur.first - start.first + tempStart.first;
        int tempY = cur.second - start.second + tempStart.second;
        if (tempX < 0 || tempX >= N || tempY < 0 || tempY >= N || temp[tempX][tempY] != 0) {
            DeleteRegion(tempStart, idx);
            return false;
        }
        
        temp[tempX][tempY] = idx;
        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (map[next.first][next.second] != idx || visited[next.first][next.second])
                continue;
            que.push(next);
            visited[next.first][next.second] = true;
        }
    }
    return true;
}

void DeleteRegion(pair<int, int> start, int idx) {
    queue<pair<int, int>> que;
    que.push(start);
    temp[start.first][start.second] = 0;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (temp[next.first][next.second] != idx)
                continue;
            que.push(next);
            temp[next.first][next.second] = 0;
        }
    }
}

void Init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = temp[i][j];
        }
    }
}


int result = 0;
void Step3() {
    fill(afterCalculate[0], afterCalculate[0] + MaxCount * MaxCount, false);
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);
    result = 0;
    // 3. 실험 결과 기록
    // 3-1. 실험 결과 기록 -> 인접한 무리의 쌍 확인
    // 3-2. A와 B가 맞닿은 면이 둘 이상이라도 AB 쌍은 한번만 확인
    // 3-3. 두 무리가 A, B 라면 A영역 넓이 X B 영역 넓이 만큼 성과
    // 확인한 모든 쌍의 성과를 더한 값이 이 실험의 결과 및 출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 0 && !visited[i][j]) {
                Neighbor({ i, j });
            }
        }
    }
    cout << result << "\n";
}

void Neighbor(pair<int, int> start) {
    queue<pair<int, int>> que;
    que.push(start);
    int idx = map[start.first][start.second];
    visited[start.first][start.second] = true;
    
    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };

            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (visited[next.first][next.second])
                continue;

            if (map[next.first][next.second] == idx) {
                visited[next.first][next.second] = true;
                que.push(next);
            }
            else if (map[next.first][next.second] != idx && map[next.first][next.second] != 0) {
                int target = map[next.first][next.second];
                if (afterCalculate[idx][target])
                    continue;
                result += (regionCount[idx] * regionCount[target]);
                afterCalculate[idx][target] = true;
                afterCalculate[target][idx] = true;
            }
        }
    }
}