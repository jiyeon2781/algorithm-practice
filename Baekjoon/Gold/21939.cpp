#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, P, L;
    cin >> N;
    set<pair<int, int>> problems; // 추천 문제 리스트
    map<int, int> difficulty; // 빠른 검색을 위한 문제 난이도 저장하는 컨테이너

    while (N--) {
        cin >> P >> L;
        problems.insert({ L, P });
        difficulty[P] = L;
    }

    cin >> M;
    string inputStr;
    while (M--) {
        cin >> inputStr;
        if (inputStr == "add") { // 추가
            cin >> P >> L;
            problems.insert({ L, P });
            difficulty[P] = L;
        }
        else if (inputStr == "recommend") { 
            cin >> L;
            if (L == 1) { // 어려운 문제 추천
                auto iter = problems.end();
                iter = --iter;
                cout << iter->second << "\n";
            }
            else { // 쉬운 문제 추천
                auto iter = problems.begin();
                cout << iter->second << "\n";
            }
        }
        else if (inputStr == "solved") {
            cin >> P;
            problems.erase({ difficulty[P], P }); // 삭제
        }
    }

    return 0;
}