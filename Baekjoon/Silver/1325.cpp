#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_NUM 10001

using namespace std;

void BFS(int start);

vector<bool> visitedComputer(MAX_NUM);
vector<int> graph[MAX_NUM];

int countComputer[MAX_NUM];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, A, B;
	cin >> N >> M;

	while (M--) {
		cin >> A >> B;
		graph[A].push_back(B);
	}

	fill(countComputer, countComputer + MAX_NUM, 0);

	for (int i = 1; i <= N; i++) {
		BFS(i);
	}

	int idx = 1;
	int maxNum = *max_element(countComputer, countComputer + N + 1);
	while (true) {
		int curNum = *max_element(countComputer + idx, countComputer + N + 1);
		if (curNum < maxNum) break;

		idx = max_element(countComputer + idx, countComputer + N + 1) - countComputer;
		cout << idx << ' ';
		idx += 1;
	}

	return 0;
}

void BFS(int start) {
	queue<int> que;
	que.push(start);
	fill(visitedComputer.begin(), visitedComputer.end(), false);
	visitedComputer[start] = true;

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		countComputer[cur] += 1;

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];

			if (visitedComputer[next]) continue;
			visitedComputer[next] = true;

			que.push(next);
		}
	}
}
