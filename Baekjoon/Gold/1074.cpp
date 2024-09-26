#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int Recursive(int N, int r, int c);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, r, c;
    cin >> N >> r >> c;

    int result = Recursive(N, r, c);
    cout << result;
}

int Recursive(int N, int r, int c) {
    if (N == 0) return 0;
    int halfSize = (int)pow(2, N - 1);

    if (halfSize > r && halfSize > c) return Recursive(N - 1, r, c); // 4등분 후 좌측 위 사각형
    else if (halfSize > r && halfSize <= c) return halfSize * halfSize + Recursive(N - 1, r, c - halfSize); // 4등분 후 우측 위 사각형
    else if (halfSize <= r && halfSize > c) return 2 * halfSize * halfSize + Recursive(N - 1, r - halfSize, c); // 4등분 후 좌측 아래 사각형
    else return 3 * halfSize * halfSize + Recursive(N - 1, r - halfSize, c - halfSize); // 4등분 후 우측 아래 사각형
}