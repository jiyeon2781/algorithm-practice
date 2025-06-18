#include <iostream>
#include <cmath>

using namespace std;

void TurnWheel(int idx, int dir);

string wheels[4];
bool isEnd[4];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < 4; i++) cin >> wheels[i];

	int t;
	cin >> t;

	int idx, dir;
	// -1 : 반시계, 1 : 시계

	string cur[4];
	for (int i = 0; i < t; i++) {
		cin >> idx >> dir;
		idx -= 1;
		// Init
		for (int j = 0; j < 4; j++) cur[j] = wheels[j];
		
		TurnWheel(idx, dir);

		int left = idx, right = idx;
		int curDir = dir;
		// 왼쪽
		while (left >= 1) {
			if (cur[left][6] == cur[left - 1][2]) break;
			TurnWheel(left - 1, -curDir);
			left -= 1;
			curDir = -curDir;
		}

		curDir = dir;
		// 오른쪽
		while (right <= 2) {
			if (cur[right][2] == cur[right + 1][6]) break;
			TurnWheel(right + 1, -curDir);
			right += 1;
			curDir = -curDir;
		}
	}

	int result = 0;
	for (int i = 0; i < 4; i++) {
		if (wheels[i][0] == '1') result += pow(2, i);
	}
	cout << result;
}

void TurnWheel(int idx, int dir) {
	if (dir == -1) wheels[idx] = wheels[idx].substr(1) + wheels[idx][0];
	else wheels[idx] = wheels[idx][7] + wheels[idx].substr(0, wheels[idx].size() - 1);
}