#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int Index(int element, deque<int> deque);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, search;
    cin >> N >> M;

    deque<int> deque;

    for (int i = 1; i <= N; i++) {
        deque.push_back(i);
    }

    int count = 0;
    
    while (M--) {
        cin >> search;

        while (true) {
            if (search == deque.front()) {
                deque.pop_front();
                break;
            }

            int idx = Index(search, deque);

            if (idx == -1) {
                cout << "Index is not found!\n";
                break;
            }

            if (idx > deque.size() / 2) {
                auto cur = deque.back();
                deque.pop_back();
                deque.push_front(cur);
                count += 1;
            }
            else if (idx <= deque.size() / 2) {
                auto cur = deque.front();
                deque.pop_front();
                deque.push_back(cur);
                count += 1;
            }
        }
    }
    cout << count;
}

int Index(int element, deque<int> deque) {
    for (int i = 0; i < deque.size(); i++) {
        if (deque[i] == element) return i;
    }
    return -1;
}