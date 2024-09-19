#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num, front = 0;
    int cnt = 3;
    vector<char> result;

    while (cnt--) {
        front = 0;

        for (int i = 0; i < 4; i++) {
            cin >> num;
            if (cin.eof() == 1) return 0;
            if (num == 0) front += 1;
        }

        if (front == 1) result.push_back('A');
        else if (front == 2) result.push_back('B');
        else if (front == 3) result.push_back('C');
        else if (front == 4) result.push_back('D');
        else result.push_back('E');
    }

    for (char element : result) {
        cout << element << "\n";
    }
    
} 