#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long minimumTime;
long long BinarySearch(long long first, long long last, int n, vector<int> times);

long long solution(int n, vector<int> times) {
    minimumTime = 1000000000;
    sort(times.begin(), times.end());
    long long answer = BinarySearch(1, n * (long long) times.back(), n, times);
    return answer;
}

long long BinarySearch(long long first, long long last, int n, vector<int> times){
    if (first > last) return minimumTime;
    long long mid = (first + last) / 2;
    long long count = 0;
    for (long long time : times) count += (mid / time);
    if (count >= n) {
        minimumTime = mid;
        return BinarySearch(first, mid - 1, n, times);
    }
    else return BinarySearch(mid + 1, last, n, times);
}