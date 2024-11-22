#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string solution(string input_string) {
    string answer = "";
    map<char, int> alpha;

    char prev = '-';
    for (char ch : input_string) {
        if (prev == '-') {
            prev = ch;
            if (alpha.find(ch) == alpha.end()) alpha.insert({ch, 1});
        }
        else if (ch != prev) {
            prev = ch;
            if (alpha.find(ch) == alpha.end()) alpha.insert({ch, 1});
            else alpha[ch] += 1;
        }
    }

    for (auto cnt : alpha) {
        if (cnt.second >= 2) answer += cnt.first;
    }
    return answer == "" ? "N" : answer;
}