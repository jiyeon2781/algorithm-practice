#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, M, index, previosIndex;
    cin >> N >> M;
    string word, keyword;
    unordered_set<string> words;
    
    for (int i = 0; i < N; i++) {
        cin >> word;
        words.insert(word);
    }

    for (int i = 0; i < M; i++) {
        cin >> keyword;
        keyword += ',';
        previosIndex = 0;
        index = keyword.find(',');
        while (index != string::npos) {
            string subStr = keyword.substr(previosIndex, index - previosIndex);
            if (words.find(subStr) != words.end()) words.erase(subStr);
            previosIndex = index + 1;
            index = keyword.find(',', previosIndex);
        }

        cout << words.size() << "\n";
    }

    return 0;
}