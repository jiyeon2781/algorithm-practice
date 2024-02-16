#include <iostream>
#include <algorithm>
#include <stack>

#define MAX_NUM 51
#define DIRECTION 8

using namespace std;

int maps[MAX_NUM][MAX_NUM];
bool visited[MAX_NUM][MAX_NUM];

int dirX[DIRECTION] = {0, 0, 1, -1, 1, 1, -1, -1};
int dirY[DIRECTION] = {1, -1, 0, 0, 1, -1, 1, -1};

void DFS(int x, int y, int w, int h);

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int w, h, num, count;
    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;

        fill(&maps[0][0], &maps[MAX_NUM - 1][MAX_NUM], 0);
        fill(&visited[0][0], &visited[MAX_NUM - 1][MAX_NUM], false);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> num;
                maps[i][j] = num;
            }
        }

        count = 0;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (!visited[i][j] && maps[i][j] == 1) {
                    DFS(i, j, w, h);
                    count += 1;
                }
            }
        }

        cout << count << "\n";
    }

    return 0;
}

void DFS(int x, int y, int w, int h) {
    stack<pair<int, int>> st;
    st.push({ x, y });
    while (!st.empty()) {
        int curX = st.top().first;
        int curY = st.top().second;
        st.pop();
        for (int i = 0; i < DIRECTION; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            if (nextX < 0 || nextX >= h || nextY < 0 || nextY >= w) continue;
            if (visited[nextX][nextY] || maps[nextX][nextY] == 0) continue;
            visited[nextX][nextY] = true;
            st.push({ nextX, nextY });
        }
    }
}