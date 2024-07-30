#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, L, H, result = 0;
    pair<int, int > max = { 0, 0 };
    vector<pair<int, int>> col;

    cin >> N;
    
    while (N--)
    {
        cin >> L >> H;
        if (max.second < H) max = { L, H }; // 가장 높은 기둥 저장
        col.push_back({ L, H });
    }
    result += max.second;

    sort(col.begin(), col.end());

    // 가장 높은 기둥을 기준으로 왼쪽, 오른쪽 면적 구한 후 합

    int maxHeight = 0;
    int columnIdx = 0;

    for (int i = col[0].first; i < max.first; i++) { // 왼쪽 -> 오른쪽
        if (i == col[columnIdx].first) {
            if (maxHeight < col[columnIdx].second) maxHeight = col[columnIdx].second;
            columnIdx += 1;
        }
        result += maxHeight;
    }

    maxHeight = 0;
    columnIdx = col.size() - 1;

    for (int i = col[col.size() - 1].first; i > max.first; i--) { // 오른쪽 -> 왼쪽
        if (i == col[columnIdx].first) {
            if (maxHeight < col[columnIdx].second) maxHeight = col[columnIdx].second;
            columnIdx -= 1;
        }
        result += maxHeight;
    }
    cout << result << "\n";
}  