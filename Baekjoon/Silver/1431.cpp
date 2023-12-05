#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

bool compare(string a, string b) {
    if (a.length() != b.length()) return a.length() < b.length();
    // A와 B의 길이가 다르면 짧은것이 먼저 옴
    int currentSumA = 0, currentSumB = 0;
    for (int i = 0; i < a.length(); i++) {
        if (isdigit(a[i])) currentSumA += (a[i] - '0');
        if (isdigit(b[i])) currentSumB += (b[i] - '0');
    }
    if (currentSumA != currentSumB) return currentSumA < currentSumB;
    // 길이가 같으면 A의 모든 자리수 합과 B의 모든 자리수 합을 비교해서 작은합을 가지는 것이 먼저옴(숫자만 더함)
    return a < b;
    // 둘 조건으로도 비교할 수 없을 때(합이 같거나 알파벳만 존재할때) 사전순으로 비교(숫자가 알파벳보다 사전순으로 작음)
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;
    vector<string> serialNumbers;
    string curNum;
    for (int i = 0; i < N; i++) {
        cin >> curNum;
        serialNumbers.push_back(curNum);
    }

    sort(serialNumbers.begin(), serialNumbers.end(), compare);

    for (int i = 0; i < N; i++) {
        cout << serialNumbers[i] << "\n";
    }

    return 0;
}
