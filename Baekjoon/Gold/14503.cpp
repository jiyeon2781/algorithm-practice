#include <iostream>

using namespace std;

struct Info {
	int x;
	int y;
	int dir;
};

void StartCleanRoom();
void CleanCurrentRegion();
bool SearchNeighborRegion();
void MoveNextRegion(int dir);
bool MovePrevRegion();

const int Dir = 4;
const int MaxSize = 51;

int N, M, cnt = 0;
Info robot;

int map[MaxSize][MaxSize];

int dirX[Dir] = {-1, 0, 1, 0};
int dirY[Dir] = {0, 1, 0, -1};
// 북, 동, 남, 서

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	
	int x, y, dir;
	cin >> x >> y >> dir;
	robot = { x, y, dir };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	// 0 : 빈칸(청소 X)
	// 1 : 벽
	// 2 : 빈칸(청소 O)

	StartCleanRoom();
}

void StartCleanRoom() {
	while (true) {
		// 1. 현재 칸 상태 확인
		if (map[robot.x][robot.y] == 0)
			CleanCurrentRegion();

		// 2. 주변 4칸 확인
		bool isEnd = SearchNeighborRegion();
		if (isEnd) break;
	}

	cout << cnt;
}

void CleanCurrentRegion() {
	// 현재 칸 청소
	map[robot.x][robot.y] = 2;
	cnt += 1;
}

bool SearchNeighborRegion() {
	// 주변 4칸 확인
	int cur;

	for (int i = 0; i < Dir; i++) {
		cur = (robot.dir + 3 - i) % Dir;
		int nextX = robot.x + dirX[cur], nextY = robot.y + dirY[cur];
		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
		if (map[nextX][nextY] == 0) {
			// 청소를 하지 않았으면 이동 후 함수 종료
			MoveNextRegion(cur);
			return false;
		}
	}

	// 청소할 공간이 없으면 후진
	return MovePrevRegion();
}

void MoveNextRegion(int dir) {
	robot.x += dirX[dir];
	robot.y += dirY[dir];
	robot.dir = dir;
}

bool MovePrevRegion() {
	pair<int, int> move = { -dirX[robot.dir], -dirY[robot.dir] };
	pair<int, int> next = { robot.x + move.first, robot.y + move.second };

	if (map[next.first][next.second] == 1) return true;
	// 청소기의 뒷편에 벽이 존재할 경우, 종료
	
	robot.x = next.first;
	robot.y = next.second;

	return false;
}