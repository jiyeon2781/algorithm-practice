#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, L;
    cin >> N >> L;

    for (int i = 0; i < L - 1; i++) cout << '1';
    cout << N;
    // L-1자리수 1 + 1자리수 N
}
