#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 99999999
#define MAX_CITY 1001

using namespace std;

struct Distance {
    int dist;
    vector<int> cities;

    Distance() {
        dist = INF;
    }
};

struct Compare {
    bool operator() (const pair<int, Distance>& a, const pair<int, Distance>& b) {
        if (a.second.dist == b.second.dist) return a.first < b.first;
        return a.second.dist > b.second.dist;
    }
};

vector<pair<int, int>> graphs[MAX_CITY];
Distance dist[MAX_CITY];
bool visited[MAX_CITY];

void Dijkstra(int start, int end);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    int start, end, cost;
    while (M--) {
        cin >> start >> end >> cost;
        graphs[start].push_back({ end, cost });
    }

    cin >> start >> end;

    Dijkstra(start, end);
    cout << dist[end].dist << "\n" << dist[end].cities.size() << "\n";
    for (int city : dist[end].cities) {
        cout << city << " ";
    }

    return 0;
}

void Dijkstra(int start, int end) {
    priority_queue<pair<int, Distance>, vector<pair<int, Distance>>, Compare> que;
    dist[start].dist = 0;
    dist[start].cities.push_back(start);

    que.push({ start, dist[start] });
    while (!que.empty()) {
        int node = que.top().first;
        Distance distInfo = que.top().second;
        que.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (int i = 0; i < graphs[node].size(); i++) {
            int nextNode = graphs[node][i].first;
            int nextDistCost = graphs[node][i].second + distInfo.dist;

            if (nextDistCost < dist[nextNode].dist) {
                dist[nextNode].dist = nextDistCost;
                dist[nextNode].cities = distInfo.cities;
                dist[nextNode].cities.push_back(nextNode);
                que.push({ nextNode, dist[nextNode] });
            }
        }
    }
}