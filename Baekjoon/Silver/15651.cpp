#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Backtracking(int index, int depth);

int N, M;
vector<int> result;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    Backtracking(1, 0);
    
}  

void Backtracking(int index, int depth) {
    if (depth == M) {
        for (auto element : result) cout << element << ' ';
        cout << "\n";
        return;
    }

    for (int i = 1; i <= N; i++) {
        result.push_back(i);
        int idx = result.size() - 1;
        Backtracking(i, depth + 1);
        result.erase(result.begin() + idx);
    }
}