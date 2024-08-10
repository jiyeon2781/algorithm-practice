#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define BOJ_LINK "boj.kr/"
#define BOJ_LINK_LENGTH 7

using namespace std;

bool compare(string str1, string str2) {
    bool isBojLink1 = (str1.substr(0, BOJ_LINK_LENGTH) == BOJ_LINK);
    bool isBojLink2 = (str2.substr(0, BOJ_LINK_LENGTH) == BOJ_LINK);

    if (isBojLink1 && isBojLink2) {
        int strNum1 = stoi(str1.substr(BOJ_LINK_LENGTH, str1.size() - BOJ_LINK_LENGTH + 1));
        int strNum2 = stoi(str2.substr(BOJ_LINK_LENGTH, str2.size() - BOJ_LINK_LENGTH + 1));
        return strNum1 <= strNum2;
    }

    if (isBojLink1) return false;
    else if (isBojLink2) return true;

    if (str1.size() == str2.size()) return str1 < str2;
    return str1.size() < str2.size();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    string str;
    vector<string> dailyStudy;

    N += 1;
    while (N--) {
        getline(cin, str);
        if (str == "") continue;
        dailyStudy.push_back(str);
    }

    sort(dailyStudy.begin(), dailyStudy.end(), compare);

    for (auto element : dailyStudy) {
        cout << element << "\n";
    }
}