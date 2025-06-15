#include <iostream>

using namespace std;

int StartPathCount();
bool IsAWalkablePath(int startIdx, bool isHorizon);

const int MaxSize = 101;

int map[MaxSize][MaxSize];
bool isUsedSlope[MaxSize][MaxSize];
int N, L;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	cin >> N >> L;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cout << StartPathCount();
}

int StartPathCount() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (IsAWalkablePath(i, true)) cnt += 1;
		if (IsAWalkablePath(i, false)) cnt += 1;
	}
	return cnt;
}


bool IsAWalkablePath(int startIdx, bool isHorizon) {
	fill(isUsedSlope[0], isUsedSlope[0] + MaxSize * MaxSize, false);

	int cur = isHorizon ? map[startIdx][0] : map[0][startIdx];
	int next = isHorizon ? map[startIdx][1] : map[1][startIdx];

	int pos = 0;

	while (pos < N - 1) {
		int dif = cur - next;
		if (abs(dif) >= 2) return false;

		// 내리막 1 차이면
		if (dif == 1) {
			for (int idx = pos + 1; idx <= pos + L; idx++) {
				if (pos + L >= N) return false;

				if (isHorizon) {
					if (next != map[startIdx][idx] || isUsedSlope[startIdx][idx]) return false;
					isUsedSlope[startIdx][idx] = true;
				}
				else {
					if (next != map[idx][startIdx] || isUsedSlope[idx][startIdx]) return false;
					isUsedSlope[idx][startIdx] = true;
				}
			}
			cur = isHorizon ? map[startIdx][pos + L] : map[pos + L][startIdx];
			next = isHorizon ? map[startIdx][pos + L + 1] : map[pos + L + 1][startIdx];

			pos += L;
			continue;
		}
		else if (dif == -1) {
			// 오르막 1 차이면
			for (int idx = pos - L + 1; idx <= pos; idx++) {
				if (idx < 0) return false;

				if (isHorizon) {
					if (cur != map[startIdx][idx] || isUsedSlope[startIdx][idx]) return false;
					isUsedSlope[startIdx][idx] = true;
				}
				else {
					if (cur != map[idx][startIdx] || isUsedSlope[idx][startIdx]) return false;
					isUsedSlope[idx][startIdx] = true;
				}
			}
		}

		cur = next;
		next = isHorizon ? map[startIdx][pos + 2] : map[pos + 2][startIdx];
		pos += 1;
	}
	return true;
}