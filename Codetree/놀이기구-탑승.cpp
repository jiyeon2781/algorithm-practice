#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int emptyCnt;
    int favoriteStudentCnt;
    int r, c;
};

Info SelectSeat(int student);
int Score();
int FavoriteCnt(pair<int, int> cur);

const int MaxSize = 21;
const int Dir = 4;

int rides[MaxSize][MaxSize];
vector<int> favorite;
vector<int> favorites[MaxSize * MaxSize];

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1 };

int n;

int scores[5] = { 0, 1, 10, 100, 1000 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    int student, favStudent;
    for (int i = 0; i < n * n; i++) {
        favorite.clear();

        cin >> student;
        for (int j = 0; j < 4; j++) {
            cin >> favStudent;
            favorite.push_back(favStudent);
        }
        favorites[student] = favorite;
        Info result = SelectSeat(student);
        // 현재 원하는 자리를 반환 -> rides에 현재 idx 저장
        rides[result.r][result.c] = student;
    }

    cout << Score();
    return 0;
}

Info SelectSeat(int student) {
    Info fav = { -1, -1, 0, 0 };

    // N * N 격자를 탐색
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 현재 칸이 비었는지 확인
            if (rides[i][j] != 0)
                continue;

            // 현재 r, c에서 좋아하는 학생 수 확인
            // 현재 r, c에서 빈 칸 확인
            int emptyCnt = 0, favoriteCnt = 0;

            for (int d = 0; d < Dir; d++) {
                pair<int, int> next = { i + dirX[d], j + dirY[d] };
                if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
                    continue;
                if (rides[next.first][next.second] == 0)
                    emptyCnt += 1;
                else { // 좋아하는 학생이 있는지 확인
                    for (auto st : favorite) {
                        if (st == rides[next.first][next.second])
                        {
                            favoriteCnt += 1;
                        }
                    }
                }
            }
            // 학생 수가 fav 학생 수보다 많으면 저장
            // fav 학생 수와 동일하면 빈 칸 개수 확인
            // 빈칸 개수가 많으면 fav에 저장

            if (fav.favoriteStudentCnt < favoriteCnt || (fav.favoriteStudentCnt == favoriteCnt && fav.emptyCnt < emptyCnt)) {

                fav = { emptyCnt, favoriteCnt, i, j };
            }
        }
    }

    return fav;
}

int Score() {
    int result = 0;
    // N * N 격자 탐색 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cnt = FavoriteCnt({i, j});
            result += scores[cnt];
        }
    }
    return result;
}

int FavoriteCnt(pair<int, int> cur) {
    int cnt = 0;
    for (int i = 0; i < Dir; i++) {
        pair<int, int> next = { cur.first + dirX[i], cur.second + dirY[i] }; 
        if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
            continue;
        for (auto st : favorites[rides[cur.first][cur.second]]) {
            if (st == rides[next.first][next.second])
                cnt += 1;
        }
    }
    return cnt;
}