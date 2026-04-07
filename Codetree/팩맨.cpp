#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int deadRound;
    int dir;
    bool isEgg;
};

void Start();
void DeleteDeadMonster();
void TryCopyAndMonsters();
void CopyAndMoveMonster(pair<int, int> cur);
void InitMap();
void InitTemp();
void InitPath(int depth, int maxDepth);
void MovePackman();
int CntCurrentPath(int idx);
void CompleteCopyMonsters();

const int MaxSize = 5;
const int DirCnt = 8;
const int MaxPathSize = 64;

vector<vector<int>> paths;
vector<int> curPath;
vector<Info> map[MaxSize][MaxSize];
vector<Info> temp[MaxSize][MaxSize];
bool isDead[MaxSize][MaxSize];

int dirX[DirCnt] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dirY[DirCnt] = {0, -1, -1, -1, 0, 1, 1, 1};
// 8 방향

int pathX[4] = {-1, 0, 1, 0};
int pathY[4] = {0, -1, 0, 1};
// 상, 좌, 하, 우 

int m, t, curRound;
pair<int, int> packman;

pair<int, int> maxInfo = { 0, 0 }; // cnt, idx

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> t;

    int r, c, d;
    cin >> r >> c;
    packman = { r, c };

    for (int i = 0; i < m; i++) {
        cin >> r >> c >> d;
        map[r][c].push_back({ -1, d - 1, false });

    }

    Start();

    return 0;
}

void Start() {
    InitPath(0, 3);

    for (int i = 1; i <= t; i++) {
        curRound = i;

        // temp 초기화
        for (int i = 1; i < MaxSize; i++)
            for (int j = 1; j < MaxSize; j++)
                temp[i][j].clear();

        TryCopyAndMonsters();
        // 몬스터 복제 및 이동 시도
        MovePackman();
        //턴수 확인 후 시체 삭제
        DeleteDeadMonster();
        // 팩맨 이동
        CompleteCopyMonsters();
    }
    // 살아있는 몬스터 개수 확인
    int cnt = 0;

    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            for (int h = 0; h < map[i][j].size(); h++) {
                if (map[i][j][h].deadRound == -1)
                    cnt += 1;
            }
        }
    }
    cout << cnt;
}

void DeleteDeadMonster() {
    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            vector<Info> curMonster;
            bool isDeadMonster = false;
            for (int h = 0; h < map[i][j].size(); h++) {
                if (map[i][j][h].deadRound == -1) {
                    curMonster.push_back(map[i][j][h]);
                }
                else if (map[i][j][h].deadRound + 2 <= curRound) {
                    continue;
                }
                else {
                    curMonster.push_back(map[i][j][h]);
                    isDeadMonster = true;
                }
            }
            map[i][j] = curMonster;
            isDead[i][j] = isDeadMonster;
        }
    }
}

void TryCopyAndMonsters() {
    // 맵 for문을 돌면서 확인 후 같은 방향으로 복제
    // 바로 부화하지 않음
    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            CopyAndMoveMonster({ i, j });
        }
    }

    // 맵 갱신
    InitMap();
}

void InitMap() {
    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            map[i][j] = temp[i][j];
        }
    }
}

void InitTemp() {
    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            temp[i][j] = map[i][j];
        }
    }
}

void CopyAndMoveMonster(pair<int, int> cur) {
    for (Info monster : map[cur.first][cur.second]) {
        // 1. 알 생성
        if (monster.deadRound > 0) {
            temp[cur.first][cur.second].push_back(monster);  // 시체 유지
            continue;
        }
        temp[cur.first][cur.second].push_back({-1, monster.dir, true});
        bool isMoved = false;
        // 2. 이동
        for (int i = 0; i < DirCnt; i++) {
            int idx = (monster.dir + i) % DirCnt;
            pair<int, int> next = { cur.first + dirX[idx], cur.second + dirY[idx] };

            // 격자 밖
            if (next.first <= 0 || next.first >= MaxSize || next.second <= 0 || next.second >= MaxSize)
                continue;
            // 시체 여부
            if (isDead[next.first][next.second])
                continue;
            // 팩맨 여부
            if (next.first == packman.first && next.second == packman.second)
                continue;

            // 지나칠 수 있는 경우
            monster.dir = idx;
            temp[next.first][next.second].push_back(monster);
            isMoved = true;
            break;
        }
        // 모두 지나치지 못했을 경우
        if(!isMoved)
            temp[cur.first][cur.second].push_back(monster);
    }
}

void InitPath(int depth, int maxDepth) {
    // 팩맨이 이동할 수 있는 경우의 수를 모두 계산 -> Backtracking
    if (depth == maxDepth) {
        paths.push_back(curPath);
        return;
    }

    for (int i = 0; i < 4; i++) {
        curPath.push_back(i);
        InitPath(depth + 1, maxDepth);
        curPath.pop_back();
    }
}

void MovePackman() {
    maxInfo = { 0, 0 };

    for (int i = 0; i < paths.size(); i++) {
        int curCnt = CntCurrentPath(i);
        if (curCnt > maxInfo.first)
            maxInfo = { curCnt, i };
        // 큰 값을 넣고 같으면 continue -> 우선순위가 낮으므로
    }

    // 팩맨 이동
    // 그리고 3번을 이동하면서 몬스터들을 죽임(부화 했는지 확인 후 deadround 갱신)
    for (auto curPath : paths[maxInfo.second]) {
        pair<int, int> next = { packman.first + pathX[curPath], packman.second + pathY[curPath] };
        if (next.first <= 0 || next.first >= MaxSize || next.second <= 0 || next.second >= MaxSize)
            continue;

        packman = next;
        for (int i = 0; i < map[next.first][next.second].size(); i++) {
            Info monster = map[next.first][next.second][i];
            if (monster.isEgg)
                continue;
            if (monster.deadRound > 0)
                continue;
            map[next.first][next.second][i].deadRound = curRound;
            isDead[next.first][next.second] = true;
        }
    }
}

int CntCurrentPath(int idx) {
    curPath = paths[idx];
    InitTemp();
    int cnt = 0;
    pair<int, int> curPackman = packman;
    bool valid = true;

    
    for (auto cur : curPath) {
        pair<int, int> next = { curPackman.first + pathX[cur], curPackman.second + pathY[cur] };
        if (next.first <= 0 || next.first >= MaxSize || next.second <= 0 || next.second >= MaxSize) {
            valid = false;
            break;  // 이 경로 자체가 무효
        }

        for (int i = 0; i < temp[next.first][next.second].size(); i++) {
            Info monster = temp[next.first][next.second][i];
            if (monster.isEgg)
                continue;
            if (monster.deadRound > 0)
                continue;
            temp[next.first][next.second][i].deadRound = curRound;
            cnt += 1;
        }

        curPackman = next;
    }

    if (!valid) return -1;
    return cnt;
}

void CompleteCopyMonsters() {
    // isEgg를 모두 false로 돌리기
    for (int i = 1; i < MaxSize; i++) {
        for (int j = 1; j < MaxSize; j++) {
            for (int h = 0; h < map[i][j].size(); h++) {
                if (map[i][j][h].isEgg)
                    map[i][j][h].isEgg = false;
            }
        }
    }
}