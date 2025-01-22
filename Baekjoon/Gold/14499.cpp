#include <iostream>
#include <algorithm>
#include <queue>
#include <iterator>

using namespace std;


void MoveDice(pair<int, int> start, int N, int M);

const int MaxSize = 21;
const int DiceIdx = 6;
const int Dir = 4;

int map[MaxSize][MaxSize];
queue<int> directions;

int dirX[Dir] = { 0, 0, -1, 1 };
int dirY[Dir] = { 1, -1, 0, 0 };

int dice[DiceIdx] = { 0, 0, 0, 0, 0, 0 };
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, x, y, K;
    cin >> N >> M >> x >> y >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    int num;

    while (K--) {
        cin >> num;
        directions.push(num);
    }

    MoveDice({x, y}, N, M);
}

void MoveDice(pair<int, int> start, int N, int M) {
    pair<int, int> cur = start, next;
    int temp, dir;

    while (!directions.empty()) {

        dir = directions.front();
        directions.pop();

        next = { cur.first + dirX[dir - 1], cur.second + dirY[dir - 1] };
        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= M) continue;
        
        int temp[DiceIdx];
        copy_n(dice, DiceIdx, temp);
        if (dir == 1) { // 동쪽
            int idx[DiceIdx] = { 2, 0, 5, 3, 4, 1 };
            for (int i = 0; i < DiceIdx; i++) dice[i] = temp[idx[i]];
        }
        else if (dir == 2) { // 서쪽
            int idx[DiceIdx] = { 1, 5, 0, 3, 4, 2 };
            for (int i = 0; i < DiceIdx; i++) dice[i] = temp[idx[i]];
        }
        else if (dir == 3) { // 북쪽
            int idx[DiceIdx] = { 4, 1, 2, 0, 5, 3 };
            for (int i = 0; i < DiceIdx; i++) dice[i] = temp[idx[i]];
        }
        else { // 남쪽
            int idx[DiceIdx] = { 3, 1, 2, 5, 0, 4 };
            for (int i = 0; i < DiceIdx; i++) dice[i] = temp[idx[i]];
        }

        if (map[next.first][next.second] == 0) map[next.first][next.second] = dice[5];
        else {
            dice[5] = map[next.first][next.second];
            map[next.first][next.second] = 0;
        }

        cout << dice[0] << "\n";

        cur = next;
    }
}
