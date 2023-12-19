#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long minimumTime;
long long BinarySearch(long long first, long long last, int n, vector<int> times);

long long solution(int n, vector<int> times) {
    minimumTime = 0;
    sort(times.begin(), times.end());
    long long answer = BinarySearch(1, n * (long long) times.back(), n, times);
    return answer;
}

long long BinarySearch(long long first, long long last, int n, vector<int> times){
    if (first > last) return minimumTime;
    long long mid = (first + last) / 2;
    // mid : 심사를 받는데 걸리는 시간
    long long count = 0;
    for (long long time : times) count += (mid / time);
    // mid 시간 기준 몇 명의 인원이 처리되었는지 확인
    if (count >= n) {
        minimumTime = mid;
        return BinarySearch(first, mid - 1, n, times);
    }
    else return BinarySearch(mid + 1, last, n, times);
}