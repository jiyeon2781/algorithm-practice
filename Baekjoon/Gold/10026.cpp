#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_NUM 101

using namespace std;

struct Node {
    int x, y;
};

int dirX[4] = { 0, 0, -1, 1 };
int dirY[4] = { 1, -1, 0, 0 };

bool visited[MAX_NUM][MAX_NUM];

void BFS(vector<vector<char>> picture, int x, int y, bool blindness);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    char pixel;
    vector<vector<char>> picture;
    for (int i = 0; i < n; i++) {
        vector<char> pixels;
        for (int j = 0; j < n; j++) {
            cin >> pixel;
            pixels.push_back(pixel);
        }
        picture.push_back(pixels);
    }

    int normalCount = 0, blindnessCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                BFS(picture, i, j, false);
                normalCount += 1;
            }
        }
    }

    fill_n(visited[0], MAX_NUM * MAX_NUM, false);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                BFS(picture,i, j, true);
                blindnessCount += 1;
            }
        }
    }

    cout << normalCount << ' ' << blindnessCount << "\n";
    return 0;
}

void BFS(vector<vector<char>> picture, int x, int y, bool blindness) {
    queue<Node> que;
    que.push({ x, y });
    char color = picture[x][y];
    int picSize = picture.size();
    while (!que.empty()) {
        int curX = que.front().x;
        int curY = que.front().y;
        que.pop();
        if (visited[curX][curY]) continue;
        visited[curX][curY] = true;
        for (int i = 0; i < 4; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            if (nextX >= picSize || nextX < 0 || nextY >= picSize || nextY < 0) continue;
            
            if (!blindness) { // 일반 조건
                if (picture[nextX][nextY] != color) continue;
            }
            else { // 적록색약 조건
                if (color == 'R' || color == 'G') {
                    if (picture[nextX][nextY] == 'B') continue;
                }
                else {
                    if (picture[nextX][nextY] != color) continue;
                }
            }
            que.push({ nextX , nextY });
        }
    }
}
