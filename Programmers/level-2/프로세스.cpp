#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int priority,index;
};

int solution(vector<int> priorities, int location) {
    queue<Process> que;
    int index = 0;
    for (int priority : priorities) {
        que.push({priority, index++});
    }
    
    sort(priorities.rbegin(), priorities.rend());
    index = 0; 
    while (index < priorities.size()) {
        Process currentQueue = que.front();
        que.pop();
        if (currentQueue.priority == priorities[index]) {
            index += 1;
            if (currentQueue.index == location) {
                return index;
                break;
            }
        }
        else 
            que.push(currentQueue);
    }
    
    return index;
}