#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int Dir = 4;

int cost[100][100];

int dirX[Dir] = {0, 0, 1, -1};
int dirY[Dir] = {1, -1, 0, 0};

int BFS(vector<vector<int>> maps) {
    
    queue<pair<int, int>> que;
    que.push({0, 0});
    cost[0][0] = 1;
    int n = maps.size(), m = maps[0].size();
    
    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();
        
        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = {cur.first + dirX[i], cur.second + dirY[i]};
            if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= m)
                continue;
            if (cost[next.first][next.second] > 0)
                continue;
            if (maps[next.first][next.second] == 0)
                continue;
            
            que.push(next);
            cost[next.first][next.second] = cost[cur.first][cur.second] + 1;
        }
    }
    
    if (cost[n-1][m-1] == 0)
        return -1;
    else return cost[n-1][m-1];
}

int solution(vector<vector<int>> maps)
{
    return BFS(maps);
}
