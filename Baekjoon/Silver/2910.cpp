#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    int count, index;
};

bool compare(pair<int, Node>& a, pair<int, Node>& b) {
    if (a.second.count == b.second.count) return a.second.index < b.second.index;
    return a.second.count > b.second.count;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, C, number;
    cin >> N >> C;
    unordered_map<int, Node> numbers;

    for (int i = 0; i < N; i++) {
        cin >> number;
        if (numbers.find(number) == numbers.end()) numbers[number] = {1, i};
        else numbers[number].count += 1;
    }
    
    vector<pair<int, Node>> numVec(numbers.begin(), numbers.end());
    sort(numVec.begin(), numVec.end(), compare);
    
    for (int i = 0; i < numVec.size(); i++) {
        for (int j = 0; j < numVec[i].second.count ; j++) cout << numVec[i].first << " ";
    }
    
    return 0;
}