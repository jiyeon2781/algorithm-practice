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
    
    stack<pair<int, int>> numbers;  // { count, 끝자리 숫자 }
    pair<int, int> num, top;

    num = { 0, 0 };

    for (char ch : str) {
        if (ch == '(') {
            numbers.push(num);
            num.second = 0;
            num.first = 0;
        }
        else if (ch == ')') {
            top = numbers.top();
            numbers.pop();
            num.first = (top.second * num.first) + (top.first - 1); // 문자열 길이 계산
        }
        else {
            num.first += 1;
            num.second = ch - '0';
        }
    }

    cout << num.first;
}  