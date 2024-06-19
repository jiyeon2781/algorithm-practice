#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int BFS(int start, vector<int> graph[], vector<bool> visited);

int solution(int n, vector<vector<int>> edge) {
    vector<bool> visited(n + 1, false);
    vector<int> graph[n + 1];
    vector<int> dist(n + 1, 0);
    
    for (vector<int> elements : edge)
    {
        graph[elements[0]].push_back(elements[1]);
        graph[elements[1]].push_back(elements[0]);
    }
    
    queue<int> que;
    que.push(1);
    visited[1] = true;
    
    while(!que.empty())
    {
        int curNode = que.front();
        que.pop();
        
        for (int i = 0; i < graph[curNode].size() ;i++){
            int nextNode = graph[curNode][i];
            if (visited[nextNode]) continue;
            visited[nextNode] = true;
            que.push(nextNode);
            dist[nextNode] = dist[curNode] + 1;
        }
    }
    
    int max = *max_element(dist.begin(), dist.end());
    int answer = count(dist.begin(), dist.end(), max);
    return answer;
}