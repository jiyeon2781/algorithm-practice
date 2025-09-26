#include <iostream>
#include <queue>

using namespace std;

void Start();
void Step1(int curMinute);
void EndPerson(int idx);
int BFS(pair<int, int> start, pair<int, int> end, int idx);
void Step2(int curMinute);
void Step3(int curMinute);
bool End();

const int MaxSize = 16;
const int PersonCnt = 31;
const int Dir = 4;

int dirX[Dir] = { -1, 0, 0, 1 };
int dirY[Dir] = { 0, -1, 1, 0 };

int map[MaxSize][MaxSize];
// 1 : 베이스캠프
// 2 : 편의점
int occupy[MaxSize][MaxSize];
int temp[MaxSize][MaxSize];
pair<int, int> stores[PersonCnt];
pair<int, int> persons[PersonCnt];
bool arrivePerson[PersonCnt];

int N, M, minute;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    pair<int, int> store;
    for (int i = 1; i <= M; i++) {
        cin >> store.first >> store.second;
        store.first -= 1;
        store.second -= 1;
        stores[i] = store;
        map[store.first][store.second] = 2;
    }

    Start();

    return 0;
}

void Start() {
    minute = 0;
    while (End()) {
        minute += 1;
        Step1(minute);
        Step2(minute);
        if (minute <= M)
            Step3(minute);
    }

    cout << minute;
}

bool End() {
    for (int i = 1; i <= M; i++) {
        if (!arrivePerson[i])
            return true;
    }
    return false;
}

void Step1(int curMinute) {
    for (int i = 1; i <= M; i++) {
        if (curMinute <= i)
            continue;
        // 아직 베이스캠프에서 출발하지 못했을 때
        if (arrivePerson[i])
            continue;
        // 이미 도착했을 때

        int distance = BFS(persons[i], stores[i], i);

        pair<int, int> nextMoved = persons[i];
        for (int d = 0; d < Dir; d++) {
            pair<int, int> next = { persons[i].first + dirX[d], persons[i].second + dirY[d] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (map[next.first][next.second] == 1 && occupy[next.first][next.second] != 0)
                continue;
            if (map[next.first][next.second] == 2 && occupy[next.first][next.second] != i && occupy[next.first][next.second] != 0)
                continue;
            int moved = BFS(next, stores[i], i);

            if (moved == -1)
                continue;

            if (distance > moved) {
                nextMoved = next;
                distance = moved;
            }
        }
        // 본인이 가고싶은 편의점으로 한 칸 이동
        persons[i] = nextMoved;
    }
}


int BFS(pair<int, int> start, pair<int, int> end, int idx) {
    fill(temp[0], temp[0] + MaxSize * MaxSize, 0);
    queue<pair<int, int>> que;
    que.push(start);

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        if (cur.first == end.first && cur.second == end.second) {
            return temp[end.first][end.second];
        }

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (temp[next.first][next.second] != 0)
                continue;
            if (map[next.first][next.second] == 2 && occupy[next.first][next.second] != 0 && occupy[next.first][next.second] != idx)
                continue;
            if (map[next.first][next.second] == 1 && occupy[next.first][next.second] != 0)
                continue;
            // 베이스캠프나 편의점이 이미 먹혔을 때

            temp[next.first][next.second] = temp[cur.first][cur.second] + 1;
            que.push(next);
        }
    }

    return -1;
}

void Step2(int curMinute) {
    // 편의점 도착 여부 확인 및 잠금
    for (int i = 1; i <= M; i++) {
        if (arrivePerson[i] || curMinute <= i)
            continue;
        if (persons[i] == stores[i])
            EndPerson(i);

    }
}

void EndPerson(int idx) {
    occupy[persons[idx].first][persons[idx].second] = idx;
    arrivePerson[idx] = true;
}

void Step3(int curMinute) {
    // 베이스 캠프 이동 및 잠금
    int distance = 999999999;
    pair<int, int> min;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 1 && occupy[i][j] == 0) {
                int moved = BFS({ i, j }, stores[curMinute], curMinute);
                if (moved == -1)
                    continue;
                if (moved < distance) {
                    min = { i, j };
                    distance = moved;
                }

            }
        }
    }
    // person 좌표 세팅
    persons[curMinute] = min;
    occupy[min.first][min.second] = curMinute;
}