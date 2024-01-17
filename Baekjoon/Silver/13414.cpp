#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

bool compare(pair<string, int>& a, pair<string, int>& b) {
    return a.second < b.second;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int K, L;
    string number;
    unordered_map<string, int> waitingList;
    cin >> K >> L;
    for (int i = 0; i < L; i++) {
        cin >> number;
        waitingList[number] = i + 1;
    }

    vector<pair<string, int>> vectorList(waitingList.begin(), waitingList.end());
    sort(vectorList.begin(), vectorList.end(), compare);

    int index = 0;
    for (auto student : vectorList) {
        if (index >= K) break;
        cout << student.first << "\n";
        index += 1;
    }

    return 0;
}