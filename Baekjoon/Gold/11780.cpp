#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 101;
const int INF = 10000001;

int graph[MaxSize][MaxSize];
int pathTable[MaxSize][MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    int a, b, cost;

    fill(graph[0], graph[0] + MaxSize * MaxSize, INF);
    for (int i = 1; i <= N; i++) graph[i][i] = 0;

    for (int i = 0; i < M; i++) {
        cin >> a >> b >> cost;
        graph[a][b] = min(graph[a][b], cost);
        pathTable[a][b] = b;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                if (graph[j][k] <= graph[j][i] + graph[i][k]) continue;
                graph[j][k] = graph[j][i] + graph[i][k];
                pathTable[j][k] = pathTable[j][i];
            }
        }
    }

    // a -> b 최소 비용
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (graph[i][j] == INF) cout << "0 ";
            else cout << graph[i][j] << ' ';
        }
        cout << "\n";
    }

    vector<int> path;
    // a -> b 도시의 경로
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j || graph[i][j] == INF) {
                cout << "0\n";
                continue;
            }

            path.clear();
            int cur = i;
            while (true) {
                if (cur == j) break;
                path.push_back(cur);
                cur = pathTable[cur][j];
            }
            path.push_back(j);

            cout << path.size() << ' ';
            for (auto element : path) cout << element << ' ';
            cout << "\n";
        }
    }
}