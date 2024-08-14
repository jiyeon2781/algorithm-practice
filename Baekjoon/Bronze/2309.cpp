#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> heights;
    int height, max = 0;
    bool end = false;

    for (int i = 0; i < 9; i++) {
        cin >> height;
        heights.push_back(height);
        max += height;
    }

    sort(heights.begin(), heights.end());

    for (int i = 0; i < heights.size() - 1; i++) {
        for (int j = i + 1; j < heights.size(); j++) {

            if (max - (heights[i] + heights[j]) == 100) {
                heights.erase(heights.begin() + j);
                heights.erase(heights.begin() + i);
                end = true;
                break;
            }
        }

        if (end) break;
    }

    for (int element : heights) 
        cout << element << "\n";
}