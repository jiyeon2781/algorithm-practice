#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Backtracking(int index, int depth, int N, int M, vector<int> check);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;

    cin >> N >> M;
    vector<int> check;

    Backtracking(1, 0, N, M, check);
}  

void Backtracking(int index, int depth, int N, int M, vector<int> check)
{
    if (depth == M) {
        for (auto element : check) cout << element << ' ';
        cout << "\n";
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (find(check.begin(), check.end(), i) != check.end()) continue;
        check.push_back(i);
        Backtracking(index + 1, depth + 1, N, M, check);
        check.erase(remove(check.begin(), check.end(), i), check.end());
    }
}