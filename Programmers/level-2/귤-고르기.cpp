#include <map>
#include <algorithm>

using namespace std;

const int MaxSize = 10000001;
map<int, int> cnt;

bool compare (const pair<int,int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    for (int element : tangerine) cnt[element] += 1;
    
    vector<pair<int, int>> vecCnt(cnt.begin(), cnt.end());
    sort(vecCnt.begin(), vecCnt.end(), compare);
    
    
    for (auto element : vecCnt) {
        if (k <= 0) break;
        k -= element.second;
        answer += 1;
    }
    return answer;
}