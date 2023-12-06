#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, num;
    cin >> N >> M;
    vector<int> numbers;

    for (int i = 0; i < N; i++) {
        cin >> num;
        numbers.push_back(num);
    }

    int start = 0, end = 0, result = 0, currentSum = 0;
    while (end <= N) {
        if (currentSum == M) result += 1;
        if (currentSum >= M) currentSum -= numbers[start++];
        else if (end == N) break;
        else currentSum += numbers[end++];
    }

    cout << result;

    return 0;
}
