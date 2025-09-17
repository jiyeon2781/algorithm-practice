#include <iostream>
#include <queue>

using namespace std;

struct Golem {
    pair<int, int> center;
    int exitDir;
};

void ClearMap();
bool Move();
bool InRange(pair<int, int> curGolem);
bool MoveDown(pair<int, int> curGolem);
bool MoveLeft(pair<int, int> curGolem);
bool MoveRight(pair<int, int> curGolem);
void SetMap();
void MoveSoul();
int BFS(pair<int, int> start);

void Print();

const int MaxSize = 75;
const int Dir = 4;

int R, C, K;
int result = 0;
int idx = 1;

int map[MaxSize][MaxSize];
bool isExit[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

Golem cur;

bool refresh = false;

int dirX[Dir] = { -1, 0, 1, 0 };
int dirY[Dir] = { 0, 1, 0, -1 };
// 북, 동, 남, 서

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> C >> K;
    int c, d;

    while (K--) {
        cin >> c >> d;

        cur.center.first = 1;
        cur.center.second = c - 1;
        cur.exitDir = d;

        while (true) {
            bool isMoved = Move();
            if (!isMoved)
                break;
        }

        if (cur.center.first < 4) 
            refresh = true;
        
        if (!refresh) {
            SetMap();
            MoveSoul();
        }
        else {
            ClearMap();
            refresh = false;
        }
           
    }

    cout << result;

    return 0;
}

void Print() {
    for (int i = 0; i < R + 3; i++) {
        for (int j = 0; j < C; j++) {
            cout << isExit[i][j] << ' ';
        }
        cout << "\n";
    }
}

void ClearMap() {
    fill(isExit[0], isExit[0] + MaxSize * MaxSize, false);
    fill(map[0], map[0] + MaxSize * MaxSize, 0);
}

bool Move() {
    //한 칸 내려감.
    // 이때, 만약 움직이지 못했을 때
    // 현재 격자 밖으로 나와있는지 확인
    // 어차피 격자 밖으로 나가있으면 Out
    bool isMoved = MoveDown(cur.center);
    if (isMoved) {
        cur.center.first += 1;
        return true;
    }
    else {
        isMoved = MoveLeft(cur.center);
    }

    if (isMoved) {
        cur.center.first += 1;
        cur.center.second -= 1;
        cur.exitDir = (cur.exitDir + 3) % 4;
        return true;
    }
    else {
        isMoved = MoveRight(cur.center);
    }

    if (isMoved) {
        //right
        cur.center.first += 1;
        cur.center.second += 1;
        cur.exitDir = (cur.exitDir + 1) % 4;
        return true;
    }
    else 
        return false;

    return true;
}

bool MoveDown(pair<int, int> curGolem) {
    if (map[curGolem.first + 2][curGolem.second] == 0 && map[curGolem.first + 1][curGolem.second - 1] == 0 && map[curGolem.first + 1][curGolem.second + 1] == 0)
    {
        curGolem.first += 1;
        bool isInRange = InRange(curGolem);
        if (isInRange)
            return true;
    }
    return false;
}

bool InRange(pair<int, int> curGolem) {
    if (curGolem.first < 0 || curGolem.first >= R + 3 || curGolem.second < 0 || curGolem.second >= C) {
        return false;
    } // center 
    if (curGolem.first < 0 || curGolem.first >= R + 3 || curGolem.second - 1 < 0 || curGolem.second - 1 >= C) {
        return false;
    } // left
    if (curGolem.first < 0 || curGolem.first >= R + 3 || curGolem.second + 1 < 0 || curGolem.second + 1 >= C) {
        return false;
    } // right
    if (curGolem.first + 1 < 0 || curGolem.first + 1 >= R + 3 || curGolem.second < 0 || curGolem.second >= C) {
        return false;
    } // down
    if (curGolem.first - 1 < 0 || curGolem.first - 1 >= R + 3 || curGolem.second < 0 || curGolem.second >= C) {
        return false;
    } // top
     
    return true;
}

bool MoveLeft(pair<int, int> curGolem) {
    // 왼쪽으로 이동 후 MoveDown
    // 이동 시 출구의 방향이 바뀜(dir + 3 % 4)
    if (map[curGolem.first][curGolem.second - 2] == 0 && map[curGolem.first + 1][curGolem.second - 1] == 0 && map[curGolem.first - 1][curGolem.second - 1] == 0)
    {
        curGolem.second -= 1;
        bool isMoved = MoveDown(curGolem);
        if (isMoved)
            return true;
    }
    return false;
}

bool MoveRight(pair<int, int> curGolem) {
    // 오른쪽으로 이동 후 MoveDown (dir + 1 % 4) 
    if (map[curGolem.first][curGolem.second + 2] == 0 && map[curGolem.first + 1][curGolem.second + 1] == 0 && map[curGolem.first - 1][curGolem.second + 1] == 0)
    {
        curGolem.second += 1;
        bool isMoved = MoveDown(curGolem);
        if (isMoved)
            return true;
    }
    return false;
}

void SetMap() {
    map[cur.center.first][cur.center.second] = idx;
    map[cur.center.first + 1][cur.center.second] = idx;
    map[cur.center.first - 1][cur.center.second] = idx;
    map[cur.center.first][cur.center.second + 1] = idx;
    map[cur.center.first][cur.center.second - 1] = idx;
    isExit[cur.center.first + dirX[cur.exitDir]][cur.center.second + dirY[cur.exitDir]] = true;
    idx += 1;
}

void MoveSoul() {
    // 가장 아래로 내려갈 수 있는 거리 측정 후 + result
    int maxRow = BFS(cur.center);
    result += maxRow;
}

int BFS(pair<int, int> start) {
    fill(visited[0], visited[0] + MaxSize * MaxSize, false);
    queue<pair<int, int>> que;
    que.push(start);
    int maxRow = start.first;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= R + 3 || next.second < 0 || next.second >= C)
                continue;
            if (visited[next.first][next.second])
                continue;
            if (map[next.first][next.second] == 0)
                continue;
            if (map[next.first][next.second] != map[cur.first][cur.second]) {
                if (!isExit[cur.first][cur.second])
                    continue;
            }
            que.push(next);
            visited[next.first][next.second] = true;
            maxRow = max(maxRow, next.first);
        }
    }

    return maxRow - 2;
}
