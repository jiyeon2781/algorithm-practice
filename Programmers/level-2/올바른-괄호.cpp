#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    stack<char> st;
    for (char ch : s) {
        if (ch == ')'){
            if (st.empty())
                return false;
            else st.pop();
        }
        else if (ch == '(') st.push(ch);
    }
    
    return st.empty() ? true : false;
}