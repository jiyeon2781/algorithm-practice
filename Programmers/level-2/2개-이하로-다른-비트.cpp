#include <string>
#include <vector>

using namespace std;

const int MaxSize = 18;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for (auto num : numbers) {
        if (num % 2 == 0) { // 짝수
            answer.push_back(num+1);
            continue;
        }
        // 홀수
        long long bit = 2; // 0010
        while(true) {
            if (!(num & bit)) break;
            bit *= 2; // 현재 자리 변경
        }
        answer.push_back(num + bit/2);
        
}
    return answer;
}