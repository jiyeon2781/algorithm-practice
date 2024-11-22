#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MaxSize = 11;

void Backtracking(vector<vector<int>> ability, int depth, int max);

int result = 0;
int solution(vector<vector<int>> ability) {
    Backtracking(ability, 0, ability.size());
    return result;
}

int curScore = 0;
bool isParticipate[MaxSize];

void Backtracking(vector<vector<int>> ability, int depth, int max) {
    if (depth == ability[0].size()) {
        if (curScore > result) result = curScore;
        return;
    }

    for (int i = 0; i < max; i++) {
        if (isParticipate[i]) continue;
        isParticipate[i] = true;
        curScore += ability[i][depth];
        Backtracking(ability, depth + 1, max);
        curScore -= ability[i][depth];
        isParticipate[i] = false;
    }
}