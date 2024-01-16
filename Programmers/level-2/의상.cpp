#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map<string, int> clothesCount;
    
    for (vector<string> cloth : clothes) {
        if (clothesCount.find(cloth[1]) == clothesCount.end()){
            clothesCount.insert({cloth[1], 1});
            continue;
        } 
        clothesCount[cloth[1]]+=1;
    }
    
    for (pair<string ,int> element : clothesCount) {
        answer *= (element.second + 1);
        // 종류가 3개일 때, (a + b + c) + (ab + bc + ac) + abc 라는 식 성립
        // 이를 통해 n차식 계수들의 합임을 알 수 있음(여기서 n은 옷 종류의 개수)
        // 위의 식을 토대로 (x + a)(x + b)(x + c) = x^3 + (a + b + c)x^2 + (ab + bc + ac)x + abc라는 식 성립
        // 해당식의 계수 합을 구하기 위해 x = 1을 대입해주고 마지막으로 1을 빼주면 해당 문제의 정답 성립
    }
    return answer - 1;
}