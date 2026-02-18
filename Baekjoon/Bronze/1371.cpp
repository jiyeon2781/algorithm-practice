#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MaxSize = 26;

int cnt[MaxSize];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    while (getline(cin, str)) {
        for (char ch : str) {
            cnt[ch - 'a'] += 1;
        }
    }

    int max = -1;
    vector<int> result;
    for (int i = 0; i < MaxSize; i++) {
        if (cnt[i] > max)
        {
            result.clear();
            max = cnt[i];
            result.push_back(i);
        }
        else if (cnt[i] == max) {
            result.push_back(i);
        }
    }

    for (int num : result) {
        char ch = num + 'a';
        cout << ch;
    }

    return 0;
}
