#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 1000000;
int A[MaxSize], B[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];

    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < N + M; i++) {
        if (idx1 >= N) cout << B[idx2++] << ' ';
        else if (idx2 >= M) cout << A[idx1++] << ' ';
        else if (A[idx1] < B[idx2]) cout << A[idx1++] << ' ';
        else cout << B[idx2++] << ' ';
    }
}