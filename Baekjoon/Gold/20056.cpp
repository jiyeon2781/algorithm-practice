#include <iostream>
#include <queue>

using namespace std;

struct Fireball {
	int m;
	int s; 
	int d;
	bool isMove;
};

void Start();
void MoveFireball();
void SeparateFireball(int x, int y);
void Init();

int CountSize();

const int MaxSize = 50;
const int Dir = 8;

int dirX[Dir] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dirY[Dir] = {0, 1, 1, 1, 0, -1, -1, -1};

queue<Fireball> map[MaxSize][MaxSize];

int N, M, K;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin >> N >> M >> K;

	int x, y, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> m >> s >> d;
		map[x-1][y-1].push({ m, s, d });
	}

	Start();
}

void Start() {
	while (K--) {
		// 파이어볼 이동
		MoveFireball();

		// 맵 순회 -> 같은 칸 파이어볼 나눔
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j].size() >= 2)
					SeparateFireball(i, j);
			}
		}
	}

	cout << CountSize();
}

queue<Fireball> nextMap[MaxSize][MaxSize];

void MoveFireball() {
	Init();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].size() == 0) 
				continue;

			while (!map[i][j].empty()) {
				Fireball cur = map[i][j].front();
				map[i][j].pop();
				int nextX = i + dirX[cur.d] * cur.s;
				int nextY = j + dirY[cur.d] * cur.s;
				while (nextX < 0) nextX += N;
				while (nextY < 0) nextY += N;
				nextMap[nextX % N][nextY % N].push(cur);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = nextMap[i][j];
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			while (!nextMap[i][j].empty())
				nextMap[i][j].pop();
		}
	}
}


void SeparateFireball(int x, int y) {
	int sumM = 0, sumS = 0;
	int cnt = map[x][y].size();
	int oddCnt = 0, evenCnt = 0;

	while (!map[x][y].empty()) {
		Fireball cur = map[x][y].front();
		map[x][y].pop();

		sumM += cur.m;
		sumS += cur.s;
		if (cur.d % 2 == 0) evenCnt += 1;
		else oddCnt += 1;
	}

	if ((int) sumM / 5 < 1) return;

	bool allEvenOrOdd = oddCnt == cnt || evenCnt == cnt ? true : false;

	for (int i = 0; i < 4; i++) {
		int dir = i * 2 + 1;
		if (allEvenOrOdd)
			dir = i * 2;
		map[x][y].push({  (int) sumM / 5, (int) sumS / cnt, dir });
	}
}


int CountSize() {
	int count = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j].size() == 0)
				continue;

			while (!map[i][j].empty()) {
				count += map[i][j].front().m;
				map[i][j].pop();
			}
		}
	}

	return count;
}
