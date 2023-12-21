#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

bool compare(char a, char b) {
    if (islower(a) && isupper(b)) return true;
    if (islower(b) && isupper(a)) return false;
    return a > b;
}

string solution(string s) {
    sort(s.begin(),s.end(), compare);
    return s;
}