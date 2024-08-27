#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void Backtracking(int idx, int depth, int L);

vector<char> chars;
vector<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
string result;
int vowelCnt, consonantCnt;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char ch;
    int L, C;
    cin >> L >> C;

    for (int i = 0; i < C; i++) {
        cin >> ch;
        chars.push_back(ch);
    }

    sort(chars.begin(), chars.end());

    vowelCnt = 0;
    consonantCnt = 0;
    result = "";

    Backtracking(0, 0, L);
}

void Backtracking(int idx, int depth, int L) {
    if (depth == L) {
        if (vowelCnt >= 1 && consonantCnt >= 2) cout << result << "\n";
        return;
    }

    for (int i = idx; i < chars.size(); i++) {
        bool isConsonant = (find(vowels.begin(), vowels.end(), chars[i]) == vowels.end());
        result += chars[i];
        if (isConsonant) consonantCnt += 1;
        else vowelCnt += 1;

        Backtracking(i + 1, depth + 1, L);

        result.pop_back();
        if (isConsonant) consonantCnt -= 1;
        else vowelCnt -= 1;
    }
}