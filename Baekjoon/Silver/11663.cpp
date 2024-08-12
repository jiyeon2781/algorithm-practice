#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM 100001

using namespace std;

int BinarySearch(int left, int right);

int dots[MAX_NUM], N;
// vector로 진행하니 시간 초과 문제로 수정

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M, left, right, result;
    cin >> N >> M;


    for (int i = 0; i < N; i++) 
        cin >> dots[i];

    sort(dots, dots + N);

    while (M--) {
        cin >> left >> right;

        result = BinarySearch(left, right); // 1. 이분 탐색

        // result = upper_bound(dots, dots + N, right) - lower_bound(dots, dots + N, left);
        // 2. 이분 탐색 라이브러리

        cout << result << "\n";
    }
}

int BinarySearch(int left, int right)
{
    int count;

    int start = 0;
    int end = N - 1;

    while (start <= end) { // 우측 부분 인덱스를 구하기 위한 이분 탐색
        int mid = (start + end) / 2;

        if (dots[mid] > right) end = mid - 1;
        else start = mid + 1;
    }
    count = end + 1;

    start = 0;
    end = N - 1;

    while (start <= end) { // 좌측 부분 인덱스를 구하기 위한 이분 탐색
        int mid = (start + end) / 2;

        if (dots[mid] < left) start = mid + 1; 
        else end = mid - 1;
    }
    count -= start;

    return count;
}