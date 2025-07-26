#include <iostream>
#include <queue>

using namespace std;

void Start();
void Firestorm(int Q);
void MoveMap(int size);
void RegionMove(int x, int y, int size);
void MeltIce(int x, int y);
int CountIce();
void Init();
int BFS(int x, int y);

const int MaxSize = (1 << 6);
const int Dir = 4;

int N, L, mapSize;
int map[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1 };

queue<pair<int, int>> melting;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> L;

	mapSize = (1 << N);

	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cin >> map[i][j];
		}
	}

	Start();
}

void Start() {
	int Q;

	while (L--) {
		cin >> Q;

		Firestorm(Q);
	}

	int cnt = 0, region = 0;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (map[i][j] <= 0) continue;
			cnt += map[i][j];
		}
	}
	region = CountIce();
	
	cout << cnt << "\n" << region;
}

void Firestorm(int Q) {
	MoveMap(1 << Q);
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (map[i][j] <= 0) 
				continue;
			MeltIce(i, j);
		}
	}

	while (!melting.empty()) {
		pair<int, int> melt = melting.front();
		melting.pop();
		map[melt.first][melt.second] -= 1;
	}
}

int tempMap[MaxSize][MaxSize];

void MoveMap(int size) {
	// (x, y) -> (y, 2^L - x)
	// 반시계 방향
	for (int i = 0; i < mapSize; i += size) {
		for (int j = 0; j < mapSize; j += size) {
			RegionMove(i, j, size);
		}
	}
	Init();
}

void Init() {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			map[i][j] = tempMap[i][j];
		}
	}
}

void RegionMove(int x, int y, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tempMap[j + x][size - 1 - i + y] = map[i + x][j + y];
		}
	}
}

void MeltIce(int x, int y) {
	// 얼음과 인접하지 않으면 얼음의 양이 줄어듦
	int cnt = 0;
	for (int i = 0; i < Dir; i++) {
		pair<int, int> neighbor = { x + dirX[i], y + dirY[i] };
		if (neighbor.first < 0 || neighbor.first >= mapSize || neighbor.second < 0 || neighbor.second >= mapSize)
			continue;
		if (map[neighbor.first][neighbor.second] >= 1)
			cnt += 1;
	}
	if (cnt < 3) melting.push({ x, y });
}

int CountIce() {
	// 최대 덩어리 구하기
	int maxNum = 0;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (visited[i][j] || map[i][j] <= 0) continue;
			int cur = BFS(i, j);
			maxNum = max(cur, maxNum);
		}
	}
	return maxNum;
}

int BFS(int x, int y) {
	int cnt = 0;
	queue<pair<int, int>> que;
	que.push({ x, y });
	visited[x][y] = true;

	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();

		cnt += 1;

		for (int i = 0; i < Dir; i++) {
			pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
			if (next.first < 0 || next.first >= mapSize || next.second < 0 || next.second >= mapSize)
				continue;
			if (map[next.first][next.second] <= 0 || visited[next.first][next.second])
				continue;
			visited[next.first][next.second] = true;
			que.push(next);
		}
	}

	return cnt;
}