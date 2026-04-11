#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct WarriorInfo {
    int r, c;
    bool isDead;
    bool isRocked;
};

struct PathInfo {
    pair<int, int> prev;
    int cost;
};

// 메두사 이동
void Start(); // 메두사 이동 시작
bool MedusaMovePath(); // 메두사의 이동 경로 확인 여부
void SaveMedusaPath(); // 메두사의 이동 경로 저장
// -- 

// 시야각 계산 및 돌로 변한 전사 설정
void MedusaLooks(); // 메두사의 시선들 계산
void MedusaLook(int dir); // 메두사 현재 시선 계산
void BlindMedusaLook(int dir); // 현재 시선 기준으로 가려지는 각 계산
void BlindMedusaLookInOneWarrior(pair<int, int> warrior, int dir); // 워리어 한명당 현재 시선 기준으로 가려지는 각 계산
void InitSeeMap(); // tempSee -> see 에 저장
int CntRockedWarriors(); // 위 두 함수를 거친 후 경직된 전사 수 계산
void SetRockedWarriors(); // 경직된 전사 설정 변경
int GetDistance(pair<int, int> a, pair<int, int> b);
// --

// 전사 움직임
void InitWarriorMap(); // temp -> warriorsMap 에 저장
void MoveWarriors(); // 전사들 움직임 (사망도 함께 계산)
void MoveWarrior(int idx); // 한 칸에서의 움직임
// --

const int MaxSize = 51;
const int MaxWarriors = 301;
const int Dir = 4;

int map[MaxSize][MaxSize]; // 도로 정보 저장
PathInfo cost[MaxSize][MaxSize];

vector<int> warriorsMap[MaxSize][MaxSize]; // 전사들의 현재 위치 정보
vector<int> tempWarriorsMap[MaxSize][MaxSize]; // 전사들의 현재 위치 정보 temp값
int see[MaxSize][MaxSize]; // 메두사 시선 및 시야각
int tempSee[MaxSize][MaxSize]; // 메두사 시선 및 시야각 임시 저장소(방향에 따른 계산)
// 0 : 없음, 1: 메두사의 시선, 2 : 가려진 시야
vector<WarriorInfo> warriors; // 현재 전사들의 정보 (인덱스 1 ~ M)
stack <pair<int, int>> path; // 메두사의 이동 경로 
// vector<pair<int, int>> path; 
pair<int, int> medusa, home, park; // 메두사 현재 위치, 집, 공원

int moveDistance = 0, rockedWarriors = 0, attackedWarriors = 0;
// 전사들의 이동거리 합, 돌이 된 전사의 수, 공격한 전사의 수
// 모두 턴마다 계산 후 출력

int N, M;
int dirX[Dir] = { -1, 1, 0, 0 };
int dirY[Dir] = { 0, 0, -1, 1 };

int dx2[Dir] = { 0, 0, -1, 1 }; // 좌우상하
int dy2[Dir] = { -1, 1, 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    cin >> home.first >> home.second >> park.first >> park.second;

    int r, c;
    warriors.push_back({ -1, -1, false, false }); // 0 인덱스 공백 저장

    for (int i = 1; i <= M; i++) {
        cin >> r >> c;
        warriorsMap[r][c].push_back(i);
        warriors.push_back({ r, c, false, false });
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    if (!MedusaMovePath())
        cout << -1;
    else {
        SaveMedusaPath();
        Start();
    }
       

    return 0;
}

void MedusaPathPrint() {
    cout << home.first << ' ' << home.second << "\n";
    while (!path.empty()) {
        pair<int, int> cur = path.top();
        path.pop();
        cout << cur.first << ' ' << cur.second << "\n";
    }
    cout << park.first << ' ' << park.second << "\n";
}

void Start() {
    while (!path.empty()) {
        moveDistance = 0, rockedWarriors = 0, attackedWarriors = 0;
        // 1. 메두사 이동
        medusa = path.top();
        path.pop();
        // 1-1. 해당 칸에 전사가 있는지 확인
        for (int i = 0; i < warriorsMap[medusa.first][medusa.second].size(); i++) {
            int idx = warriorsMap[medusa.first][medusa.second][i];
            warriors[idx].isDead = true;
            // attackedWarriors += 1;
        }
        warriorsMap[medusa.first][medusa.second].clear();

        // 2. 메두사 시선 계산
        MedusaLooks();
        // 3. 전사들 이동
        MoveWarriors();
        cout << moveDistance << ' ' << rockedWarriors << ' ' << attackedWarriors << "\n";
    }
    cout << 0;
}

void SaveMedusaPath() {
    pair<int, int> cur = park;

    while (true) {
        cur = cost[cur.first][cur.second].prev;
        if (home.first == cur.first && home.second == cur.second)
            break;
        path.push(cur);
    }
}

bool MedusaMovePath() {
    queue<pair<int, int>> que;
    cost[home.first][home.second] = { {-1, -1}, 1 };
    // 넘어온 좌표와 cost 저장
    que.push(home);

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        if (park.first == cur.first && park.second == cur.second)
            return true;

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            // 경계를 벗어나면
            if (cost[next.first][next.second].cost > 0)
                continue;
            //이미 cost가 존재하면
            if (map[next.first][next.second] == 1)
                continue;
            // 도로가 없으면

            cost[next.first][next.second] = { cur, cost[cur.first][cur.second].cost + 1 };
            que.push(next);
        }
    }
    return false;
}

