#include <iostream>
#include <queue>

using namespace std;

void Start();
void SpreadOfDust(int x, int y);
void Init();
void ActivateAirCleaner();
void MoveDust(vector<int> moves, int idx);
int DustCount();

const int MaxSize = 51;
const int Dir = 4;

int R, C, T;

int map[MaxSize][MaxSize];
int temp[MaxSize][MaxSize];

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1 };
// 아래, 위, 오른쪽, 왼쪽

pair<int, int> airCleaner[2];

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> R >> C >> T;

	int idx = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				airCleaner[idx++] = { i, j };
			}
		}
	}

	Start();
}

void Start() {
	while (T--) {
		fill(temp[0], temp[0] + MaxSize * MaxSize, 0);
		
		for (int i = 0; i < 2; i++) {
			temp[airCleaner[i].first][airCleaner[i].second] = -1;
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (map[i][j] >= 1)
					SpreadOfDust(i, j);
			}
		}
		Init();
		ActivateAirCleaner();
	}
	cout << DustCount();
}

void Init() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = temp[i][j];
		}
	}
}

void SpreadOfDust(int x, int y) {
	// 1. 미세먼지 확산
	int remain = 0, spread = (int) map[x][y] / 5;

	// 1-1. 인접한 네 방향으로 확산
	for (int i = 0; i < Dir; i++) {
		pair<int, int> neighbor = { x + dirX[i], y + dirY[i] };
		if (neighbor.first < 0 || neighbor.first >= R || neighbor.second < 0 || neighbor.second >= C)
			continue;
		if (map[neighbor.first][neighbor.second] == -1)
			continue;
		// 1-2. 인접한 방향에 공기청정기 존재 or 경계를 벗어나면 확산 X

		temp[neighbor.first][neighbor.second] += spread;
		remain += 1;
		// 1-3. 확산되는 양 : A/5 -> 소수점은 버림
		// 1-4. 해당 칸에 미세먼지 양은 A - A/5 * 확산된 방향 개수
	}
	temp[x][y] += map[x][y] - remain * spread;
}

void ActivateAirCleaner() {
	// 2. 공기 청정기 작동

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			temp[i][j] = map[i][j];
		}
	}

	// 오른쪽, 위, 왼쪽, 아래 (2 1 3 0)
	MoveDust({ 2, 1, 3, 0 }, 0);
	// 오른쪽, 아래, 왼쪽, 위 (2 0 3 1)
	MoveDust({ 2, 0, 3, 1 }, 1);

	Init();
}

void MoveDust(vector<int> moves, int idx) {
	pair<int, int> cur = { airCleaner[idx].first + dirX[moves[0]], airCleaner[idx].second + dirY[moves[0]]};
	temp[cur.first][cur.second] = 0;

	// 2-1. 위쪽 공기청정기 바람 : 반시계 방향 순환, 아래쪽 공기청정기 바람 : 시계 방향 순환
	// 2-2. 바람이 불면 미세먼지가 바람의 방향대로 모두 한칸씩 이동
	for (int i = 0; i < Dir; i++) {
		while (true) {
			pair<int, int> next = { cur.first + dirX[moves[i]], cur.second + dirY[moves[i]]};
			if (next.first < 0 || next.first >= R || next.second < 0 || next.second >= C)
				break;
			if (temp[next.first][next.second] == -1)
				break;
			temp[next.first][next.second] = map[cur.first][cur.second];
			cur = next;
		}
	}
}
int DustCount() {
	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] > 0) sum += map[i][j];
		}
	}
	return sum;
}