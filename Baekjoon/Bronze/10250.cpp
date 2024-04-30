#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, H, W, N;
    cin >> tc;
    while (tc--) {
        cin >> H >> W >> N;
        int roomNum = (N / H);
        if ((N % H) != 0) roomNum += 1;
        int floor = (N % H) * 100;
        if ((N % H) == 0) floor = (((N - 1) % H) + 1) * 100;

        cout << floor + roomNum << "\n";
    }
}