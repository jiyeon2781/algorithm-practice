#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 51;
const int Dir = 4;

void Start();
void Blizard(int d, int s);
bool Bomb();
void Change();
void Move(bool isInput);

int N, M;
int map[MaxSize][MaxSize];
int line[MaxSize * MaxSize];
int temp[MaxSize * MaxSize];
int bombCnt[4]{ 0,0,0,0 };
pair<int, int> shark;

int dirX[Dir] = { -1, 1, 0 ,0 };
int dirY[Dir] = { 0, 0, -1, 1 };
// ↑, ↓, ←, →

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

    shark = { (N - 1) / 2, (N - 1) / 2 };

    Start();
}

void Start() {
    int d, s;
    while (M--) {
        cin >> d >> s;
        Blizard(d - 1, s);

        // TODO 구슬 이동
        fill(line, line + MaxSize * MaxSize, 0);
        Move(false);

        // TODO 구슬 폭파 -> 폭발한 구슬 갯수 반영
        bool result = Bomb();
        while (result) {
            result = Bomb();
        }
        // TODO 구슬 변화
        Change();

        fill(map[0], map[0] + MaxSize * MaxSize, 0);
        Move(true);
    }
    // 결과 출력

    int sum = 0;
    for (int i = 1; i < 4; i++) {
        sum += (i * bombCnt[i]);
    }
    cout << sum;
}

void Blizard(int d, int s) {
    for (int i = 1; i <= s; i++) {
        pair<int, int> next = { shark.first + dirX[d] * i, shark.second + dirY[d] * i };
        map[next.first][next.second] = 0;
    }
}

void Move(bool isInput) {
    int moveDirIdx[Dir] = { 2, 1, 3, 0 };
    int length = 1, cnt = 0;
    int moveIdx = 0, lineIdx = 0;
    pair<int, int> cur = shark; // 시작점

    while (true) {
        if (cnt >= 2 && length < N - 1) {
            cnt = 0;
            length += 1;
        }

        int curLength = length;

        while (curLength--) {
            pair<int, int> next = { cur.first + dirX[moveDirIdx[moveIdx]], cur.second + dirY[moveDirIdx[moveIdx]] };
            if (!isInput)
            {
                if (map[next.first][next.second] >= 1) line[lineIdx++] = map[next.first][next.second];
            }
            else {
                map[next.first][next.second] = line[lineIdx++];
            }
                
            cur = next;
        }

        cnt += 1;
        moveIdx = (moveIdx + 1) % Dir;

        if (cnt >= 3 && length == N - 1) break;
    }
}

bool Bomb() {
    int prev = line[0];
    int startIdx = 0;
    int cnt = 1;
    bool result = false;

    for (int i = 1; i < N * N; i++) {
        if (line[i] == 0) continue;

        if (prev != line[i]) {
            // 같지 않을 때
            if (cnt >= 4) {
                // Bomb
                result = true;

                // 0으로 변경
                for (int cur = startIdx; cur < i; cur++) line[cur] = 0;
                // 폭발 개수 반영
                bombCnt[prev] += cnt;
            }
            startIdx = i;
            prev = line[i];
            cnt = 1;
        }
        else {
            // 같을 떄
            cnt += 1;
        }
    }

    if (cnt >= 4) {
        result = true;
        for (int cur = startIdx; cur < N * N; cur++) line[cur] = 0;
        bombCnt[prev] += cnt;
    }
    
    return result;
}

void Change() {
    fill(temp, temp + MaxSize * MaxSize, 0);

    int prev = line[0];
    int cnt = 1;
    int tempIdx = 0;
    

    for (int i = 1; i < N * N; i++) {
        if (line[i] == 0) continue;

        if (prev != line[i]) {
            if (prev != 0) {
                temp[tempIdx++] = cnt;
                temp[tempIdx++] = prev;
            }
            
            prev = line[i];
            cnt = 1;
        }
        else {
            cnt += 1;
        }
    }

    if (prev != 0) {
        temp[tempIdx++] = cnt;
        temp[tempIdx++] = prev;
    }

    for (int i = 0; i < N * N; i++) line[i] = temp[i];
}