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

    int t, n, result = 1;
    string name, kind;
    map<string, int> clothes;

    cin >> t;
    while (t--)
    {
        cin >> n;
        clothes.clear();
        result = 1;

        while (n--)
        {
            cin >> name >> kind;

            if (clothes.find(kind) == clothes.end())
                clothes[kind] = 1;
            else
                clothes[kind] += 1;
        }
        
        // 입을 수 있는 경우의 수 계산
        for (auto iter = clothes.begin(); iter != clothes.end(); iter++)
            result *= (iter->second + 1); // 안 입는 경우의 수 : + 1

        cout << result - 1 << "\n"; // 아무것도 안 입은 경우 제거
    }
} 