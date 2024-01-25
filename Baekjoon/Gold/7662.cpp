#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int T, N, queSize, popNum;
    cin >> T;

    int operNum;
    char oper;

    for (int tc = 0; tc < T; tc++) {
        cin >> N;
        priority_queue<int> maxQue; // 최대 힙
        priority_queue<int, vector<int>, greater<int>> minQue; // 최소 힙
        map<int, int> countQue; // 현재 저장되어있는 원소의 개수
        queSize = 0;

        for (int i = 0; i < N; i++) {
            cin >> oper >> operNum;
            
            // I num : Q에 해당 num을 삽입하는 연산
            if (oper == 'I') {
                maxQue.push(operNum);
                minQue.push(operNum);
                if (countQue.find(operNum) == countQue.end()) countQue.insert({ operNum, 1 });
                else countQue[operNum] += 1;
                queSize += 1;
                continue;
            }

            if (queSize == 0) continue;
            queSize -= 1;
            if (operNum == -1) {
                // D -1 : Q에서 최솟값을 삭제하는 연산
                if (minQue.empty()) continue;
                while (countQue[minQue.top()] == 0) minQue.pop(); // 존재하지 않는 원소는 삭제
                popNum = minQue.top();
                minQue.pop();
            }
            else if (operNum == 1) {
                // D 1 : Q에서 최댓값을 삭제하는 연산
                if (maxQue.empty()) continue;
                while (countQue[maxQue.top()] == 0) maxQue.pop();
                popNum = maxQue.top();
                maxQue.pop();
            }
            countQue[popNum] -= 1;
        }

        // 결과 출력
        if (queSize == 0) cout << "EMPTY\n";
        else {
            while (countQue[maxQue.top()] == 0) maxQue.pop();
            while (countQue[minQue.top()] == 0) minQue.pop();
            cout << maxQue.top() << ' ' << minQue.top() << "\n";
        }
    }
    return 0;
}