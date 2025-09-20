#include <iostream>

using namespace std;

bool RudolfMove();
void SantasMove();
void Crash(bool isRudolfRush, int idx, pair<int, int> dir);
int GetDistance(pair<int, int> a, pair<int, int> b);
void Interaction(pair<int, int> moveSanta, pair<int, int> dir, int idx);
void Stun(int idx);
void AddPoint();
void Print();

const int MaxSantaCnt = 31;
const int MaxMapSize = 51;
const int Dir = 4;

int N, M, P, C, D;
int curTurn = 0;

int map[MaxMapSize][MaxMapSize];
bool visited[MaxMapSize][MaxMapSize];

pair<int, int> rudolf;
pair<int, int> santas[MaxSantaCnt];
int isStunTurn[MaxSantaCnt];
bool isDead[MaxSantaCnt];
int result[MaxSantaCnt];

int dirX[Dir] = { -1, 0, 1, 0, };
int dirY[Dir] = { 0, 1, 0, -1 };
// 상 우 하 좌 

int nearDistance;
int nearIdx;
pair<int, int> rudolfDir = { 0, 0 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P >> C >> D;

    cin >> rudolf.first >> rudolf.second;
    rudolf.first -= 1;
    rudolf.second -= 1;

    fill(isStunTurn, isStunTurn + MaxSantaCnt, -1);
    fill(isDead, isDead + MaxSantaCnt, false);

    int idx = 0;
    for (int i = 1; i <= P; i++) {
        int x, y;
        cin >> idx >> x >> y;
        santas[idx].first = x - 1;
        santas[idx].second = y - 1;

        map[santas[idx].first][santas[idx].second] = idx;
    }

    for (curTurn = 1; curTurn <= M; curTurn++) {
        bool isMeet = RudolfMove();
         // Print();
        if (isMeet) {
            int idx = 0;
            for (int i = 1; i <= P; i++) {
                if (rudolf.first == santas[i].first && rudolf.second == santas[i].second) {
                    if (isDead[i])
                        continue;
                    idx = i;
                    break;
                }
            }
            Crash(true, idx, rudolfDir);
        }
        SantasMove();
        AddPoint();

         // Print();
    }

    for (int i = 1; i <= P; i++) {
        cout << result[i] << ' ';
    }

    return 0;
}

void AddPoint() {
    for (int i = 1; i <= P; i++) {
        if (isDead[i])continue;
        result[i] += 1;
    }
}

void Print() {
    cout << "---cur Turn : " << curTurn << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << ' ';
        }
        cout << "\n";
    }
    cout << "rudolf : (" << rudolf.first << ',' << rudolf.second << ")\n";
    for (int i = 1; i <= P; i++) {
        cout << result[i] << ' ';
    }
    cout << "\n";
    for (int i = 1; i <= P; i++) {
        if (isDead[i]) cout << "dead ";
        else cout << "alive ";
    }
    cout << "------\n";
}

bool RudolfMove() {
    // 현재 칸에는 산타가 없다는 가정
    // 각 산타의 거리 계산 후 1칸 이동
    pair<int, int> near;
    nearDistance = 999999;
    rudolfDir = { 0, 0 };

    for (int i = 1; i <= P; i++) {
        pair<int, int> santa = santas[i];
        if (isDead[i]) 
            continue;
        int distance = GetDistance(santa, rudolf);
        if (distance < nearDistance) {
            nearDistance = distance;
            near = santa;
        }
        else if (distance == nearDistance) {
            if (santa.first > near.first || (santa.first == near.first && santa.second > near.second)) {
                near = santa;
            }
        }
    }

    if (nearDistance == 999999)
        return false;

    if (near.first > rudolf.first) {
        rudolfDir.first += 1;
    }
    else if (near.first < rudolf.first) {
        rudolfDir.first -= 1;
    }
    if (near.second > rudolf.second) {
        rudolfDir.second += 1;
    }
    else if (near.second < rudolf.second) {
        rudolfDir.second -= 1;
    }

    rudolf.first += rudolfDir.first;
    rudolf.second += rudolfDir.second;

    // 산타와 만났으면 return true
    if (map[rudolf.first][rudolf.second] != 0)
        return true;
    else 
        return false;
}

void SantasMove() {
    for (int idx = 1; idx <= P; idx++) {
        // 산타가 기절했거나 탈락했을 경우 continue
        if (isStunTurn[idx] == curTurn || isStunTurn[idx] + 1 == curTurn)
            continue;
        if (isDead[idx])
            continue;

        nearDistance = GetDistance(santas[idx], rudolf);
        pair<int, int> afterMoveSanta;
        
        int dir = -1;

        // 루돌프와 가까워지는 방향으로
        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { santas[idx].first + dirX[i], santas[idx].second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (map[next.first][next.second] != 0)
                continue;
            // 산타가 있으면 continue

            int distance = GetDistance(next, rudolf);
            if (nearDistance > distance) {
                nearDistance = distance;
                afterMoveSanta = next;
                dir = i;
            }
        }

        if (dir == -1)
            continue;

        // 산타 이동
        map[santas[idx].first][santas[idx].second] = 0;
        map[afterMoveSanta.first][afterMoveSanta.second] = idx;
        santas[idx] = afterMoveSanta;

        // 루돌프 확인 후 Crash 진행
        if (afterMoveSanta.first == rudolf.first && afterMoveSanta.second == rudolf.second)
            Crash(false, idx, {-dirX[dir], -dirY[dir]});
    }
}

int GetDistance(pair<int, int> a, pair<int, int> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

void Crash(bool isRudolfRush, int idx, pair<int,int> dir) {
    pair<int, int> cur = rudolf;
    pair<int, int> moveSanta;
    if (isRudolfRush) {
        result[idx] += C;
        moveSanta = { cur.first + dir.first * C, cur.second + dir.second * C };
    }
    else
    {
        result[idx] += D;
        moveSanta = { cur.first + dir.first * D, cur.second + dir.second * D };
    }

    if (moveSanta.first < 0 || moveSanta.first >= N || moveSanta.second < 0 || moveSanta.second >= N)
        isDead[idx] = true;
    else {
        Interaction(moveSanta, dir, idx);
        Stun(idx);
    }
    map[cur.first][cur.second] = 0;
}

void Interaction(pair<int, int> moveSanta, pair<int ,int> dir, int idx) {
    pair<int, int> cur = moveSanta;
    int curIdx = idx;
    while (true) {
        if (map[cur.first][cur.second] == 0) break;
        if (cur.first < 0 || cur.first >= N || cur.second < 0 || cur.second >= N) break;

        int nextIdx = map[cur.first][cur.second];
        map[cur.first][cur.second] = curIdx;
        santas[curIdx] = cur;
        cur = { cur.first + dir.first, cur.second + dir.second };
        curIdx = nextIdx;
    }
    if (cur.first < 0 || cur.first >= N || cur.second < 0 || cur.second >= N) {
        isDead[curIdx] = true;
        return;
    }
        
    map[cur.first][cur.second] = curIdx;
    santas[curIdx] = cur;
}

void Stun(int idx) {
    isStunTurn[idx] = curTurn;
}
