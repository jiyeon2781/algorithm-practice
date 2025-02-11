#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int BinarySearch(int start, int end, int M);

vector<int> money;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    int num, maxNum = 0;
    for (int i = 0; i < N; i++) {
        cin >> num;
        money.push_back(num);
        maxNum += num;
    }

    int result = BinarySearch(1, maxNum, M);
    cout << result;
}

int BinarySearch(int start, int end, int M) {
    int result = end;

    while (start <= end) {
        int mid = (start + end) / 2;
        int cnt = 0, cur = 0;

        // 1. 1일 ~ M일까지 계산
        bool impossibleWithdraw = false;
        for (int i = 0; i < money.size(); i++) {
            if (money[i] <= cur) cur -= money[i];
            else if (money[i] > cur) {
                if (money[i] > mid) {
                    impossibleWithdraw = true;
                    break;
                }
                cnt += 1;
                cur = mid - money[i];
            }
        }

        // 2. 조건에 부합하면, 최소값인지 확인 후 저장
        if (cnt > M || impossibleWithdraw) start = mid + 1;
        else {
            result = mid;
            end = mid - 1;
        }
    }
    return result;
}