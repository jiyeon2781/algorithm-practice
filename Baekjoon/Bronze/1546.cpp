#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric> 

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, num;
    cin >> n;
    vector<float> scores;
    for (int i = 0; i < n; i++) {
        cin >> num;
        scores.push_back(num);
    }

    sort(scores.begin(), scores.end(), greater<>());
    int maxScore = scores[0];
    for (int i = 0; i < n; i++) scores[i] = scores[i] / maxScore * 100;

    float mean = accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
    cout << mean << "\n";
    return 0;
}

