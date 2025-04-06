#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x, y;
    int empty;
};

void AssignSeat(int student, int N);
void Init(int N);
vector<Node> CountFavoriteSeat(int student, int N);
int SumSatisfaction(int N);

bool Compare(Node a, Node b) {
    if (a.empty == b.empty) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
    return a.empty > b.empty;
}

const int MaxSize = 21;
const int FavoriteStudentMaxCnt = 4;
const int Dir = 4;

int seat[MaxSize][MaxSize];
int favoriteCnt[MaxSize][MaxSize];

int favoriteList[MaxSize * MaxSize][MaxSize * MaxSize];

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1 };

int satisfaction[5] = { 0, 1, 10, 100, 1000 };
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int student, curFavorite;

    for (int idx = 1; idx <= N * N; idx++) {
        cin >> student;
        for (int i = 0; i < FavoriteStudentMaxCnt; i++) {
            cin >> curFavorite;
            favoriteList[student][curFavorite] = 1;
        }
        AssignSeat(student, N);
    }

    int result = SumSatisfaction(N);
    cout << result;
}

void Init(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            favoriteCnt[i][j] = 0;
        }
    }
}

void AssignSeat(int student, int N) {
    // 자리 지정
    Init(N);

    // favoriteCnt에 저장된 Count를 통해 지정
    // 여러개일 수 있으므로 리스트에 저장
    vector<Node> maxCntFavoriteSeats = CountFavoriteSeat(student, N);

    // 가장 좋아하는 사람이 많은 자리를 저장
    seat[maxCntFavoriteSeats[0].x][maxCntFavoriteSeats[0].y] = student;
}

vector<Node> CountFavoriteSeat(int student, int N) { // 각 자리별 만족도, 빈자리 수 구함
    int maxCnt = 0, emptyCnt = 0;
    vector<Node> maxCntList;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            emptyCnt = 0;
            if (seat[i][j] != 0) continue;

            // 인접한 자리 중 빈자리 or 좋아하는 번호 자리
            for (int dir = 0; dir < Dir; dir++) {
                int nextX = i + dirX[dir];
                int nextY = j + dirY[dir];

                if (nextX >= N || nextX < 0 || nextY >= N || nextY < 0) continue;
                if (seat[nextX][nextY] == 0) emptyCnt += 1;
                else {
                    // 좋아하는 사람인지 확인
                    if (favoriteList[student][seat[nextX][nextY]] == 1) {
                        // 좋아하는 사람일 때
                        favoriteCnt[i][j] += 1;
                    }
                }
            }

            if (maxCnt < favoriteCnt[i][j]) {
                maxCnt = favoriteCnt[i][j];
                maxCntList.clear();
                maxCntList.push_back({ i, j, emptyCnt});
            }
            else if (maxCnt == favoriteCnt[i][j]) {
                maxCntList.push_back({ i, j, emptyCnt});
            }
        }
    }

    sort(maxCntList.begin(), maxCntList.end(), Compare);
    return maxCntList;
}

int SumSatisfaction(int N) { // 만족도 총합
    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cnt = 0;
            for (int dir = 0; dir < Dir; dir++) {
                int nextX = i + dirX[dir];
                int nextY = j + dirY[dir];

                if (nextX >= N || nextX < 0 || nextY >= N || nextY < 0) continue;
                if (favoriteList[seat[i][j]][seat[nextX][nextY]] == 1) cnt += 1;
            }
            result += satisfaction[cnt];
        }
    }
    return result;
}