#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, num;
    cin >> N >> M;
    // N : 입력받을 걸그룹의 수
    // M : 맞혀야할 문제의 수 

    string group, name;
    map<string, set<string>> informations; // 걸그룹에 해당하는 멤버들 저장
    map<string, string> groupInfo; // key : 멤버, value : 그룹 -> 검색을 빠르게 하기 위함

    while (N--) {
        cin >> group >> num;
        while (num--) {
            cin >> name;

            if (informations.find(group) == informations.end()) {
                set<string> setName;
                setName.insert(name);
                informations.insert({ group, setName });
            }
            else informations[group].insert(name);

            groupInfo[name] = group;
        }
    }

    while (M--) {
        cin >> name >> num;
        if (num == 1) {
            cout << groupInfo[name] << "\n";
            continue;
        }
        set<string>& element = informations[name];
        for (string str : element) {
            cout << str << "\n";
        }
    }

    return 0;
}