#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long start, end, cnt;
    cin >> start >> end;

    if (end < start) swap(start, end);

    cnt = end - start - 1 < 0 ? 0 : end - start - 1;
    cout << cnt << "\n";

    for (long long i = start + 1; i < end; i++) cout << i << ' ';
} 