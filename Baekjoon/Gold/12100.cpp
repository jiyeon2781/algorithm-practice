#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Backtracking(vector<vector<int>> map, int depth, int maxDepth);
vector<vector<int>> CalculateAndMoving(vector<vector<int>> map, int dir);

const int Dir = 4;
const int MaxCount = 5;

int result = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<vector<int>> map;
    vector<int> nums;
    int N, num;

    cin >> N;

    for (int i = 0; i < N; i++) {
        nums.clear();
        for (int j = 0; j < N; j++) {
            cin >> num;
            nums.push_back(num);
            if (num > result) result = num;
        }
        map.push_back(nums);
    }

    Backtracking(map, 0, MaxCount);
    cout << result;
}

void Backtracking(vector<vector<int>> map, int depth, int maxDepth) {
    if(depth == maxDepth) return;
    
    for (int i = 0; i < Dir; i++) {
        auto nextMap = CalculateAndMoving(map, i);
        Backtracking(nextMap, depth + 1, maxDepth);
    }
}

vector<vector<int>> CalculateAndMoving(vector<vector<int>> map, int dir) {
    int idx = 0;
    int prev = 0;
    vector<int> nums(map.size(), 0);
    vector<vector<int>> resultMap(map.size(), nums);

    if (dir == 0) { // 좌
        for (int i = 0; i < map.size(); i++) {
            prev = 0;
            idx = 0;
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == 0) continue;
                if (prev == map[i][j]) { // prev와 현재 위치의 숫자가 동일할 때
                    resultMap[i][idx++] = prev * 2;
                    if (result < prev * 2) result = prev * 2;
                    prev = 0;
                    continue;
                }
                else if (prev != map[i][j] && prev != 0) // prev와 현재 위치 숫자가 동일하지 않을 때
                    resultMap[i][idx++] = prev;
                prev = map[i][j];
            }

            if (prev != 0) resultMap[i][idx] = prev;
        }
    }
    else if (dir == 1) { // 우
        for (int i = 0; i < map.size(); i++) {
            prev = 0;
            idx = map[i].size() - 1;
            for (int j = map[i].size() - 1; j >= 0; j--) {
                if (map[i][j] == 0) continue;
                if (prev == map[i][j]) { // prev와 현재 위치의 숫자가 동일할 때
                    resultMap[i][idx--] = prev * 2;
                    if (result < prev * 2) result = prev * 2;
                    prev = 0;
                    continue;
                }
                else if (prev != map[i][j] && prev != 0) // prev와 현재 위치 숫자가 동일하지 않을 때
                    resultMap[i][idx--] = prev;
                prev = map[i][j];
            }

            if (prev != 0) resultMap[i][idx] = prev;
        }
    }
    else if (dir == 2) { // 위
        for (int i = 0; i < map.size(); i++) {
            prev = 0;
            idx = 0;
            for (int j = 0; j < map[i].size(); j++) {
                if (map[j][i] == 0) continue;
                if (prev == map[j][i]) { // prev와 현재 위치의 숫자가 동일할 때
                    resultMap[idx++][i] = prev * 2;
                    if (result < prev * 2) result = prev * 2;
                    prev = 0;
                    continue;
                }
                else if (prev != map[j][i] && prev != 0) // prev와 현재 위치 숫자가 동일하지 않을 때
                    resultMap[idx++][i] = prev;
                prev = map[j][i];
            }

            if (prev != 0) resultMap[idx][i] = prev;
        }
    }
    else if (dir == 3) { // 아래
        for (int i = 0; i < map.size(); i++) {
            prev = 0;
            idx = map[i].size() - 1;
            for (int j = map[i].size() - 1; j >= 0; j--) {
                if (map[j][i] == 0) continue;
                if (prev == map[j][i]) { // prev와 현재 위치의 숫자가 동일할 때
                    resultMap[idx--][i] = prev * 2;
                    if (result < prev * 2) result = prev * 2;
                    prev = 0;
                    continue;
                }
                else if (prev != map[j][i] && prev != 0) // prev와 현재 위치 숫자가 동일하지 않을 때
                    resultMap[idx--][i] = prev;
                prev = map[j][i];
            }

            if (prev != 0) resultMap[idx][i] = prev;
        }
    }
    return resultMap;
}
