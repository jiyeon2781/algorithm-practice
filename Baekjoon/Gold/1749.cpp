#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 201;
const int MinNum = -2000000;

int matrix[MaxSize][MaxSize];
int sum[MaxSize][MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++){
            cin >> matrix[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i][j];
        }
    }

    int result = MinNum;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int l = i; l <= N; l++) {
                for (int k = j; k <= M; k++) {
                    int cur = sum[l][k] - sum[l][j - 1] - sum[i - 1][k] + sum[i - 1][j - 1];
                    if (cur > result) result = cur;
                }
            }
        }
    }
    cout << result;
}