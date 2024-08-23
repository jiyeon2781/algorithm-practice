#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num;
    cin >> N; 

    stack<int> nums; // 수열

    stack<int> st; // 내림차순 스택
    stack<int> result; // 결과

    while (N--) {
        cin >> num;
        nums.push(num);
    }

    while (!nums.empty()) {
        num = nums.top();
        nums.pop();

        while (!st.empty() && st.top() <= num) // 현재 값보다 작거나 같은 숫자는 pop
            st.pop();

        if (st.empty()) // 현재 값보다 큰 수가 없을 때
            result.push(-1);
        else
            result.push(st.top());

        st.push(num);
    }

    while (!result.empty()) {
        cout << result.top() << ' ';
        result.pop();
    }
}
