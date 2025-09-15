#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Leader {
    int num;
    string food;
    pair<int, int> location;
};

struct Compare {
    bool operator()(Leader& a, Leader& b) {
        if (a.food.size() == b.food.size()) {
            if (a.num == b.num) {
                if (a.location.first == b.location.first)
                    return a.location.second > b.location.second;
                return a.location.first > b.location.first;
            }
            return a.num < b.num;
        }
        return a.food.size() > b.food.size();
    }
};

const int MaxSize = 51;
const int Dir = 4;

void Start();
void Morning();
void Afternoon();
pair<int, int> SetGroup(pair<int, int> start, int idx, string food);
void Evening();
void Move(int dir, pair<int, int> start, int give);
string AddFood(string food, string studentFood);

int N, T;

string students[MaxSize][MaxSize];
int studentNumber[MaxSize][MaxSize];
int groups[MaxSize][MaxSize];
bool afterGived[MaxSize][MaxSize];
priority_queue<Leader, vector<Leader>, Compare> leaders;

int dirX[Dir] = { -1, 1, 0 ,0 };
int dirY[Dir] = { 0, 0, -1, 1 };

int result[7];
// TCM, TC, TM, CM, M, C, T

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> T;

    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < N; j++) 
            students[i][j] = str[j];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> studentNumber[i][j];
        }
    }

    Start();

    return 0;
}

void Start() {
    while (T--) {
        
        // 아침
        Morning();

        // 점심
        Afternoon();

        // 저녁
        Evening();
        
        for (int i = 0; i < 7; i++) 
            cout << result[i] << ' ';
        cout << "\n";
    }
}

void Morning() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            studentNumber[i][j] += 1;
        }
    }
}

void Afternoon() {
    fill(groups[0], groups[0] + MaxSize * MaxSize, 0);

    int idx = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (groups[i][j] == 0){
                auto leader = SetGroup({ i, j }, idx++, students[i][j]);
                leaders.push({ studentNumber[leader.first][leader.second], students[leader.first][leader.second], leader});
            }
        }
    }
}

pair<int, int> SetGroup(pair<int, int> start, int idx, string food) {
    queue<pair<int, int>> que;
    que.push(start);
    groups[start.first][start.second] = idx;
    studentNumber[start.first][start.second] -= 1;
    pair<int, int> leader = start;
    int cnt = 1;

    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        for (int i = 0; i < Dir; i++) {
            pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] };
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
                continue;
            if (groups[next.first][next.second] != 0 || students[next.first][next.second] != food)
                continue;
            groups[next.first][next.second] = idx;
            que.push(next);
            studentNumber[next.first][next.second] -= 1;
            cnt += 1;
            if (studentNumber[leader.first][leader.second] < studentNumber[next.first][next.second])
                leader = next;
            else if (studentNumber[leader.first][leader.second] == studentNumber[next.first][next.second]) {
                if (leader.first > next.first)
                    leader = next;
                else if (leader.first == next.first && leader.second > next.second)
                    leader = next;
            }
        }
    }
    studentNumber[leader.first][leader.second] += cnt;
    return leader;
}

void Evening() {
    fill(afterGived[0], afterGived[0] + MaxSize * MaxSize, false);
    
    while (!leaders.empty()) {
        Leader leader = leaders.top();
        leaders.pop();

        if (afterGived[leader.location.first][leader.location.second])
            continue;

        int dir = leader.num % Dir;
        int give = leader.num - 1;
        studentNumber[leader.location.first][leader.location.second] = 1;

        Move(dir, leader.location, give);
    }

    fill(result, result + 7, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (students[i][j] == "TCM")
                result[0] += studentNumber[i][j];
            else if (students[i][j] == "TC")
                result[1] += studentNumber[i][j];
            else if (students[i][j] == "TM")
                result[2] += studentNumber[i][j];
            else if (students[i][j] == "CM")
                result[3] += studentNumber[i][j];
            else if (students[i][j] == "M")
                result[4] += studentNumber[i][j];
            else if (students[i][j] == "C")
                result[5] += studentNumber[i][j];
            else if (students[i][j] == "T")
                result[6] += studentNumber[i][j];
        }
    }
}

void Move(int dir, pair<int, int> start, int give) {
    pair<int, int> cur = start;
    string food = students[start.first][start.second];
    int curGive = give;

    while (true) {
        if (curGive <= 0)
            break;

        pair<int, int> next = { cur.first + dirX[dir], cur.second + dirY[dir] };
        cur = next;

        if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N)
            break;

        if (students[next.first][next.second] == food)
            continue;

        // 음식이 다를 경우
        afterGived[next.first][next.second] = true;

        if (studentNumber[next.first][next.second] < curGive) {
            // 강한 전파
            students[next.first][next.second] = food;
            studentNumber[next.first][next.second] += 1;
            curGive -= studentNumber[next.first][next.second];
        }
        else {
            // 약한 전파
            students[next.first][next.second] = AddFood(food, students[next.first][next.second]);
            studentNumber[next.first][next.second] += curGive;
            curGive = 0;
        }
    }
}

string AddFood(string food, string studentFood) {
    for (char ch : food) {
        auto iter = studentFood.find(ch);
        if (iter == string::npos) {
            // 추가
            studentFood += ch;
        }
    }

    if (studentFood.size() == 3) studentFood = "TCM";
    else if (studentFood == "CT") studentFood = "TC";
    else if (studentFood == "MT") studentFood = "TM";
    else if (studentFood == "MC") studentFood = "CM";
    
    return studentFood;
}