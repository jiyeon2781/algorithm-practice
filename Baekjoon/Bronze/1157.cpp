#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define COUNT_ALPHABET 26

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<pair<int,int>> alphabets(COUNT_ALPHABET, {0, 0});
    string str;
    cin >> str;

    for (char ch : str) {
        ch = toupper(ch);
        alphabets[ch - 'A'].first += 1;
        if (alphabets[ch - 'A'].second == 0) alphabets[ch - 'A'].second = ch - 'A';
    }
    
    sort(alphabets.begin(), alphabets.end(), compare);
    if (alphabets[0].first == alphabets[1].first) cout << "?";
    else cout << (char) (alphabets[0].second + 'A');

}
