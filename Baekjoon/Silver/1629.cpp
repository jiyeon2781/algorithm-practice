#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long recursive(long long A, long long B, long long C);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long A, B, C;
    cin >> A >> B >> C;
    cout << recursive(A, B, C) << "\n";
    return 0;
}

long long recursive(long long A, long long B, long long C) {
    /* O(B) 시간 복잡도 -> 해당 문제에선 시간초과
    long long value = 1;
    while (B--) value = value * A % C;
    return value;
    */

    // A^n * A^n = a^2n;
    // 12^58 = 4 (mod 67)
    // 12^116 = (4)^2 mod 67 = 16
    if (B == 1) return A % C;
    long long value = recursive(A, B / 2, C);
    value = value * value % C;
    if (B % 2 == 1) return value * A % C; // 홀수이면 value에 A를 한번 더 곱해야 함
    else return value;
    // 모듈러 연산 사용 -> B가 절반으로 깍이므로 O(log B)
}