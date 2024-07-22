#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, height;
    long long result = 0;

    cin >> N;
    vector<int> heights;
    while (N--) {
        cin >> height;
        heights.push_back(height);
    }

    stack<int> st;

    // 각 건물마다 빌딩 관찰 가능 시점을 stack에 저장 후 저장되어 있던 순간의 합이 각 빌딩에서 관찰 가능한 빌딩의 개수가 됨
    for (int element : heights)
    {
        if (st.empty()) st.push(element);
        else {
            if (st.top() > element) st.push(element);
            else if (st.top() <= element) {
                while (!st.empty() && st.top() <= element) st.pop(); // 현재 건물보다 이전 건물이 낮으면 pop
                st.push(element);
            }
        }
        result += (st.size() - 1);
    }

    cout << result;
} 