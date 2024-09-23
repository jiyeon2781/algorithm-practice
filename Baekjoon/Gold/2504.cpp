#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack<pair<char, bool>> charSt; // { 기호, 덧셈 여부 }
    stack<int> numSt;

    string str;
    cin >> str;

    char prev = '-', topCh;
    bool isPlus = false;
    int result = 0, num = 0;

    for (auto ch : str) {
        isPlus = false;

        if (ch == '(' || ch == '[') { // ( or [
            if (prev == ')' || prev == ']') charSt.push({ch, true});
            else charSt.push({ ch, false });
            prev = ch;
            continue;
        }

        // ) or ]

        if (!charSt.empty()) { 
            topCh = charSt.top().first;
            isPlus = charSt.top().second;
            charSt.pop();
        }

        else { // character stack이 비었을 때
            cout << 0;
            return 0;
        }

        if (prev == '(' && ch == ')') numSt.push(2);
        else if (prev == '[' && ch == ']') numSt.push(3);
        else {
            if (topCh == '(' && ch == ')') {
                num = numSt.top();
                numSt.pop();
                numSt.push(num * 2);
            }
            else if (topCh == '[' && ch == ']') {
                num = numSt.top();
                numSt.pop();
                numSt.push(num * 3);
            }
            else {
                cout << 0;
                return 0;
            }
        }

        if (isPlus) { // 덧셈
            int num1 = numSt.top();
            numSt.pop();
            int num2 = numSt.top();
            numSt.pop();
            numSt.push(num1 + num2);
        }

        prev = ch;
    }

    if (!charSt.empty()) cout << 0;
    else cout << numSt.top();
}