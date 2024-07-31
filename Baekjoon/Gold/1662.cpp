#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;
    
    stack<pair<int, int>> numbers; // { count, 끝자리 숫자 }
    pair<int, int> top;

    int strLength = 0;
    char preChar;

    for (char ch : str) {
        if (ch == '(') {
            numbers.push({ strLength, preChar });
            strLength = 0;
        }
        else if (ch == ')') {
            top = numbers.top();
            numbers.pop();
            strLength = (top.second * strLength) + (top.first - 1); // 문자열 길이 계산
        }
        else {
            strLength += 1;
            preChar = ch - '0';
        }
    }

    cout << strLength;
}  