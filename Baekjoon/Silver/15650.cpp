#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Backtracking(int num, int depth);

int N, M;
vector<int> checkList;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    Backtracking(1, 0);
}

void Backtracking(int num, int depth) {
    if (depth == M) {
        for (int element : checkList) cout << element << ' ';
        cout << "\n";
        return;
    }

    for (int i = num; i <= N; i++) {
        if (find(checkList.begin(), checkList.end(), i) != checkList.end()) continue;
        checkList.push_back(i);
        Backtracking(i + 1, depth + 1);
        checkList.erase(remove(checkList.begin(), checkList.end(), i), checkList.end());
    }
}