#include <iostream>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    string result = "yes";

    while (true) {
        getline(cin, str);
        if (str == ".") break;
        result = "yes";

        stack<char> st;
        for (char ch : str) {
            if (ch == ')' || ch == ']') {
                if (st.empty()) {
                    result = "no";
                    break;
                }

                if ((st.top() == '(' && ch == ')') || (st.top() == '[' && ch == ']')) {
                    st.pop();
                    continue;
                }
                result = "no";
                break;
            }
            if (ch == '(' || ch == '[') {
                st.push(ch);
            }
        }

        if (!st.empty()) result = "no";
        cout << result << "\n";
    }
    return 0;
}
