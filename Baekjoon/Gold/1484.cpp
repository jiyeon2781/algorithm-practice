#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int G;
    cin >> G;

    int current = 2, prev = 1;
    vector<int> results;

    while (true) {
        if (prev + 1 == current && (current * current) - (prev * prev) > G) break;
        // 몸무게 차이가 1이고, 해당 식이 G보다 클때 종료 : 인접한 제곱수 차가 G보다 크게 되면 더 작은수가 나올 수 없기 때문

        if ((current * current) - (prev * prev) < G) current += 1;
        else if ((current * current) - (prev * prev) > G) prev += 1;
        else if ((current * current) - (prev * prev) == G) results.push_back(current++);
    }

    for (int i = 0; i < results.size(); i++) cout << results[i] << "\n";
    if (results.size() == 0) cout << "-1\n";

    return 0;
}