#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int H, W, num;
    cin >> H >> W;
    vector<int> blocks;

    for (int i = 0; i < W; i++) {
        cin >> num;
        blocks.push_back(num);
    }

    int left, right, minNum, result  = 0;
    for (int i = 1; i < W - 1; i++) {
        left = *max_element(blocks.begin(), blocks.begin() + i); // 0 ~ i 의 max left
        right = *max_element(blocks.begin() + i + 1, blocks.end()); // i + 1 ~ W의 max right
        minNum = min(left, right); // left, right에서 가장 작은 수 : minNum

        if (minNum > blocks[i]) result += (minNum - blocks[i]); 
        // 현재 블록이 m보다 작으면, 빗물은 고이므로 mminNum - blocks[i]
    }
    cout << result;
}