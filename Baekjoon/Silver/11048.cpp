#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 1001;

int candies[MaxSize][MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> candies[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int candy = candies[i][j];

            // 1. (r, c+1)
            if (j >= 1) candies[i][j] = candy + candies[i][j - 1];
            // 2. (r+1, c)
            if (i >= 1) candies[i][j] = max(candy + candies[i - 1][j], candies[i][j]);
            // 3. (r+1, c+1)
            if (i >= 1 && j >= 1) candies[i][j] = max(candy + candies[i - 1][j - 1], candies[i][j]);
        }
    }
    cout << candies[N - 1][M - 1];
}
