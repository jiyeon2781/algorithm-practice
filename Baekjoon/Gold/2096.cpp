#include <iostream>
#include <algorithm>

using namespace std;

const int Size = 3;
const int INF = 1000000;

int cur[Size], minDp[Size], maxDp[Size], prevMin[Size], prevMax[Size];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    fill(minDp, minDp + Size, INF);
    
    while (N--) {
        for (int i = 0; i < Size; i++) cin >> cur[i];

        for (int i = 0; i < Size; i++) {
            minDp[i] = prevMin[i] + cur[i];
            maxDp[i] = prevMax[i] + cur[i];
            if (i != 0) {
                minDp[i] = min(prevMin[i - 1] + cur[i], minDp[i]);
                maxDp[i] = max(prevMax[i - 1] + cur[i], maxDp[i]);
            }
                
            if (i != 2) {
                minDp[i] = min(prevMin[i + 1] + cur[i], minDp[i]);
                maxDp[i] = max(prevMax[i + 1] + cur[i], maxDp[i]);
            }
        }

        for (int j = 0; j < Size; j++) {
            prevMin[j] = minDp[j];
            prevMax[j] = maxDp[j];
        }
    }

    cout << *max_element(maxDp, maxDp + Size) << ' ' << *min_element(minDp, minDp + Size);
}