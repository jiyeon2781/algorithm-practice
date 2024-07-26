#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, num;
    cin >> N;

    vector<int> result(N, 0);

    for (int i = 1; i <= N; i++) // 키 1~N까지의 사람
    {
        cin >> num;
        
        int count = 0;

        for (int j = 0; j < N; j++) // result라는 빈자리를 미리 두고 정해진 규칙대로 사람을 배치
        {
            if (count == num) { // 왼쪽에 존재하는 사람의 count를 모두 세었을 때 
                if (result[j] != 0) continue; // 이미 사람이 존재한다면 continue
                result[j] = i; // 해당 사람으로 빈자리를 채움
                break;
            }
            if (result[j] == 0) count += 1; // 왼쪽에 존재하는 사람의 count가 아직 충분하지 않을 때
        }
    }

    for (int element : result) 
        cout << element << ' ';
}  
