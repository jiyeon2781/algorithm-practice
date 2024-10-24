#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 101;
const int INF = 10000001;
int graph[MaxSize][MaxSize];

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
        // 노선이 여러 개일 수 있으므로 가장 작은 거리의 노선으로 갱신
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (graph[i][j] == INF) cout << "0 ";
            else cout << graph[i][j] << ' ';
        }
        cout << "\n";
    }
}