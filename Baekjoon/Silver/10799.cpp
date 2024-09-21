#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack<char> st;
    string str;
    cin >> str;

    int result = 0;
    int prev = '-';
    for (auto ch : str) {
        if (ch == '(') st.push(ch); // current char : (
        else { // current char : )
            if (prev == '(') result += (st.size() - 1);
            else 
                result += 1;
            st.pop();
        }
        prev = ch;
    }
    cout << result;
}