#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> scovilleQueue(scoville.begin(), scoville.end());
    while (true) {
        if (scovilleQueue.top() >= K) break;
        else if (scovilleQueue.size() < 2) return -1;
        int currentScoville = scovilleQueue.top();
        scovilleQueue.pop();
        int nextScoville = scovilleQueue.top();
        scovilleQueue.pop();
        scovilleQueue.push(currentScoville + (nextScoville * 2));
        answer += 1;
    }
    return answer;
}