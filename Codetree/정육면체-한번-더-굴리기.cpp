#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct CubeInfo {
	int x;
	int y;
	int dir;
	int bottom;
	vector<int> Sections; // 옆면 숫자
// 밑면 기준 오른쪽, 위, 왼쪽, 아래
};

void CalculateSectionCost(); 
void SetMapCost(pair<int, int> start, int cnt);
int BFS(pair<int, int> start, int idx);
void Start();
void Move();
void Plus();
void Rotation();

CubeInfo cube;

const int MaxSize = 21;

int map[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];

int dirX[4] = {0, 1, 0, -1};
int dirY[4] = { 1, 0, -1, 0 };
// 오른쪽, 아래, 왼쪽, 위 이동
//반시계로 저장됨

int n, m;

vector<vector<int>> sideSection = 
{ {3, 2, 4, 5}, {3, 6, 4, 1}, {1, 5, 6, 2}, {1, 2, 6, 5}, {3, 1, 4, 6}, {3, 5, 4, 2} };

int result = 0;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	vector<int> section = { 3, 5, 4, 2 };
	cube = { 0, 0, 0, 6, section };
	
	Start();

	return 0;
}

void Start() {
	CalculateSectionCost();
	for (int i = 0; i < m; i++) {
		Move();
		// 큐브 이동
		Plus();
		// 아랫면과 칸 계산
		Rotation();
		// 아랫면과 현재 칸 크기 대조 및 rotation
	}
	cout << result;
}
void CalculateSectionCost() {
	// 1. 바닥 구역의 값을 미리 구해서 Plus에서는 더하기만 함
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (cost[i][j] == 0) {
				auto cnt = BFS({ i, j }, map[i][j]);
				SetMapCost({ i, j }, cnt * map[i][j]);
			}
		}
	}
}

void SetMapCost(pair<int, int> start, int cnt) {
	queue<pair<int, int>> que;
	que.push(start);
	cost[start.first][start.second] = cnt;

	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
			if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
				continue;
			// 범위를 벗어남
			if (cost[next.first][next.second] > 0)
				continue;
			// 이미 cost 존재
			if (!visited[next.first][next.second])
				continue;
			// 아까 방문한 곳이 아님

			que.push(next);
			cost[next.first][next.second] = cnt;
		}
	}
}

int BFS(pair<int, int> start, int idx) {
	fill(visited[0], visited[0] + MaxSize * MaxSize, false);
	queue<pair<int, int>> que;
	que.push(start);
	int cnt = 1;
	visited[start.first][start.second] = true;
	
	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
			if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
				continue;
			// 범위를 벗어남
			if (visited[next.first][next.second])
				continue;
			// 이미 방문함
			if (map[next.first][next.second] != idx)
				continue;
			// 같은 idx가 아님

			cnt += 1;
			que.push(next);
			visited[next.first][next.second] = true;
		}
	}

	return cnt;
}

void Move() {
	// 1. 윗면 계산
	// 2. dir 방향에 따른 윗면 위치 조정
	vector<int> newSection(4);

	int top = 7 - cube.bottom;
	int dir = cube.dir;
	int bottom = cube.bottom;

	// 3. 좌표 갱신 
	pair<int, int> next = { cube.x + dirX[dir], cube.y + dirY[dir] };
	
	// 3-1. 만약 큐브가 경계를 벗어나면 dir + 2 % 4 후 새로 next 저장
	if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n) {
		dir = (dir + 2) % 4;
		next = { cube.x + dirX[dir], cube.y + dirY[dir] };
	}

	int newBottom = 0;

	// 4. section 저장
	// 5. 바닥 갱신
	int idx = 0;
	if (dir == 0) { // 오른쪽
		newBottom = cube.Sections[0];
		newSection[0] = top;
		idx = 0;
	}
	else if (dir == 1) { // 아래
		newBottom = cube.Sections[3];
		newSection[3] = top;
		idx = 3;

	}
	else if (dir == 2) { // 왼쪽
		newBottom = cube.Sections[2];
		newSection[2] = top;
		idx = 2;
	}
	else if (dir == 3) { // 위
		newBottom = cube.Sections[1];
		newSection[1] = top;
		idx = 1;
	}

	for (int i = 0; i < 4; i++) {
		if (sideSection[newBottom - 1][i] == top) {
			for (int j = 1; j <= 3; j++) {
				newSection[(idx + j) % 4] = sideSection[newBottom - 1][(i + j) % 4];
			}
			break;
		}
	}
	
	// 6. cube 새로 저장
	cube = { next.first, next.second, dir, newBottom, newSection };

}

void Plus() {
	// 1. 큐브 정보에서 x, y를 빼옴
	result += cost[cube.x][cube.y];
	// 2. 바닥 칸 cost 확인
}

void Rotation() {
	// 1. 현재 바닥면 및 bottom 크기 비교
	int curBottom = cube.bottom;
	int curMap = map[cube.x][cube.y];
	vector<int> newSection(4);

	if (curBottom > curMap) {
		// 2. bottom이 크면 90도 시계 방향 회전(dir + 1 % 4)
		cube.dir = (cube.dir + 1) % 4;
	}
	else if (curBottom < curMap) {
		// 3. bottom이 작으면 90도 반시계 방향 회전 (dir + 3 % 4)
		cube.dir = (cube.dir + 3) % 4;
	}
}