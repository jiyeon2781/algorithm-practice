#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> queue(works.begin(), works.end());
    for (int num = n; num > 0 ; num--) {
        if (!queue.empty()) {
            int maxNumber = queue.top();
            queue.pop();
            queue.push(maxNumber - 1);
            }
    }
    
    while (!queue.empty()) {
        int currentNumber =  queue.top();
        if (currentNumber <= 0) break;
        queue.pop();
        answer += (currentNumber * currentNumber);
    }
    return answer;
}