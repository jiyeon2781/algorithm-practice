#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int gridCount = brown + yellow;

    for (int num = 3; num <= gridCount; num++) {
        if (gridCount % num != 0) continue;
        if ((num - 2) * ((gridCount / num) - 2) ==  yellow) {
            answer.push_back(gridCount / num);
            answer.push_back(num);
            break;
        }
    }
    return answer;
}