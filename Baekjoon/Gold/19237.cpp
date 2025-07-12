#include <iostream>
#include <vector>

using namespace std;

struct Shark {
	int dir;
	int x;
	int y;
};

struct Info {
	int idx;
	int second;
};

void Start();
void RemainSharkSmell();
void SharkMove();
bool SharkIsExist(pair<int, int> cur, int idx);
bool IsDeadSharksWithoutFirst();

const int Dir = 4;
const int Max = 20;

int dirX[Dir] = {-1, 1, 0 ,0};
int dirY[Dir] = {0, 0, -1, 1};
// 위, 아래, 왼쪽, 오른쪽 (0, 1, 2, 3)

Info map[Max][Max];

Shark sharks[Max * Max + 1];
int seconds = 1;
int priority[Max * Max + 1][Dir][Dir];
int N, M, K;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin >> N >> M >> K;

	int num;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> num;
			if (num == 0) continue;
			sharks[num] = { 0, i, j };
		}
	} // Map

	for (int i = 1; i <= M; i++) {
		cin >> num;
		sharks[i].dir = num - 1;
	} // Sharks Direction

	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < Dir; j++) {
			for (int k = 0; k < Dir; k++) {
				cin >> priority[i][j][k];
				priority[i][j][k] -= 1;
			}
		}
	}

	Start();

}

void Start() {
	while (seconds <= 1000) {
		// 1. 상어 냄새 남기기
		RemainSharkSmell();

		// 2. 상어 이동
		SharkMove();

		// 3. 1번 상어만 남았는지 확인
		if (IsDeadSharksWithoutFirst()) {
			cout << seconds;
			return;
		}

		seconds += 1;
	}

	if (IsDeadSharksWithoutFirst()) cout << seconds;
	else cout << -1;
}

void RemainSharkSmell() {
	for (int i = 1; i <= M; i++) {
		if (sharks[i].x == -1 || sharks[i].y == -1) continue;
		// 이미 죽었으면 continue
		map[sharks[i].x][sharks[i].y] = { i, seconds };
	}
}

void SharkMove() {
	for (int i = 1; i <= M; i++) {
		if (sharks[i].x == -1 || sharks[i].y == -1) continue;
		// 이미 죽었으면 continue
		
		Shark prev = { -1, 0, 0 };
		bool isMove = false , isDead = false;

		// 냄새 확인
		for (int dir = 0; dir < Dir; dir++) {
			int nextX = sharks[i].x + dirX[priority[i][sharks[i].dir][dir]];
			int nextY = sharks[i].y + dirY[priority[i][sharks[i].dir][dir]];

			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
			Info next = map[nextX][nextY];
			// 다음 이동 할 곳

			// 냄새가 안나거나, 이미 없어진 냄새거나
			if (next.idx == 0 || seconds >= K + next.second) {
				// 이동후 이미 상어가 존재하는지
				if (!SharkIsExist({ nextX, nextY }, i)) {
					isDead = true;
					break;
				}
				// 우선순위 대로 이동
				sharks[i].x = nextX;
				sharks[i].y = nextY;
				sharks[i].dir = priority[i][sharks[i].dir][dir];
				isMove = true;
				break;
			}

			if (next.idx == i && prev.dir == -1) {
				prev = { priority[i][sharks[i].dir][dir], nextX, nextY };
			}
		}

		// 자기 자신이 냄새 남긴 칸으로 이동
		if (!isMove && !isDead) {
			if (prev.dir == -1) break;
			if (!SharkIsExist({ prev.x , prev.y }, i)) break;
			// 우선순위 대로 이동 -> 이동 시 냄새 남기기
			sharks[i].x = prev.x;
			sharks[i].y = prev.y;
			sharks[i].dir = prev.dir;
		}
	}
}

// 상어가 살아 남았는지 확인
bool SharkIsExist(pair<int,int> cur, int idx) {
	for (int i = 1; i <= M; i++) {
		if (sharks[i].x != cur.first || sharks[i].y != cur.second) continue;
		if (idx == i) continue;

		if (i < idx) {
			sharks[idx].x = -1;
			sharks[idx].y = -1;
			return false;
		}
		else {
			sharks[i].x = -1;
			sharks[i].y = -1;
			return true;
		}
	}
	return true;
}

bool IsDeadSharksWithoutFirst() {
	for (int i = 2; i <= M; i++) {
		if (sharks[i].x != -1 && sharks[i].y != -1) return false;
	}
	return true;
}