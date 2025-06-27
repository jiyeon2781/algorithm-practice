#include <iostream>
#include <stack>

using namespace std;

void DrawDragonCurve(int x, int y, int dir, int gen);
int CountRectangle();

const int Max = 101;

bool map[Max][Max];

int dirX[4] = { 1, 0, -1, 0 };
int dirY[4] = { 0, -1, 0, 1 };
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N;

	cin >> N;

	for (int tc = 0; tc < N; tc++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		// x, y 좌표
		// d : 시작 방향
		// g : 세대

		// 드래곤 커브 작성
		map[y][x] = true;
		DrawDragonCurve(x, y, d, g);
	}

	// 정사각형 개수 Count
	cout << CountRectangle();
}

void DrawDragonCurve(int x, int y, int dir, int gen) {
	stack<int> st, prevSt;
	st.push(dir);
	prevSt = st;
	map[y + dirY[dir]][x + dirX[dir]] = true;
	pair<int, int> corp = { y + dirY[dir], x + dirX[dir] };

	for (int i = 1; i <= gen; i++) {
		while (!st.empty()) {
			int cur = (st.top() + 1) % 4;
			st.pop();
			pair<int, int> next = { corp.first + dirY[cur] ,corp.second + dirX[cur] };
			map[next.first][next.second] = true;
			prevSt.push(cur);
			corp = next;
		}
		st = prevSt;
	}
}

int CountRectangle() {
	int cnt = 0;
	for (int i = 0; i < Max - 1; i++) {
		for (int j = 0; j < Max - 1; j++) {
			if (!map[i][j]) continue;
			if (!map[i + 1][j]) continue;
			if (!map[i][j + 1]) continue;
			if (!map[i + 1][j + 1]) continue;
			cnt += 1;
		}
	}
	return cnt;
}
