#include <iostream>
#include <algorithm>

using namespace std;

int CalculateFirstPlan(int second);
int CalculateSecondPlan(int second);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, second, firstSum = 0, secondSum = 0;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> second;
        firstSum += CalculateFirstPlan(second);
        secondSum += CalculateSecondPlan(second);
    }

    if (firstSum > secondSum) cout << "M " << secondSum;
    else if (firstSum < secondSum) cout << "Y " << firstSum;
    else cout << "Y M " << firstSum;
} 

int CalculateFirstPlan(int second) {
    return (second / 30 + 1) * 10;
}

int CalculateSecondPlan(int second) {
    return (second / 60 + 1) * 15;
}