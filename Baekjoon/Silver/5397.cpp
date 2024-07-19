#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    string pw;
    list<char> result;

    while (t--)
    {
        cin >> pw;
        result.clear();
        list<char>::iterator iter;
        iter = result.begin();

        for (char ch : pw) {
            if (ch == '<') {
                if (iter == result.begin()) continue;
                iter--;
            }
            else if (ch == '>') {
                if (iter == result.end()) continue;
                iter++;
            }
            else if (ch == '-') {
                if (iter == result.begin()) continue;
                auto temp = iter;
                result.erase(--temp);
            }
            else result.insert(iter, ch);
        }

        for (char ch : result) cout << ch;
        cout << "\n";
    }
} 