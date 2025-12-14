#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool BFS(int start);

const int MaxCount = 51;

int N, M;
int peopleCnt, partyCnt;
bool peoples[MaxCount], isTrue = false;
vector<int> partyPeoples[MaxCount];
bool graph[MaxCount][MaxCount];
bool visited[MaxCount];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num;
    fill(peoples, peoples + MaxCount, false);

    cin >> N >> M;

    cin >> peopleCnt;

    for (int i = 0; i < peopleCnt; i++) {
        cin >> num;
        peoples[num - 1] = true;
    }

    int result = 0;

    for (int curP = 0; curP < M; curP++) {
        cin >> partyCnt;
        for (int i = 0; i < partyCnt; i++) {
            int cur;
            cin >> cur;
            partyPeoples[curP].push_back(cur - 1);
        }
    }

    // graph 저장
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < partyPeoples[i].size(); j++) {
            for (int k = j; k < partyPeoples[i].size(); k++) {
                graph[partyPeoples[i][j]][partyPeoples[i][k]] = true;
                graph[partyPeoples[i][k]][partyPeoples[i][j]] = true;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        isTrue = false;

        for (int j = 0; j < partyPeoples[i].size(); j++) {
            // 그래프로 이어져있는지 확인
            if (peoples[partyPeoples[i][j]] || BFS(partyPeoples[i][j])) {
                isTrue = true;
                break;
            }
            if (isTrue)
                break;
        }

        if (!isTrue)
            result += 1;
    }

    cout << result;

    return 0;
}

bool BFS(int start) {
    queue<int> que;
    que.push(start);
    fill(visited, visited + MaxCount, false);
    visited[start] = true;

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (int i = 0; i < N; i++) {
            if (visited[i] || i == cur)
                continue;
            if (graph[cur][i]) {
                if (peoples[i])
                    return true;
                visited[i] = true;
                que.push(i);
            }
        }
    }
    return false;
}