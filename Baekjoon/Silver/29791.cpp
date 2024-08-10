#include <iostream>
#include <algorithm>
#include <queue>

#define ERDA_COOLTIME 100
#define ORIGIN_COOLTIME 360
#define IMMUNITY_COOLTIME 90

using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    priority_queue<int, vector<int>, greater<int>> erdaSkillTime;
    priority_queue<int, vector<int>, greater<int>> originSkillTime;

    int erdaTimeCount, originTimeCount;
    long long time;
    cin >> erdaTimeCount >> originTimeCount;
    
    while (erdaTimeCount--) {
        cin >> time;
        erdaSkillTime.push(time);
    }

    while (originTimeCount--) {
        cin >> time;
        originSkillTime.push(time);
    }

    int erdaResult = 0, originResult = 0;
    long long coolTimeEnd = 0, immunityEnd = 0;

    while (!erdaSkillTime.empty()) {
        time = erdaSkillTime.top();

        if (coolTimeEnd <= time && immunityEnd <= time) {
            erdaResult += 1;
            coolTimeEnd = time + ERDA_COOLTIME;
            immunityEnd = time + IMMUNITY_COOLTIME;
        }
        
        erdaSkillTime.pop();
    }

    coolTimeEnd = 0, immunityEnd = 0;
    while (!originSkillTime.empty()) {
        time = originSkillTime.top();

        if (coolTimeEnd <= time && immunityEnd <= time)
        {
            originResult += 1;
            coolTimeEnd = time + ORIGIN_COOLTIME;
            immunityEnd = time + IMMUNITY_COOLTIME;
        }

        originSkillTime.pop();
    }

    cout << erdaResult << ' ' << originResult;
}