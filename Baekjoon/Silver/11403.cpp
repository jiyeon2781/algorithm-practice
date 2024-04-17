#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MAX_NUM 101

bool BFS(int start, int end);

vector<bool> visited(MAX_NUM);
vector<int> graph[MAX_NUM];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, num;
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> num;
			if (num == 0) continue;
			graph[i].push_back(j);
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (BFS(i, j)) cout << "1 ";
			else cout << "0 ";
		}
		cout << "\n";
	}
	
	return 0;
}

bool BFS(int start, int end) {
	queue<int> que;
	que.push(start);

	fill(visited.begin(), visited.begin() + MAX_NUM, false);

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		if (cur == end && visited[cur]) return true;

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];
			if (visited[next]) continue;
			visited[next] = true;
			que.push(next);
		}
	}
	return false;
}