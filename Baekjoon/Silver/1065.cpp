#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

bool IsSequence(int num);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (IsSequence(i)) {
            cnt += 1;
        }
    }
    cout << cnt;
    return 0;
}


bool IsSequence(int num) {
    vector<int> vec;

    while (num > 0) {
        vec.push_back(num % 10);
        num /= 10;
    }

    if (vec.size() < 3)
        return true;

    int diff = vec[0] - vec[1];

    for (int i = 1; i < vec.size() - 1; i++) {
        if (vec[i] - vec[i + 1] != diff)
            return false;
    }
    return true;
}