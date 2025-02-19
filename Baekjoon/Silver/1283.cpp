#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> Split(string str, char delimiter);
string SetingParentheses(string input, bool onlyFirst);

const int MaxSizeAlphabet = 26;

bool isSettingQuickKey[MaxSizeAlphabet];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    string option;
    vector<string> splitOption;
    bool setQuickKey = false;
    N += 1;

    while (N--) {
        getline(cin, option);
        if (option == "") continue;

        splitOption = Split(option, ' ');
        setQuickKey = false;

        for (int i = 0; i < splitOption.size(); i++) { // 첫글자만 검사
            string output = SetingParentheses(splitOption[i], true);
            if (splitOption[i] != output) {
                setQuickKey = true;
                splitOption[i] = output;
                break;
            }
        }

        bool endQuickKey = false;
        if (!setQuickKey) {
            for (int i = 0; i < splitOption.size(); i++) { // 뒷글자도 같이 검사
                string output = SetingParentheses(splitOption[i], false);
                if (splitOption[i] != output) {
                    endQuickKey = true;
                    splitOption[i] = output;
                    break;
                }
                if (endQuickKey) break;
            }
        }

        option = "";
        for (auto st : splitOption) {
            option += st;
            option += " ";
        }

        cout << option << "\n";
    }
}

string SetingParentheses(string input, bool onlyFirst) {
    for (int i = 0; i < input.size(); i++) {
        char ch = input[i];
        if (onlyFirst && i != 0) break;

        if (ch >= 'a' && ch <= 'z') {
            if (isSettingQuickKey[ch - 'a']) continue;
            isSettingQuickKey[ch - 'a'] = true;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            if (isSettingQuickKey[ch - 'A']) continue;
            isSettingQuickKey[ch - 'A'] = true;
        }
        input = input.insert(i, "[");
        input = input.insert(i + 2, "]");
        break;
    }
    return input;
}

vector<string> Split(string str, char delimiter)
{
    vector<string> result;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter)) result.push_back(temp);
    return result;
}