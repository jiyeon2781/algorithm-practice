#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 11;

int moneys[MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, K;
    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        cin >> moneys[i];
    }

    int result = 0, index = 0;

    for (int i = N - 1; i >= 0; i--) {
        if (K >= moneys[i]) {
            while (K >= moneys[i]) {
                K -= moneys[i];
                result += 1;
            }
        }
        if (K == 0) break;
    }

    cout << result;
}