#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int BinarySearch(int start, int end, int value);

vector<pair<int, int>> holes;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> num;
        if (!holes.size() == 0 && holes[holes.size() - 1].first >= num + i) continue;
        // 이미 큰 구멍이 앞에 존재하면 저장하지 않음
        holes.push_back({ num + i, i + 1 });
    }

    int Q;
    cin >> Q;
    while (Q--) {
        cin >> num;
        int result = BinarySearch(0, holes.size() - 1, num);
        cout << result << ' ';
    }
}

int BinarySearch(int start, int end, int value) {
    while (start <= end) {
        int mid = (start + end) / 2;

        if (value <= holes[mid].first)
            end = mid - 1;
        else
            start = mid + 1;
    }

    return holes[start].second;
}