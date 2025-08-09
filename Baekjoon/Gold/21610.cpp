#include <iostream>
#include <queue>

using namespace std;

void Start();
void MoveAndRemoveClouds(int d, int s);
void WaterCopy();
void CreateClouds();
int SumWaters();

const int MaxSize = 51;
const int Dir = 8;

int N;

int map[MaxSize][MaxSize]; // 비의 양
bool visited[MaxSize][MaxSize]; // 구름이 지나간 자리

int dirX[Dir] = {0, -1, -1, -1, 0, 1, 1, 1};
int dirY[Dir] = {-1, -1, 0, 1, 1, 1, 0, -1};
// ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 

queue<pair<int, int>> moves, clouds, movedClouds;


int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int M;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int d, s;

	while (M--) {
		cin >> d >> s;
		moves.push({ d - 1, s });
	}

	// Init Cloud
	clouds.push({ N - 1, 0 });
	clouds.push({ N - 1, 1 });
	clouds.push({ N - 2, 0 });
	clouds.push({ N - 2, 1 });

	// Start
	Start();
}

void Start() {
	while (!moves.empty()) {
		fill(visited[0], visited[0] + MaxSize * MaxSize, false);

		pair<int, int> move = moves.front();
		moves.pop();
		
		MoveAndRemoveClouds(move.first, move.second);
		WaterCopy();
		CreateClouds();
	}

	cout << SumWaters();
}

void MoveAndRemoveClouds(int d, int s) {
	while (!clouds.empty()) {
		int x = clouds.front().first, y = clouds.front().second;
		clouds.pop();
		// 구름 삭제

		int nextX = x + dirX[d] * s, nextY = y + dirY[d] * s;
		while (nextX < 0) nextX += N;
		while (nextY < 0) nextY += N;
		nextX %= N;
		nextY %= N;
		// d 방향 s 칸으로 이동

		map[nextX][nextY] += 1;
		visited[nextX][nextY] = true;
		movedClouds.push({ nextX, nextY });
		// 각 구름의 칸 바구니에 물의 양 증가
	}
}

void WaterCopy() {
	while (!movedClouds.empty()) {
		int x = movedClouds.front().first, y = movedClouds.front().second;
		movedClouds.pop();
		// 물이 증가한 칸에 물복사 버그

		int waters = 0;
		for (int i = 1; i < Dir; i += 2) {
			int nextX = x + dirX[i], nextY = y + dirY[i];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
			// 경계를 넘어가면 거리가 1이 아님
			if (map[nextX][nextY] >= 1) waters += 1;
		}
		// 대각선 방향으로 거리가 1인칸 물이 있는 바구니 수만큼 물의 양 증가(1, 3, 5, 7)

		map[x][y] += waters;
	}
}

void CreateClouds() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {	
		// 바구니의 저장된 물의 양이 2 이상인 모든 칸에 구름이 생김
		// 구름이 사라진 칸(Remove)에서는 생성되지 않음
			if (map[i][j] >= 2 && !visited[i][j]) {
				clouds.push({ i, j });
				map[i][j] -= 2;
			}
		}
	}
}

int SumWaters() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += map[i][j];
		}
	}
	return sum;
} 