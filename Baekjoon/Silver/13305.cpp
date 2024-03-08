#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    long long num;
    vector<long long> dist, price;

    for (int i = 0; i < N - 1; i++) {
        cin >> num;
        dist.push_back(num);
    }
    for (int i = 0; i < N; i++) {
        cin >> num;
        price.push_back(num);
    }

    long long minOilPrice = price[0], result = 0;

    for (int i = 0; i < N - 1; i++) {
        if (minOilPrice > price[i]) minOilPrice = price[i];
        result += minOilPrice * dist[i];
    }

    cout << result << "\n";
}
