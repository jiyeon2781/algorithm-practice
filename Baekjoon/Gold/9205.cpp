#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

void Init();
bool BFS();

const int Size = 101;
const int divNum = 50;

int N;

pair<int, int> festival;
pair<int, int> point[Size];
bool visited[Size];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;

    while (tc--) {
        cin >> N; // 편의점 개수

        cin >> point[0].first >> point[0].second; // 집
        for (int i = 1; i <= N; i++)  // 편의점
            cin >> point[i].first >> point[i].second;
        cin >> festival.first >> festival.second; // 페스티벌

        Init();
        auto result = BFS();
        if (result)
            cout << "happy\n";
        else
            cout << "sad\n";
    }
    return 0;
}

void Init() {
    fill(visited, visited + Size, false);
}

bool BFS() {
    queue<int> que;
    que.push(0);
    visited[0] = true;
    
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        
        int distance = abs(point[cur].first - festival.first) + abs(point[cur].second - festival.second);
        if (distance <= 1000) // 맥주 20개 * 50미터
            return true;

        for (int i = 0; i <= N; i++) {
            if (visited[i] || cur == i)
                continue;
            distance = abs(point[cur].first - point[i].first) + abs(point[cur].second - point[i].second);
            if (distance <= 1000)
            {
                visited[i] = true;
                que.push(i);
            }
        }
    }

    return false;
}