#include <iostream>
#include <vector>

using namespace std;

struct Info {
	int number;
	int dir;
};

struct Shark {
	int x, y;
	int dir;
};

const int Dir = 8;
const int Max = 4;

void Backtracking(vector<vector<Info>> cur, Shark curShark, int curCnt);
vector<vector<Info>> MoveFishes(vector<vector<Info>> cur, Shark curShark);

int dirX[Dir] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirY[Dir] = { 0, -1, -1, -1, 0, 1, 1, 1 };
bool deadFish[Max * Max + 1];

int result = 0;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	vector<vector<Info>> map;
	Shark shark;

	int num, dir;
	for (int i = 0; i < Max; i++) {
		vector<Info> curLine;
		for (int j = 0; j < Max; j++) {
			cin >> num >> dir;
			curLine.push_back({ num, dir - 1 });
		}
		map.push_back(curLine);
	}

	deadFish[map[0][0].number] = true;
	int cnt = map[0][0].number;
	shark = { 0, 0, map[0][0].dir };
	map[0][0].number = -1;

	Backtracking(map, shark, cnt);

	cout << result;
}

void Backtracking(vector<vector<Info>> cur, Shark curShark, int curCnt) {
	// Move Fishes
	// return Fishes map
	vector<vector<Info>> next = MoveFishes(cur, curShark);

	// Move Shark -> 이동할 수 없으면 break(result 비교)
	pair<int, int> nextSharkMove;
	int move = 1;
	while (true) {
		nextSharkMove = { curShark.x + dirX[curShark.dir] * move, curShark.y + dirY[curShark.dir] * move };
		if (nextSharkMove.first < 0 || nextSharkMove.first >= Max || nextSharkMove.second < 0 || nextSharkMove.second >= Max) {
			result = max(result, curCnt);
			break;
		}

		move += 1;

		// 이동할 수 있다고 판단
		// Backtracking
		Shark nextShark = { nextSharkMove.first , nextSharkMove.second, next[nextSharkMove.first][nextSharkMove.second].dir };
		int deadFishNum = next[nextShark.x][nextShark.y].number;
		if (deadFishNum == -1) continue;
		// 빈칸이므로 이동 불가능

		curCnt += next[nextShark.x][nextShark.y].number;
		deadFish[next[nextShark.x][nextShark.y].number] = true;
		next[nextShark.x][nextShark.y].number = -1;
		Backtracking(next, nextShark, curCnt);
		next[nextShark.x][nextShark.y].number = deadFishNum;
		deadFish[next[nextShark.x][nextShark.y].number] = false;
		curCnt -= next[nextShark.x][nextShark.y].number;
	}
}

vector<vector<Info>> MoveFishes(vector<vector<Info>> cur, Shark curShark) {
	for (int idx = 1; idx <= Max * Max; idx++) {
		if (deadFish[idx]) continue;
		Info curFish;
		pair<int, int> curCoord;
		for (int i = 0; i < Max; i++) {
			for (int j = 0; j < Max; j++) {
				if (cur[i][j].number == idx) {
					curFish = cur[i][j];
					curCoord = { i, j };
				}
			}
		}
		
		pair<int, int> next;
		int curDir = curFish.dir;

		// Move curFish
		do {
			next = { curCoord.first + dirX[curDir], curCoord.second + dirY[curDir] };
			// 다음 좌표가 상어가 아니고 범위를 벗어나지 않을 때
			if (curShark.x != next.first || curShark.y != next.second) {
				if (next.first >= 0 && next.first < Max && next.second >= 0 && next.second < Max) {
					// 물고기 이동(Swap)
					Info temp = curFish;
					temp.dir = curDir;
					cur[curCoord.first][curCoord.second] = cur[next.first][next.second];
					cur[next.first][next.second] = temp;
					break;
				}
			}
			curDir = (curDir + 1) % Dir;
			// 45도 반시계 방향
		} while (curDir != curFish.dir);
	}

	return cur;
}
