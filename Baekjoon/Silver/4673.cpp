#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int Cal(int i);

const int MaxNum = 10001;

bool isNum[MaxNum];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i < MaxNum; i++) {
        int cur = i;
        while (true) {
            int next = Cal(cur);
            if (next >= MaxNum)
                break;
            isNum[next] = true;
            cur = next;
        }
    }

    for (int i = 1; i < MaxNum; i++) {
        if (!isNum[i])
            cout << i << "\n";
    }
    return 0;
}

int Cal(int i) {
    int cnt = i;
    while (i > 0) {
        cnt += (i % 10);
        i /= 10;
    }
    return cnt;
}