#include <string>
#include <vector>

#define MAX_DUNGEONGS_COUNT 8

using namespace std;

vector<bool> visited(MAX_DUNGEONGS_COUNT);
int answer = 0;

void DFS(int depth, int k, vector<vector<int>> dungeons) {
    for (int index = 0; index < dungeons.size(); index++) {
        if (visited[index]) continue;
        
        if (dungeons[index][0] <= k) {
            visited[index] = true;
            DFS(depth + 1, k - dungeons[index][1], dungeons);
            visited[index] = false;
        }
    }
    
    if (answer <= depth) answer = depth;
    
}

int solution(int k, vector<vector<int>> dungeons) {
    DFS(0, k, dungeons);
    return answer;
}