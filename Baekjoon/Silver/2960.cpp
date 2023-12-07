#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM 1001

using namespace std;

bool isPrimeNumber[MAX_NUM];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K, count = 0, result = 0, isSearch = false;
    cin >> N >> K;

    for (int i = 2; i <= N; i++) {
        if (!isPrimeNumber[i]) {
            for (int j = i; j <= N; j += i) {
                if (isPrimeNumber[j]) continue;
                count += 1;
                isPrimeNumber[j] = true;
                if (count == K) {
                    result = j;
                    isSearch = true;
                    break;
                }
                
            }
            if (isSearch) break;
        }
    }
    cout << result;
    return 0;
}
