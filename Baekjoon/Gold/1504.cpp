#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_VERTEX_CNT 801
#define INF 200000000

using namespace std;

struct Node {
    int node;
    int cost;
};

struct compare {
    bool operator() (Node a, Node b) {
        if (a.cost == b.cost) return a.node > b.node;
        return a.cost > b.cost;
    }
};

int Dijkstra(int start, int end, int N); 

vector<Node> graph[MAX_VERTEX_CNT];
int dist[MAX_VERTEX_CNT] = { 0, };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, E;
    cin >> N >> E;

    int a, b, c, u, v;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({ b, c });
        graph[b].push_back({ a, c });
    }

    cin >> u >> v;
    
    int result = 0;

    int uv = Dijkstra(1, u, N) + Dijkstra(u, v, N) + Dijkstra(v, N, N); // 1 -> u -> v -> N
    int vu = Dijkstra(1, v, N) + Dijkstra(v, u, N) + Dijkstra(u, N, N); // 1 -> v -> u -> N

    uv > vu ? result = vu : result = uv; // shortest distance
    if (result >= INF) result = -1; // not found
    cout << result;
}

int Dijkstra(int start, int end, int N) {
    priority_queue<Node, vector<Node>, compare> que;

    fill(dist, dist + N + 1, INF);
    dist[start] = 0;

    que.push({ start, dist[start] });

    while (!que.empty()) {
        int curNode = que.top().node;
        int curCost = que.top().cost;
        que.pop();

        for (int i = 0; i < graph[curNode].size(); i++) {
            int nextNode = graph[curNode][i].node;
            int nextCost = curCost + graph[curNode][i].cost;

            if (dist[nextNode] > nextCost) {
                dist[nextNode] = nextCost;
                que.push({ nextNode, nextCost });
            }
        }
    }

    return dist[end];
}