void MedusaLooks() {
    int maxCnt = -1, maxDir = 0;
    // 각 방향별로 메두사의 시선 및 시야각 계산 후 count
    // 임시 temp 생성 -> 시야각을 임시로 저장할 공간
    for (int d = 0; d < Dir; d++) {
        fill(tempSee[0], tempSee[0] + MaxSize * MaxSize, 0);

        MedusaLook(d);
        // 현재 메두사가 보는 시야각 (1을 저장)
        BlindMedusaLook(d);
        // 전사에 가려진 시야각 (2를 저장)

        int curCnt = CntRockedWarriors();
        // 저장된 맵 (tempSee)을 통해 바위로 변한 전사들 저장

        if (maxCnt < curCnt) {
            maxCnt = curCnt;
            maxDir = d;
            InitSeeMap();
        }
    }

    rockedWarriors = maxCnt;
    SetRockedWarriors();
}

void InitSeeMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            see[i][j] = tempSee[i][j];
        }
    }
}

void MedusaLook(int dir) {
    // ☆ tempSee에 저장 해야 함
    if (dir == 0) { // 위
        // r - 1 ~ 0 까지 시야 처단
        // c - 1 ~ c + 1, c - 2 ~ c + 2, c - 3 ~ c + 3 
        int idx = 1;
        for (int r = medusa.first - 1; r >= 0; r--) {
            for (int c = medusa.second - idx; c <= medusa.second + idx; c++) {
                if (c < 0) {
                    tempSee[r][0] = 1;
                }
                else if (c >= N) {
                    tempSee[r][N - 1] = 1;
                }
                else
                    tempSee[r][c] = 1;
            }
            idx += 1;
        }
    }
    else if (dir == 1) { // 아래
        int idx = 1;
        for (int r = medusa.first + 1; r < N; r++) {
            for (int c = medusa.second - idx; c <= medusa.second + idx; c++) {
                if (c < 0) {
                    tempSee[r][0] = 1;
                }
                else if (c >= N) {
                    tempSee[r][N - 1] = 1;
                }
                else
                    tempSee[r][c] = 1;
            }
            idx += 1;
        }
    }
    else if (dir == 2) { // 왼쪽
        int idx = 1;
        for (int c = medusa.second - 1; c >= 0; c--) {
            for (int r = medusa.first - idx; r <= medusa.first + idx; r++) {
                if (r < 0) {
                    tempSee[0][c] = 1;
                }
                else if (r >= N) {
                    tempSee[N - 1][c] = 1;
                }
                else
                    tempSee[r][c] = 1;
            }
            idx += 1;
        }
    }
    else if (dir == 3) { // 오른쪽
        int idx = 1;
        for (int c = medusa.second + 1; c < N; c++) {
            for (int r = medusa.first - idx; r <= medusa.first + idx; r++) {
                if (r < 0) {
                    tempSee[0][c] = 1;
                }
                else if (r >= N) {
                    tempSee[N - 1][c] = 1;
                }
                else
                    tempSee[r][c] = 1;
            }
            idx += 1;
        }
    }
}

void BlindMedusaLook(int dir) {
    // ☆ tempSee에 저장 해야 함
    for (int i = 1; i <= M; i++) {
        WarriorInfo cur = warriors[i];
        if (tempSee[cur.r][cur.c] == 0)
            continue;
        if (cur.isDead)
            continue;
        if (dir == 0 && cur.r >= medusa.first)
            continue;
        else if (dir == 1 && cur.r <= medusa.first)
            continue;
        else if (dir == 2 && cur.c >= medusa.second)
            continue;
        else if (dir == 3 && cur.c <= medusa.second)
            continue;
        BlindMedusaLookInOneWarrior({cur.r, cur.c}, dir);
    }
}

