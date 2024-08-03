#include <iostream>
#include <algorithm>

#define MAX_NUM 46

using namespace std;

int F[MAX_NUM];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i <= N; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }

    cout << F[N];
}