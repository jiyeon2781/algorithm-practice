#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void Start();

queue<int> trucks;
queue<int> bridge;

int N, W, L;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> W >> L;

    int num;
    for (int i = 0; i < N; i++) {
        cin >> num;
        trucks.push(num);
    }

    Start();

    return 0;
}

// 1초 단위로 계산 -> 시간 건너뛰기 금지
void Start() {
    int time = 0, weight = 0;

    for (int i = 0; i < W; i++)
        bridge.push(0);

    while (!bridge.empty()) {
        time += 1;

        weight -= bridge.front();
        bridge.pop();

        if (!trucks.empty()) {
            if (weight + trucks.front() <= L) {
                weight += trucks.front();
                bridge.push(trucks.front());
                trucks.pop();
            }
            else 
                bridge.push(0);
        }
    }

    cout << time;
}