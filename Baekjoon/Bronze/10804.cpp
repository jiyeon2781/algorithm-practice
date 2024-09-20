#include <iostream>
#include <algorithm>

using namespace std;

void Print(int nums[]);
void ReverseNum(int start, int end, int nums[]);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int nums[21];
    int start, end;
    for (int i = 1; i <= 20; i++) nums[i] = i;

    for (int i = 0; i < 10; i++) {
        cin >> start >> end;
        ReverseNum(start, end, nums);
    }
    Print(nums);
} 

void Print(int nums[]) {
    for (int i = 1; i <= 20; i++) cout << nums[i] << ' ';
}

void ReverseNum(int start, int end, int nums[]) {
    int size = end - start + 1;
    int endIdx = end;
    for (int i = start; i < (size / 2) + start; i++) 
        swap(nums[i], nums[endIdx--]);
}