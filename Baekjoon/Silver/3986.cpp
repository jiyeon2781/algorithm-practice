#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, count = 0;
    string str;

    cin >> n; 
    for (int i = 0; i < n; i++) {
        stack<char> st;
        cin >> str;
        for (char ch : str) {
            if (st.empty()) {
                st.push(ch);
            }
            else {
                char curCh = st.top();
                if (ch == curCh) st.pop();
                else st.push(ch);
            }
        }
        if (st.empty()) count += 1;
    }
    cout << count;

    return 0;
}
