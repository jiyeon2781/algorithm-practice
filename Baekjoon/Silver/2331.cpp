#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

void CalNumber(long long A, long long P);

vector<long long> result;
int idx = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long A, P;
    cin >> A >> P;

    result.push_back(A);
    CalNumber(A, P);
    cout << idx;
    return 0;
}

void CalNumber(long long A, long long P) {
    long long cur = 0;
    do
    {
        long long num = A % 10;
        A /= 10;
        cur += pow(num, P);
    } while (A > 0);

    for (int i = 0; i < result.size(); i++) {
        if (result[i] == cur)
        {
            idx = i;
            return;
        }
    }
    result.push_back(cur);
    CalNumber(cur, P);
}