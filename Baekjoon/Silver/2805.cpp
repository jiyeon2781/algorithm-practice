#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int BinarySearch(int start, int end, int value);

vector<int> trees;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, num;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> num;
        trees.push_back(num);
    }

    sort(trees.begin(), trees.end());

    cout << BinarySearch(0, trees[N-1], M);
}

int BinarySearch(int start, int end, int value) {
    int result = 0, mid;
    long long cur, sum;
    while (start <= end) {
        mid = (start + end) / 2;
        cur = 0;

        for (auto element : trees) {
            if (mid > element) continue;
            cur += (long long) (element - mid);
        }

        if (cur >= value) {
            if (result == 0 || cur < sum) {
                result = mid;
                sum = cur;
            }
            start = mid + 1;
        }
        else end = mid - 1;
    }
    return result;
}