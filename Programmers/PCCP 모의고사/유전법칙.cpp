#include <string>
#include <vector>
#include <stack>

using namespace std;

string obj[4] = {"rr", "RR", "Rr" , "Rr"};

vector<string> solution(vector<vector<int>> queries) {
    vector<string> answer;
    for (auto query : queries) {
        stack<vector<int>> st;
        while (query[0] > 1) {
            st.push(query);
            int cur = query[1] / 4;
            int mod = query[1] % 4;
            query[0]-=1;
            if (mod != 0) query[1] = cur + 1;
            else query[1] = cur;
        }

        string prev = "-";
        while (!st.empty()) {
            vector<int> nums = st.top();
            st.pop();
            int mod = nums[1] % 4;
            prev = obj[mod];
            if (mod == 1 || mod == 0) break;
        } 
        if (prev != "-") answer.push_back(prev);
        else answer.push_back("Rr");
    }
    return answer;
}