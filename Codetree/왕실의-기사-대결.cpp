#include <iostream>
#include <queue>

using namespace std;

struct Knight {
    int k;
    int isDamaged;
    bool isDead;
};

const int MaxSize = 41;
const int MaxKnightCnt = 31;
const int Dir = 4;

void MoveKnight(int knight, int dir);
bool IsAvailableMove(int knight, int dir);
void AttackKnight(int knight);
void MoveKnights(int dir);
bool MoveDirection(pair<int, int> start, int dir);
void Remove(int knight);

int L, N, Q;
// L : 체스판 크기
// N : Knight 개수
// Q : 왕의 명령 개수

int map[MaxSize][MaxSize];
int knights[MaxSize][MaxSize];
int temp[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];
Knight info[MaxKnightCnt];

bool isMoved[MaxKnightCnt];

int dirX[Dir] = {-1, 0, 1, 0};
int dirY[Dir] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c, h, w, k;

    cin >> L >> N >> Q;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cin >> map[i][j];
        }
    }
    // 0 : 빈칸
    // 1 : 함정
    // 2 : 벽

    for (int idx = 1; idx <= N; idx++) {
        cin >> r >> c >> h >> w >> k;
        info[idx] = { k, 0, false };
        for (int i = r - 1; i < r + h - 1; i++) {
            for (int j = c - 1; j < c + w - 1; j++) {
                knights[i][j] = idx;
            }
        }
    }

    int knight, dir;
    while (Q--) {
        cin >> knight >> dir;
        if (info[knight].isDead) 
            continue;
        fill(isMoved, isMoved + MaxKnightCnt, false);
        MoveKnight(knight, dir);
    }

    int sum = 0;
    for (int i = 1; i < MaxKnightCnt; i++) {
        if (info[i].isDead || info[i].k == 0)
            continue;
        if (info[i].isDamaged > 0) {
            sum += info[i].isDamaged;
        }
    }

    cout << sum;

    return 0;
}


void MoveKnight(int knight, int dir) {
    if (!IsAvailableMove(knight, dir))
        return;
    MoveKnights(dir); // 모두 움직임
    AttackKnight(knight); // 움직인 이후 함정 수 만큼 Knight 피해
}


void MoveKnights(int dir) {
    fill(temp[0], temp[0] + MaxSize * MaxSize, 0);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (knights[i][j] != 0) {
                if (isMoved[knights[i][j]])
                {
                    temp[i + dirX[dir]][j + dirY[dir]] = knights[i][j];
                }
                else {
                    temp[i][j] = knights[i][j];
                }
            }
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            knights[i][j] = temp[i][j];
        }
    }
}


bool IsAvailableMove(int knight, int dir) {
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);

    // 밀 수 있는지 확인
    // 1. Idx가 knight와 동일하면
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (visited[i][j])
                continue;
            if (knights[i][j] == knight) {
                bool result = MoveDirection({i, j}, dir);
                if (!result)
                    return false;
            }
        }
    }
    // 1-5. 모두 확인하고 이상 없으면 true 리턴

    return true;
}

bool MoveDirection(pair<int, int> start, int dir) {
    visited[start.first][start.second] = true;
    queue<pair<int, int>> que;
    que.push(start);
    isMoved[knights[start.first][start.second]] = true;
    int idx = knights[start.first][start.second];

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= L || next.second < 0 || next.second >= L) {
                if (i == dir)
                    return false;
                continue;
            }

            if (knights[next.first][next.second] == 0) {
                if (map[next.first][next.second] == 2 && i == dir)
                    return false;
                continue;
            }
            
            if (visited[next.first][next.second])
                continue;
            if (knights[next.first][next.second] != knights[cur.first][cur.second] && i == dir || knights[next.first][next.second] == knights[cur.first][cur.second]) {
                isMoved[knights[next.first][next.second]] = true;
                visited[next.first][next.second] = true;
                que.push(next);
            }
        }
    }
    return true;
}

void AttackKnight(int knight) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (knights[i][j] != 0 && map[i][j] == 1 && knights[i][j] != knight && isMoved[knights[i][j]]) {
                info[knights[i][j]].isDamaged += 1;
                info[knights[i][j]].k -= 1;
                if (info[knights[i][j]].k <= 0) {
                    info[knights[i][j]].isDead = true;
                    Remove(knights[i][j]);
                }
                    
            }
        }
    }
}

void Remove(int knight) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (knights[i][j] == knight)
                knights[i][j] = 0;
        }
    }
}