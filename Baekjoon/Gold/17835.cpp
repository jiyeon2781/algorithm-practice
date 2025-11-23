#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void Start();
void Dijkstra();

const long long INF = 10000000000;
const long long Max = 100001;

long long N, M, K;

vector<pair<long long, long long>> map[Max];
long long dist[Max];
vector<long long> interviews;
bool isInterview[Max];
pair<long long, long long> result = { -1, -1 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    long long u, v, c;

    for (long long i = 0; i < M; i++) {
        cin >> u >> v >> c;
        map[v].push_back({ u, c });
    }

    long long k;

    for (long long i = 0; i < K; i++) {
        cin >> k;
        interviews.push_back(k);
        isInterview[k] = true;
    }

    Start();

    cout << result.first << "\n" << result.second << "\n";

    return 0;
}

void Start() {
    Dijkstra();

    for (long long i = 1; i <= N; i++) {
        if (result.first == -1 || result.second < dist[i])
            result = { i, dist[i] };
    }
}

void Dijkstra() {
    fill(dist, dist + N + 1, INF);
    
    priority_queue < pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> que;
    for (long long cur : interviews) {
        que.push({ 0, cur });
        dist[cur] = 0;
    }

    while (!que.empty()) {
        long long cost = que.top().first;
        long long node = que.top().second;

        que.pop();

        if (dist[node] < cost) continue;

        for (int i = 0; i < map[node].size(); i++) {
            long long nodeCost = map[node][i].second;
            long long nextNode = map[node][i].first;

            if (dist[nextNode] > cost + nodeCost) {
                dist[nextNode] = cost + nodeCost;
                que.push({ dist[nextNode], nextNode });
            }
        }
    }
}
