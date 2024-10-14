#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 10000001;

void CreateKMPTable(string pattern);
int KMP(string str, string pattern);

int kmpTable[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str, pattern;
    cin >> str >> pattern;

    CreateKMPTable(pattern);
    cout << KMP(str, pattern);
}

void CreateKMPTable(string pattern) { // KMP Table 생성
    fill(kmpTable, kmpTable + pattern.size(), 0);

    int j = 0;
    for (int i = 1; i < pattern.size(); i++) {
        while (j > 0 && pattern[i] != pattern[j]) j = kmpTable[j - 1];
        if (pattern[i] == pattern[j]) kmpTable[i] = ++j;
    }
}

int KMP(string str, string pattern) { // KMP Algorithm
    int pIdx = 0;

    for (int sIdx = 0; sIdx < str.size(); sIdx++) {
        while (pIdx > 0 && str[sIdx] != pattern[pIdx]) pIdx = kmpTable[pIdx - 1];
        if (str[sIdx] == pattern[pIdx]) pIdx += 1;
        if (pIdx == pattern.size()) return 1;
    }
    return 0;
}

// 참고 문헌
// 1. https://blog.encrypted.gg/1040
// 2. https://chanhuiseok.github.io/posts/algo-14/