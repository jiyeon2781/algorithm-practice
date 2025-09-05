#include <iostream>
#include <queue>

using namespace std;

struct Info {
	bool isRobotHere;
	int Percent;
};

void Start();
void MoveBelt();
void InitTemp();
void MoveRobots();
void InputRobot();
void MoveRobot(int first, int second);
int IsAvailableCount();

const int MaxSize = 202;

int N, K;

Info belt[MaxSize];
Info temp[MaxSize];

int step = 1;

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> K;

	for (int i = 0; i < 2 * N; i++) 
		cin >> belt[i].Percent;

	Start();
}

void Start() {
	while (true) {
		// 벨트가 각 칸위에 있는 로봇과 함께 이동
		MoveBelt();
		// 가장 먼저 벨트에 올라간 로봇 부터 벨트가 회전하는 방향으로 이동할 수 있다면 이동
		//  - 이동 불가능 시 이동하지 않음
		//  - 이동하기 위한 조건 : 이동하려는 칸에 로봇 X 그 칸의 내구도가 1 이상 남아있어야 함
		MoveRobots();
		// 올리는 위치 칸 내구도가 0이 아니면 로봇을 올림
		InputRobot();
		// 내구도가 0인 칸의 개수가 K개 이상이라면 과정 종료
		if (IsAvailableCount() >= K) break;
		step += 1;
	}
	cout << step;

}

void InitTemp() {
	for (int i = 0; i < 2 * N; i++) 
		temp[i] = belt[i];
}

void MoveBelt() {
	InitTemp();

	for (int i = 0; i < 2 * N - 1; i++) {
		belt[i + 1] = temp[i];
		if (i + 1 >= N - 1) 
			belt[i + 1].isRobotHere = false;
	}
	belt[0] = temp[2 * N - 1];
}

void MoveRobots() {
	if (belt[N - 1].isRobotHere)
		belt[N - 1].isRobotHere = false;
	for (int i = N - 1; i > 0; i--) {
		if (!belt[i].isRobotHere && belt[i - 1].isRobotHere && belt[i].Percent > 0) {
			MoveRobot(i - 1, i);
		}
	}
}

void MoveRobot(int first, int second) {
	belt[second].isRobotHere = true;
	belt[first].isRobotHere = false;
	belt[second].Percent -= 1;
}

void InputRobot() {
	if (belt[0].Percent > 0)
	{
		belt[0].isRobotHere = true;
		belt[0].Percent -= 1;
	}
}

int IsAvailableCount() {
	int cnt = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (belt[i].Percent <= 0) cnt += 1;
	}
	return cnt;
}