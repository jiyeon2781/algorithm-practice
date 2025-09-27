#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Person {
    pair<int, int> cur;
    int dir;
    int gunNum;
    int personNum;
};

void Start();
void MovePlayers();
void Move(int idx);
void Attack(int idx);
bool ExistPlayer(pair<int, int> player, int idx);
void SwapGun(int idx);
void MoveLosePlayer(Person person, int idx);

const int MaxSize = 21;
const int MaxPersonCnt = 31;
const int Dir = 4;

int N, M, K;

vector<int> map[MaxSize][MaxSize];

int dirX[Dir] = {-1, 0, 1, 0};
int dirY[Dir] = {0, 1, 0, -1};

Person players[MaxPersonCnt];
int result[MaxPersonCnt];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    int attackCount;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> attackCount;
            if (attackCount == 0)
                continue;
            map[i][j].push_back(attackCount);
        }
    }

    int x, y, d, s;

    for (int i = 1; i <= M; i++) {
        cin >> x >> y >> d >> s;
        x -= 1;
        y -= 1;
        players[i] = { {x, y}, d, 0, s };
    }

    Start();

    return 0;
}

void Start() {
    while (K--) {
        MovePlayers();
    }

    for (int i = 1; i <= M; i++) {
        cout << result[i] << ' ';
    }
}

Person enemy;
int enemyIdx;

void MovePlayers() {
    // 첫번째 플레이어 부터 순차적으로 1칸씩 이동
    // 칸에 들어가서 총을 줍거나 플레이어 만났을때
    for (int i = 1; i <= M; i++) {
        // 첫번째 플레이어 이동 Move
        Move(i);
        if (ExistPlayer(players[i].cur, i)) {
            // 해당 칸에 플레이어?
            Attack(i);
        }
        else {
            // 해당 칸에 총?
            SwapGun(i);
        }
    }
}

void Move(int idx) {
    // dir 방향으로 1칸 이동
    pair<int, int> cur = players[idx].cur;
    int dir = players[idx].dir;
    pair<int, int> next = { cur.first + dirX[dir], cur.second + dirY[dir] };

    // 만약 next가 범위가 넘어간다면, 뒤로 1칸
    if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
    {
        dir = (dir + 2) % Dir;
        next = { cur.first + dirX[dir], cur.second + dirY[dir] };
    }

    players[idx].cur = next;
    players[idx].dir = dir;
}

bool ExistPlayer(pair<int, int> player, int idx) {
    for (int i = 1; i <= M; i++) {
        if (players[i].cur == player && i != idx) {
            enemy = players[i];
            enemyIdx = i;
            return true;
        }
    }
    return false;
}


void Attack(int idx) {
    Person player = players[idx];

    int playerSum = player.gunNum + player.personNum;
    int enemySum = enemy.gunNum + enemy.personNum;

    if (playerSum > enemySum || (playerSum == enemySum && player.personNum > enemy.personNum)) {
        // 플레이어가 이겼을 때
        result[idx] += (playerSum - enemySum);
        MoveLosePlayer(enemy, enemyIdx);
        SwapGun(idx);
    }
    else {
        // 플레이어가 졌을 때
        result[enemyIdx] += (enemySum - playerSum);
        MoveLosePlayer(players[idx], idx);
        SwapGun(enemyIdx);
    }
}

void MoveLosePlayer(Person person, int idx) {
    if (person.gunNum != 0) {
        map[person.cur.first][person.cur.second].push_back(person.gunNum);
        players[idx].gunNum = 0;
    }

    pair<int, int> cur = person.cur;
    int dir = person.dir;
    while (true) {
        pair<int, int> next = { cur.first + dirX[dir], cur.second + dirY[dir] };
        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N || ExistPlayer(next, idx)) {
            dir = (dir + 1) % 4;
        }
        else {
            players[idx].cur = next;
            players[idx].dir = dir;

            vector<int> guns = map[players[idx].cur.first][players[idx].cur.second];

            if (guns.size() == 0)
                break;

            int maxIdx = -1;
            int gunSize = players[idx].gunNum;
            for (int i = 0; i < guns.size(); i++) {
                if (gunSize < guns[i]) {
                    maxIdx = i;
                    gunSize = guns[i];
                }
            }

            if (maxIdx == -1)
                break;

            players[idx].gunNum = guns[maxIdx];

            vector<int> newGuns;
            for (int i = 0; i < guns.size(); i++) {
                if (maxIdx == i)
                    continue;
                newGuns.push_back(guns[i]);
            }
            map[players[idx].cur.first][players[idx].cur.second] = newGuns;

            break;
        }
    }
}

void SwapGun(int idx) {
    int cur = players[idx].gunNum;
    vector<int> guns = map[players[idx].cur.first][players[idx].cur.second];

    if (guns.size() == 0)
        return;
    int maxNum = cur;
    int maxIdx = -1;
    for (int i = 0; i < guns.size(); i++) {
        if (maxNum < guns[i]) {
            maxNum = guns[i];
            maxIdx = i;
        }
    }

    if (cur == 0) {
        players[idx].gunNum = guns[maxIdx];

        vector<int> newGuns;
        for (int i = 0; i < guns.size(); i++) {
            if (maxIdx == i)
                continue;
            newGuns.push_back(guns[i]);
        }

        map[players[idx].cur.first][players[idx].cur.second] = newGuns;
    }
    else if (maxIdx != -1) {
        players[idx].gunNum = guns[maxIdx];
        map[players[idx].cur.first][players[idx].cur.second][maxIdx] = cur;
    }
}
