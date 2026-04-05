#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Info {
	int height;
	int width;
	int column;
	int row;
};

void Start();
bool IsValid(int height, int width, int column, int row);
void AddBox(int idx, int height, int width, int column);
void DrawMap(int idx, int height, int width, int column, int row);
bool Falling();
void MoveBox(int idx, int afterRow);
void DropBoxInLeft();
void DropBoxInRight();
void EraseBox(int idx);

const int MaxSize = 51;
const int MaxCount = 101;

int map[MaxSize][MaxSize];
vector<Info> boxes(MaxCount);
bool isBoxEnd[MaxCount];
int boxHeightCount[MaxCount];
int boxWidthCount[MaxCount];

int N, M;
vector<int> result;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	int k, h, w, c;
	for (int i = 0; i < M; i++) {
		cin >> k >> h >> w >> c;
		boxes[k] = { h, w, c, 0 };
		AddBox(k, h, w, c);
	}

	Start();

	for (auto num : result) cout << num << "\n";
	return 0;
}

void AddBox(int idx, int height, int width, int column) {
	int prevRow = -1;
	for (int i = 1; i <= N; i++) {
		if (IsValid(height, width, column, i)) prevRow = i;
		else {
			DrawMap(idx, height, width, column, prevRow);
			boxes[idx].row = prevRow;
			return;
		}
	}
	DrawMap(idx, height, width, column, prevRow);
	boxes[idx].row = prevRow;
}

bool IsValid(int height, int width, int column, int row) {
	for (int i = row; i < row + height; i++)
		for (int j = column; j < column + width; j++) {
			if (i > N) return false;
			if (map[i][j] > 0) return false;
		}
	return true;
}

void DrawMap(int idx, int height, int width, int column, int row) {
	for (int i = row; i < row + height; i++)
		for (int j = column; j < width + column; j++)
			map[i][j] = idx;
}

void Start() {
	while (result.size() < M) {
		DropBoxInLeft();
		DropBoxInRight();
	}
}

bool Falling() {
	bool isFalled = false;

	for (int idx = 1; idx < MaxCount; idx++) {
		if (isBoxEnd[idx] || boxes[idx].height == 0) continue;

		int col = boxes[idx].column;
		int h = boxes[idx].height;
		int w = boxes[idx].width;
		int topRow = boxes[idx].row;
		int botRow = topRow + h - 1;

		// 박스 바로 아래 각 열의 빈 칸 수 계산 → 최솟값만큼 내려갈 수 있음
		int minGap = N;
		for (int j = col; j < col + w; j++) {
			int gap = 0;
			for (int i = botRow + 1; i <= N; i++) {
				if (map[i][j] == 0) gap++;
				else break;
			}
			minGap = min(minGap, gap);
		}

		if (minGap > 0) {
			MoveBox(idx, topRow + minGap);
			isFalled = true;
		}
	}

	return isFalled;
}

void MoveBox(int idx, int newTopRow) {
	int col = boxes[idx].column;
	int h = boxes[idx].height;
	int w = boxes[idx].width;
	int oldRow = boxes[idx].row;

	for (int i = oldRow; i < oldRow + h; i++)
		for (int j = col; j < col + w; j++)
			map[i][j] = 0;

	for (int i = newTopRow; i < newTopRow + h; i++)
		for (int j = col; j < col + w; j++)
			map[i][j] = idx;

	boxes[idx].row = newTopRow;
}

void DropBoxInLeft() {
	fill(boxHeightCount, boxHeightCount + MaxCount, 0);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] != 0) {
				boxHeightCount[map[i][j]]++;
				break;
			}
		}
	}

	for (int i = 1; i <= MaxCount; i++) {
		if (isBoxEnd[i] || boxes[i].height == 0) continue;
		if (boxHeightCount[i] != boxes[i].height) continue;
		EraseBox(i);
		while (Falling());
		result.push_back(i);
		isBoxEnd[i] = true;
		break;
	}
}

void DropBoxInRight() {
	fill(boxHeightCount, boxHeightCount + MaxCount, 0);

	for (int i = 1; i <= N; i++) {
		for (int j = N; j >= 1; j--) {
			if (map[i][j] != 0) {
				boxHeightCount[map[i][j]]++;
				break;
			}
		}
	}

	for (int i = 1; i <= MaxCount; i++) {
		if (isBoxEnd[i] || boxes[i].height == 0) continue;
		if (boxHeightCount[i] != boxes[i].height) continue;
		EraseBox(i);
		while (Falling());
		result.push_back(i);
		isBoxEnd[i] = true;
		break;
	}
}

void EraseBox(int idx) {
	for (int i = 1; i <= N; i++)
		for (int j = boxes[idx].column; j < boxes[idx].column + boxes[idx].width; j++)
			if (map[i][j] == idx) map[i][j] = 0;
}