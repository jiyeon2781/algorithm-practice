#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    
    sort(citations.rbegin(), citations.rend());
    for (int idx = 0; idx < citations.size(); idx++) {
        if (citations[idx] >= idx + 1) answer += 1;
            
    }
    return answer;
}