void BlindMedusaLookInOneWarrior(pair<int, int> warrior, int dir) {
    int idx = 1;
    if (dir == 0) { // 위
        if (medusa.second < warrior.second) {
            idx = 1;
            for (int r = warrior.first - 1; r >= 0; r--) {
                for (int c = warrior.second; c <= warrior.second + idx; c++) {
                    if (c < 0) {
                        if (tempSee[r][0] == 0)
                            continue;
                        tempSee[r][0] = 2;
                    }
                    else if (c >= N) {
                        if (tempSee[r][N - 1] == 0)
                            continue;
                        tempSee[r][N - 1] = 2;
                    }
                    else{
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                        
                }
                idx += 1;
            }
        }
        else if (medusa.second > warrior.second) {
            idx = 1;
            for (int r = warrior.first - 1; r >= 0; r--) {
                for (int c = warrior.second - idx; c <= warrior.second; c++) {
                    if (c < 0) {
                        if (tempSee[r][0] == 0)
                            continue;
                        tempSee[r][0] = 2;
                    }
                    else if (c >= N) {
                        if (tempSee[r][N - 1] == 0)
                            continue;
                        tempSee[r][N - 1] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }

                }
                idx += 1;
            }
        }
        else {
            for (int r = warrior.first - 1; r >= 0; r--) {
                if (tempSee[r][warrior.second] == 0)
                    continue;
                tempSee[r][warrior.second] = 2;
            }
        }
    }
    else if (dir == 1) { // 아래
        if (medusa.second < warrior.second) {
            idx = 1;
            for (int r = warrior.first + 1; r < N; r++) {
                for (int c = warrior.second; c <= warrior.second + idx; c++) {
                    if (c < 0) {
                        if (tempSee[r][0] == 0)
                            continue;
                        tempSee[r][0] = 2;
                    }
                    else if (c >= N) {
                        if (tempSee[r][N - 1] == 0)
                            continue;
                        tempSee[r][N - 1] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else if (medusa.second > warrior.second) {
            idx = 1;
            for (int r = warrior.first + 1; r < N; r++) {
                for (int c = warrior.second - idx; c <= warrior.second; c++) {
                    if (c < 0) {
                        if (tempSee[r][0] == 0)
                            continue;
                        tempSee[r][0] = 2;
                    }
                    else if (c >= N) {
                        if (tempSee[r][N - 1] == 0)
                            continue;
                        tempSee[r][N - 1] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else {
            for (int r = warrior.first + 1; r < N; r++) {
                if (tempSee[r][warrior.second] == 0)
                    continue;
                tempSee[r][warrior.second] = 2;
            }
        }
    }
    else if (dir == 2) {
        if (medusa.first < warrior.first) {
            idx = 1;
            for (int c = warrior.second - 1; c >= 0; c--) {
                for (int r = warrior.first; r <= warrior.first + idx; r++) {
                    if (r < 0) {
                        if (tempSee[0][c] == 0)
                            continue;
                        tempSee[0][c] = 2;
                    }
                    else if (r >= N) {
                        if (tempSee[N - 1][c] == 0)
                            continue;
                        tempSee[N - 1][c] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else if (medusa.first > warrior.first) {
            idx = 1;
            for (int c = warrior.second - 1; c >= 0; c--) {
                for (int r = warrior.first - idx; r <= warrior.first; r++) {
                    if (r < 0) {
                        if (tempSee[0][c] == 0)
                            continue;
                        tempSee[0][c] = 2;
                    }
                    else if (r >= N) {
                        if (tempSee[N - 1][c] == 0)
                            continue;
                        tempSee[N - 1][c] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else {
            for (int c = warrior.second - 1; c >= 0; c--) {
                if (tempSee[warrior.first][c] == 0)
                    continue;
                tempSee[warrior.first][c] = 2;
            }
        }
    }
    else if (dir == 3) {

        if (medusa.first < warrior.first) {
            idx = 1;
            for (int c = warrior.second + 1; c < N; c++) {
                for (int r = warrior.first; r <= warrior.first + idx; r++) {
                    if (r < 0) {
                        if (tempSee[0][c] == 0)
                            continue;
                        tempSee[0][c] = 2;
                    }
                    else if (r >= N) {
                        if (tempSee[N - 1][c] == 0)
                            continue;
                        tempSee[N - 1][c] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else if (medusa.first > warrior.first) {
            idx = 1;
            for (int c = warrior.second + 1; c < N; c++) {
                for (int r = warrior.first - idx; r <= warrior.first; r++) {
                    if (r < 0) {
                        if (tempSee[0][c] == 0)
                            continue;
                        tempSee[0][c] = 2;
                    }
                    else if (r >= N) {
                        if (tempSee[N - 1][c] == 0)
                            continue;
                        tempSee[N - 1][c] = 2;
                    }
                    else {
                        if (tempSee[r][c] == 0)
                            continue;
                        tempSee[r][c] = 2;
                    }
                }
                idx += 1;
            }
        }
        else {
            for (int c = warrior.second + 1; c < N; c++) {
                if (tempSee[warrior.first][c] == 0)
                    continue;
                tempSee[warrior.first][c] = 2;
            }
        }
    }
}

int CntRockedWarriors() {
    int cnt = 0;
    // ☆ tempSee에 있는 전사 데이터를 바탕으로
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tempSee[i][j] != 1)
                continue;
            cnt += warriorsMap[i][j].size();
        }
    }
    return cnt;
}

void SetRockedWarriors() {
    bool isRocked = true;
    // 모든 돌로 변한 전사 초기화 후 (돌 값 초기화) 돌 값 세팅
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (see[i][j] == 1)
                isRocked = true;
            else
                isRocked = false;
            for (int k = 0; k < warriorsMap[i][j].size(); k++) {
                int idx = warriorsMap[i][j][k];
                warriors[idx].isRocked = isRocked;
            }
        }
    }
}

void MoveWarriors() {
    fill(tempWarriorsMap[0], tempWarriorsMap[0] + MaxSize * MaxSize, vector<int>());
    // 이동 시 죽은 횟수도 구해야 함
    for (int i = 1; i <= M; i++) {
        if (warriors[i].isDead)
            continue;
        if (warriors[i].isRocked) {
            tempWarriorsMap[warriors[i].r][warriors[i].c].push_back(i);
            warriors[i].isRocked = false;
        }
        else {
            MoveWarrior(i);
        }
        
    }
    InitWarriorMap();
}

void InitWarriorMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            warriorsMap[i][j] = tempWarriorsMap[i][j];
        }
    }
}

void MoveWarrior(int idx) {
    // 하나의 Warrior 이동
    // 이동 시 vectorMap temp에 저장
    // warriors에도 갱신
    
    pair<int, int> saveNext = { -1, -1 }, cur = { warriors[idx].r, warriors[idx].c };
    int saveDist = GetDistance(cur, medusa);

    for (int i = 0; i < Dir; i++) {
        pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
            continue;
        if (see[next.first][next.second] == 1)
            continue;
        
        int dist = GetDistance(next, medusa);
        if (dist < saveDist)
        {
            saveNext = next;
            saveDist = dist;
            break;
        }
    }

    if (saveNext.first == -1) {
        warriors[idx].r = cur.first;
        warriors[idx].c = cur.second;

        tempWarriorsMap[cur.first][cur.second].push_back(idx);
        return;
    }
    moveDistance += 1;


    cur = saveNext;
    saveNext = { -1, -1 };
    saveDist = GetDistance(cur, medusa);
    if (saveDist == 0) {
        warriors[idx].isDead = true;
        attackedWarriors += 1;
        return;
    }

    for (int i = 0; i < Dir; i++) {
        pair<int, int> next = { cur.first + dx2[i], cur.second + dy2[i] };
        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
            continue;
        if (see[next.first][next.second] == 1)
            continue;

        int dist = GetDistance(next, medusa);
        if (dist < saveDist)
        {
            saveNext = next;
            saveDist = dist;
            break;
        }
    }

    if (saveNext.first == -1) {
        warriors[idx].r = cur.first;
        warriors[idx].c = cur.second;

        tempWarriorsMap[cur.first][cur.second].push_back(idx);
        return;
    }
    moveDistance += 1;

    warriors[idx].r = saveNext.first;
    warriors[idx].c = saveNext.second;

    if (saveNext.first == medusa.first && saveNext.second == medusa.second) {
        warriors[idx].isDead = true;
        attackedWarriors += 1;
        return;
    }

    tempWarriorsMap[saveNext.first][saveNext.second].push_back(idx);
}


int GetDistance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}