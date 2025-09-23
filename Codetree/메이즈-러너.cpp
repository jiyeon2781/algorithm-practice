#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct SquareInfo {
    pair<int, int> start;
    int size;
};

struct PersonInfo {
    pair<int, int> cord;
    int index;
};

const int MaxSize = 11;
const int Dir = 4;

bool MovePersons();
pair<int, int> MovePerson(pair<int, int> person);
SquareInfo MakeSquares();
int GetDistance(pair<int, int> start, pair<int, int> end);
bool MakeSquare(pair<int, int> start, int size);
void RotationMaze();


int N, M, K;

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, -1, 1};
int map[MaxSize][MaxSize];

pair<int, int> mapExit;
vector<pair<int, int>> persons;
bool isSucceed[MaxSize];
queue< PersonInfo> rotationPersons;
int moveCnt = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    int x, y;

    while (M--) {
        cin >> x >> y;
        persons.push_back({ x - 1, y - 1 });
    }

    cin >> mapExit.first >> mapExit.second;
    mapExit.first -= 1;
    mapExit.second -= 1;

    while (K--) {
        bool isFinished = MovePersons();
        RotationMaze();
    }

    cout << moveCnt << "\n";
    cout << mapExit.first + 1 << ' ' << mapExit.second + 1 << "\n";

    return 0;
}

bool MovePersons() {
    bool complete = true;
    for (int i = 0; i < persons.size(); i++) {
        if (isSucceed[i])
            continue;
        complete = false;
        pair<int, int> next = MovePerson(persons[i]);
        persons[i] = next;

        if (next == mapExit)
            isSucceed[i] = true;
    }
    return complete;
}

pair<int, int> MovePerson(pair<int, int> person) {
    int curDist = GetDistance(person, mapExit);
    for (int i = 0; i < Dir; i++) {
        pair<int, int> next = { person.first + dirX[i], person.second + dirY[i] };
        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
            continue;
        if (map[next.first][next.second] > 0)
            continue;
        
        int nextDist = GetDistance(next, mapExit);
        if (nextDist > curDist)
            continue;

        moveCnt += 1;
        return next;
    }
    return person;
}

int GetDistance(pair<int, int> start, pair<int, int> end) {
    return abs(start.first - end.first) + abs(start.second - end.second);
}

SquareInfo MakeSquares() {
    int size = 2;
    bool isFinish = false;
    SquareInfo info = { {-1, -1}, N };

    while (size) {
        if (size == N + 1)
            break;

        for (int i = mapExit.first - size + 1; i <= mapExit.first; i++) {
            for (int j = mapExit.second - size + 1; j <= mapExit.second; j++) {
                if (i < 0 || i >= N || j < 0 || j >= N)
                    continue;
                isFinish = MakeSquare({i, j}, size);
                if (isFinish) {
                    info = { {i, j}, size };
                    break;
                }
            }
            if (isFinish)
                break;
        }

        if (isFinish) break;
        size += 1;
    }

    return info;
}

bool MakeSquare(pair<int, int> start, int size) {
    int cnt = 0;

    for (int i = start.first; i < start.first + size; i++) {
        for (int j = start.second; j < start.second + size; j++) {
            if (i < 0 || i >= N || j < 0 || j >= N) {
                while (!rotationPersons.empty()) {
                    rotationPersons.pop();
                }
                return false;
            }

            for (int idx = 0; idx < persons.size(); idx++) {
                if (isSucceed[idx])
                    continue;
                if (persons[idx].first == i && persons[idx].second == j) {
                    rotationPersons.push({ { i, j }, idx });
                    cnt += 1;
                }
            }
        }
    }

    if (cnt > 0)
        return true;
    return false;
}

int temp[MaxSize][MaxSize];

void RotationMaze() {
    SquareInfo square = MakeSquares();
    if (square.start.first == -1)
        return;
    pair<int, int> start = square.start;

    fill(temp[0], temp[0] + MaxSize * MaxSize, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = map[i][j];
        }
    }
    bool isModify = false;

    for (int i = 0; i < square.size; i++) {
        for (int j = 0; j < square.size; j++) {
            if (map[i + start.first][j + start.second] > 0) {
                map[i + start.first][j + start.second] -= 1;
            }

            temp[j + start.first][square.size - 1 - i + start.second] = map[i + start.first][j + start.second];
            if (mapExit.first == i + start.first && mapExit.second == j + start.second && !isModify) {
                mapExit = { j + start.first, square.size - 1 - i + start.second };
                isModify = true;
            }
        }
    }

    while (!rotationPersons.empty()) {
        PersonInfo cur = rotationPersons.front();

        isModify = false;
        for (int i = 0; i < square.size; i++) {
            for (int j = 0; j < square.size; j++) {
                if (i + start.first == cur.cord.first && j + start.second == cur.cord.second) {
                    persons[cur.index] = { j + start.first, square.size - 1 - i + start.second };
                    isModify = true;
                    break;
                }
            }
            if (isModify)
                break;
        }

        rotationPersons.pop();
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = temp[i][j];
        }
    }
}
