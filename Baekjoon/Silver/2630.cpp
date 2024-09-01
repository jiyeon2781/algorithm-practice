#include <iostream>
#include <algorithm>

using namespace std;

void divide(int x, int y, int size);
bool IsSameColor(int x, int y, int size);

const int MaxSize = 129;

int paper[MaxSize][MaxSize];
int blue = 0, white = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> paper[i][j];
        }
    }
    divide(1, 1, N);
    cout << white << "\n" << blue;
}

void divide(int x, int y, int size) {
    // 모두 blue? white? -> 맞으면 += 아니면 divide
    if (IsSameColor(x, y, size)) {
        if (paper[x][y] == 1) blue += 1;
        else white += 1;
        return;
    }

    int nextSize = size / 2;

    divide(x, y, nextSize);
    divide(x, y + nextSize, nextSize);
    divide(x + nextSize, y, nextSize);
    divide(x + nextSize, y + nextSize , nextSize);
}

bool IsSameColor(int x, int y, int size) {
    bool isBlue = paper[x][y] == 1 ? true : false;

    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if ((paper[i][j] == 0 && isBlue) || (paper[i][j] == 1 && !isBlue)) return false;
        }
    }
    return true;
}