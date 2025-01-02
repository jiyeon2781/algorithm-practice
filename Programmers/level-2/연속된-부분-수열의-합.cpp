#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    int start, end = 0, sum = sequence[start];
    
    for (start = 0; start < sequence.size(); start++) {
        while(sum < k && end < sequence.size() - 1) sum += sequence[++end];
        if (sum == k) {
            if (answer.size() == 0) {
                answer.push_back(start);
                answer.push_back(end);
            }
            else if (answer[1] - answer[0] > end - start) {
                answer[1] = end;
                answer[0] = start;
            }
        }
        sum -= sequence[start];
    }
    
    return answer;
}