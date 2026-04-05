#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct TeamInfo {
	pair<int, int> head;
	pair<int, int> tail;
};

struct BallInfo {
	pair<int, int> start;
	int dir;
};

void Start();
void SaveInfos();
void SaveInfo(pair<int, int> start, int idx);
void MoveTeams();
void Move(int idx);
BallInfo GetBallMoveInfo(int round);
void BallMove(BallInfo ball);
int AddScore(pair<int, int> cur);

const int MaxSize = 21;
const int MaxTeamCnt = 6;
const int Dir = 4;

int result = 0;
int n, m, k;

bool visited[MaxSize][MaxSize];
int cost[MaxSize][MaxSize];
int map[MaxSize][MaxSize];
int teamIdx[MaxSize][MaxSize];
TeamInfo teams[MaxTeamCnt];

int dirX[Dir] = { 0, -1, 0, 1 };
int dirY[Dir] = { 1, 0, -1, 0 };
// 오, 위, 왼, 아래

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> k;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	SaveInfos();
	Start();

	return 0;
}

void SaveInfos() {
	int idx = 1;
	fill(visited[0], visited[0] + MaxSize * MaxSize, false);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1)
				SaveInfo({ i, j }, idx++);
		}
	}
}

void SaveInfo(pair<int, int> start, int idx) {
	teamIdx[start.first][start.second] = idx;
	visited[start.first][start.second] = true;
	TeamInfo team;
	team.head = start;
	queue <pair<int, int>> que;
	que.push(start);

	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();

		for (int i = 0; i < Dir; i++) {
			pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
			if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
				continue;
			if (map[next.first][next.second] != 2 && map[next.first][next.second] != 3)
				continue;
			if (visited[next.first][next.second])
				continue;

			teamIdx[next.first][next.second] = idx;
			if (map[next.first][next.second] == 3) {
				team.tail = next;
				teams[idx] = team;
			}
			que.push(next);
			visited[next.first][next.second] = true;
		}
	}
}

void Start() {
	for (int i = 0; i < k; i++) {
		MoveTeams();
		// 한 라운드 마다 이동

		auto curBall = GetBallMoveInfo(i);
		// 현재 공의 정보 얻기
	
		/*
		// 디버그: 라운드마다 각 팀 head/tail 위치 출력
		for (int t = 1; t <= m; t++) {
			cout << "Round " << i << " Team " << t
				<< " head:(" << teams[t].head.first << "," << teams[t].head.second << ")"
				<< " tail:(" << teams[t].tail.first << "," << teams[t].tail.second << ")"
				<< " score:" << result << "\n";
		}
		*/
		BallMove(curBall);
		// 해당 공을 바탕으로 던져서 점수 터득
	}

	cout << result;
}

void MoveTeams() {
	for (int i = 1; i <= m; i++) {
		Move(i);
	}
}

void Move(int idx) {
	fill(visited[0], visited[0] + MaxSize * MaxSize, false);
	TeamInfo team = teams[idx];
	pair<int, int> nextHead;

	for (int i = 0; i < Dir; i++) {
		pair<int, int> next = { team.head.first + dirX[i], team.head.second + dirY[i] };
		if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
			continue;
		if (map[next.first][next.second] == 0)
			continue;

		if (map[next.first][next.second] == 4 || map[next.first][next.second] == 3) {
			map[next.first][next.second] = 1;
			teamIdx[next.first][next.second] = idx;
			map[team.head.first][team.head.second] = 2;
			nextHead = next;
			break;
		}
	}

	for (int i = 0; i < Dir; i++) {
		pair<int, int> next = { team.tail.first + dirX[i], team.tail.second + dirY[i] };
		if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
			continue;
		if (map[next.first][next.second] == 0)
			continue;

		if (map[next.first][next.second] == 2) {
			if (next.first == team.head.first && next.second == team.head.second)
				continue;

			map[next.first][next.second] = 3;
			if (team.tail.first != nextHead.first || team.tail.second != nextHead.second) {
				map[team.tail.first][team.tail.second] = 4;
				teamIdx[team.tail.first][team.tail.second] = 0;
			}

			teams[idx].tail = next;
			break;
		}
	}
	teams[idx].head = nextHead;
}

BallInfo GetBallMoveInfo(int round) {
	auto curRound = round;
	BallInfo resBall;
	if (round >= n * 4) {
		auto cur = round / (n * 4);
		curRound = round - (n * 4) * cur;
	}

	int mod = curRound % n;
	int div = curRound / n;

	resBall.dir = div;

	switch (div) {
	case 0:
		resBall.start = { mod, 0 };
		break;
	case 1:
		resBall.start = { n - 1, mod };
		break; 
	case 2:
			resBall.start = { n - 1 - mod, n - 1 };
			break;
		case 3:
			resBall.start = { 0, n - 1 - mod };
			break;
	}

	return resBall;
}

void BallMove(BallInfo ball) {
	int dir = ball.dir;
	pair<int, int> cur = ball.start;

	while (true) {
		if (map[cur.first][cur.second] != 0 && map[cur.first][cur.second] != 4) {
			// 점수 터득
			int score = AddScore(cur);
			result += score;

			// 방향 전환
			int idx = teamIdx[cur.first][cur.second];
			map[teams[idx].head.first][teams[idx].head.second] = 3;
			map[teams[idx].tail.first][teams[idx].tail.second] = 1;

			pair<int, int> temp = teams[idx].head;
			teams[idx].head = teams[idx].tail;
			teams[idx].tail = temp;

			break;
		}
		cur = { cur.first + dirX[dir], cur.second + dirY[dir] };
		if (cur.first < 0 || cur.first >= n || cur.second < 0 || cur.second >= n)
			break;
	}
}

int AddScore(pair<int, int> target) {
	fill(cost[0], cost[0] + MaxSize * MaxSize, 0);
	int idx = teamIdx[target.first][target.second];
	TeamInfo team = teams[idx];
	pair<int, int> start = teams[idx].head;
	cost[start.first][start.second] = 1;
	queue<pair<int, int>> que;
	que.push(start);

	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();

		if (cur.first == target.first && cur.second == target.second)
			return cost[cur.first][cur.second] * cost[cur.first][cur.second];

		for (int i = 0; i < Dir; i++) {
			pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
			if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
				continue;
			if (cost[next.first][next.second] > 0 || map[next.first][next.second] == 4 || map[next.first][next.second] == 0)
				continue;
			if (map[cur.first][cur.second] == 1 && map[next.first][next.second] == 3)
				continue;

			cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
			que.push(next);
			break;
		}
	}
}