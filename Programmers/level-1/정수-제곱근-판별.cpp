#include <cmath>

using namespace std;

long long solution(long long n) {
    long double num = sqrt(n);
    if (num == floor(num)) return (num+1) * (num+1);
    else return -1;
}