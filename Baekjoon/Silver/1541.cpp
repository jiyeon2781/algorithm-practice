#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int SplitAndCalculate(string str);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    cout << SplitAndCalculate(str);
}

int SplitAndCalculate(string str) {
    vector<int> nums;
    vector<char> ch;

    string num = "";
    int result = 0;

    // split

    if (str[0] == '-') {
        for (int i = 1; i < str.size(); i++) {
            if (str[i] >= '0' && str[i] <= '9') num += str[i];
            else {
                nums.push_back(stoi('-' + num));
                str = str.substr(i, str.size() - i);
                num = "";
                break;
            }
        }
    }

    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9') num += str[i];
        else {
            if (num != "") nums.push_back(stoi(num));
            ch.push_back(str[i]);
            num = "";
        }
    }

    if (num != "") nums.push_back(stoi(num));

    // calculate

    int cur = nums[nums.size() - 1];
    for (int i = ch.size() - 1; i >= 0; i--) {
        if (ch[i] == '+') cur += nums[i];
        else {
            result -= cur;
            cur = nums[i];
        }
    }
    
    return result + cur;
}