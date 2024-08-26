#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int times[3];
    string time, name;
    int result = 0;
    int hour, minute;

    for (int i = 0; i < 3; i++) {
        cin >> time;
        hour = stoi(time.substr(0, 2));
        minute = stoi(time.substr(3, 2));
        times[i] = 60 * hour + minute;
    }

    map<string, int> names;

    while (cin >> time >> name) { 
        hour = stoi(time.substr(0, 2));
        minute = stoi(time.substr(3, 2));
        int curTime = 60 * hour + minute;

        if (curTime <= times[0])
            names[name] = 1;
        else if (curTime >= times[1] && curTime <= times[2]) {
            if (names.find(name) != names.end())
                names[name] += 1;
        }
    }

    for (auto element : names) {
        if (element.second >= 2) result += 1;
    }

    cout << result;
}