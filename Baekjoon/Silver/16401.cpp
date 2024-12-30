#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int BinarySearch(int start, int end, int M);
// start : 과자의 최소 길이, end : 과자의 최대 길이
vector<int> snacks;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M, N, num;
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        snacks.push_back(num);
    }

    sort(snacks.begin(), snacks.end());

    int result = BinarySearch(1, snacks[N - 1], M); 
    // 나눠줄 수 있는 과자의 최대 길이를 반환
    cout << result << "\n";
}

int BinarySearch(int start, int end, int M) {
    int result = 0, cnt = 0;
    
    while (start <= end) {
        int mid = (start + end) / 2;
        cnt = 0;
        for (auto snack : snacks) cnt += (snack / mid);
        // mid 길이로 나오는 과자의 개수 count

        if (cnt >= M) {
            start = mid + 1;
            if (result < mid) result = mid;
        }
        else end = mid - 1;
    }
    return result;
}