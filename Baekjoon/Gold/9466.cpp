#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void DFS(int node);

vector<int> students;
vector<bool> visited; // 방문 여부
vector<bool> isCompleted; // cycle 뽑았는지 여부
int result = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;
    while (tc--) {
        int N, student;
        cin >> N;

        visited = vector<bool>(N + 1, false);
        students = vector<int>(N + 1, 0);
        isCompleted = vector<bool>(N + 1, false);

        for (int i = 1; i <= N; i++) {
            cin >> student;
            students[i] = student;
        }

        result = 0;
        for (int i = 1; i <= N; i++) {
            if (isCompleted[i]) continue;
            DFS(i);
        }

        cout << N - result << "\n";
    }
}

void DFS(int node) {
    if (visited[node]) return;
    visited[node] = true;
    int next = students[node];

    if (visited[next]) {
        if (!isCompleted[next]) {
            result += 1;
            while (next != node) {
                result += 1;
                next = students[next];
            }
        }
    }
    else DFS(next);

    isCompleted[node] = true;
}