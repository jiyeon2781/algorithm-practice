#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    int idx = 0, prevNum;
    stack<int> st;
    
    for (int i = 0; i < prices.size(); i++) {
        while (true){
            if (st.empty() || prices[st.top()] <= prices[i]) break;
            // 주식이 하락세일 때 떨어지지 않은 시간 계산
            prevNum = st.top();
            answer[prevNum] = i - prevNum;
            st.pop();
        }
        st.push(i); // 해당 주식의 index를 기준으로 저장
    }
    
    while (!st.empty()) { // 계산되지 않은 나머지 시간 계산(상승세)
        answer[st.top()] = prices.size() - st.top() - 1;
        st.pop();
    }
    return answer;
}