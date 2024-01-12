#include <iostream>
#include <vector>
#include <queue>

#define MAX_NUM 801
#define INF 8000001
using namespace std;

struct Node {
    int v;
    int cost;
};

struct compare {
    bool operator() (const Node a, const Node b) {
        return a.cost > b.cost;
    }
};

vector<Node> graph[MAX_NUM];

int Dijkstra(int start, int end);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, E, a, b, cost, v1, v2;

    cin >> N >> E;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> cost;
        graph[a].push_back({ b, cost });
        graph[b].push_back({ a, cost });
    }
    cin >> v1 >> v2;

    int result1 = Dijkstra(1, v1) + Dijkstra(v1, v2) + Dijkstra(v2, N);
    int result2 = Dijkstra(1, v2) + Dijkstra(v2, v1) + Dijkstra(v1, N);
    // 1 -> v1 -> v2 -> N
    // 1 -> v2 -> v1 -> N
    // 중 작은 값 출력

    if ((result2 >= INF && result1 >= INF)) cout << "-1\n";
    else  if (result1 < result2) cout << result1 << "\n";
    else cout << result2 << "\n";

    return 0;
}

int Dijkstra(int start, int end) {
    priority_queue<Node, vector<Node>, compare> queue;
    vector<int> dist(MAX_NUM, INF); // INF값을 잘 설정해야함 (오버플로우가 일어나므로)
    vector<bool> visited(MAX_NUM, false);

    dist[start] = 0;
    int result = INF;

    queue.push({ start, 0 });
    while (!queue.empty()) {
        int curNode = queue.top().v;
        int curCost = queue.top().cost;
        queue.pop();

        if (visited[curNode]) continue;
        visited[curNode] = true;

        for (int i = 0; i < graph[curNode].size(); i++) {
            int nextNode = graph[curNode][i].v;
            int nextNodeCost = graph[curNode][i].cost;
            
            if (nextNodeCost + curCost < dist[nextNode]) {
                dist[nextNode] = nextNodeCost + curCost;
                queue.push({ nextNode, nextNodeCost + curCost });
            }
        }
    }
    return dist[end];
}