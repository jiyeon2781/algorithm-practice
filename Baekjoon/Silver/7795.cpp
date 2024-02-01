#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int T, N, M, num,count;
    cin >> T;
    vector<int> A, B;
    
    while (T--) {
        cin >> N >> M;
        A.clear();
        B.clear();
        count = 0;

        while (N--) {
            cin >> num;
            A.push_back(num);
        }
        
        while (M--) {
            cin >> num;
            B.push_back(num);
        }

        sort(A.begin(), A.end(), greater<int>());
        sort(B.begin(), B.end());

        for (int elementA : A) {
            for (int elementB : B) {
                if (elementA <= elementB) break;
                count += 1;
            }
        }

        cout << count << "\n";
    }

    return 0;
}
