#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 301;
int arr[MaxSize][MaxSize];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
        }
    }

    cin >> K;
    pair<int, int> start, end;

    while (K--) {
        cin >> start.first >> start.second >> end.first >> end.second;
        cout << arr[end.first][end.second] - arr[start.first - 1][end.second] - arr[end.first][start.second - 1] + arr[start.first - 1][start.second - 1] << "\n";
    }
}
