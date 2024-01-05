#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 200000000
#define MAX_CITY_NUM 1001

using namespace std;

vector<pair<int, int>> graph[MAX_CITY_NUM];
int dist[MAX_CITY_NUM];
int visited[MAX_CITY_NUM];

int dijkstra(int start, int end);

struct compare {
    bool operator() (const pair<int,int> a, const pair<int, int> b) {
        return a.second > b.second;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, start, end, cost;
    cin >> N >> M; // N : 도시 개수, M : 버스 개수
    for (int i = 0; i < M; i++) {
        cin >> start >> end >> cost;
        graph[start].push_back({ end,cost });
    }
    
    cin >> start >> end;

    fill(dist, dist + N + 1, INF);

    int result = dijkstra(start, end);
    cout << result << "\n";

    return 0;
}

int dijkstra(int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> queue;
    // 현재 도달한 지점, 비용
    dist[start] = 0;
    queue.push({ start, dist[start] });
    while (!queue.empty()) {
        int curNode = queue.top().first;
        int curCost = queue.top().second;
        queue.pop();

        if (visited[curNode]) continue; // 해당 노드를 이미 탐색했는지 확인
        visited[curNode] = true;

        for (int i = 0; i < graph[curNode].size(); i++) {
            int nextNode = graph[curNode][i].first; // 다음 도달할 지점
            int nextCost = graph[curNode][i].second + curCost; // 다음 도달했을 때 갱신되는 비용

            if (nextCost < dist[nextNode]) {
                dist[nextNode] = nextCost;
                queue.push({ nextNode, dist[nextNode] });
            }
        }
    }
    return dist[end];
}