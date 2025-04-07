#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int x, y;
    int rainbowCnt;
    int score;
};

struct Compare {
    bool operator()(Node a, Node b) {
        if (a.rainbowCnt == b.rainbowCnt) {
            if (a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        }
        return a.rainbowCnt < b.rainbowCnt;
    }
};

int AutoPlay(int N);
void InitVisited(int N);
void InitIdxBoard(int N);
Node SearchBlockGroup(int N);
pair<int, int>  BFS(int N, pair<int, int> start, int color, int idx);
void DeleteMap(int N, Node start);
void ApplyGravity(int N);
void Rotation(int N);
void DropBlock(int startColumn, int N);

const int MaxSize = 21;
const int MaxColor = 6;
const int Dir = 4;
 
int board[MaxSize][MaxSize];
int newBoard[MaxSize][MaxSize];
bool visited[MaxSize][MaxSize];
int idxBoard[MaxSize][MaxSize];

int dirX[Dir] = { 1, -1, 0, 0 };
int dirY[Dir] = { 0, 0, 1, -1 };

int main()
{ // https://www.acmicpc.net/board/view/111179 -> 해당 반례에서 0 2 2를 인식하지 못함 -> 우선순위가 잘못된 것으로 추정
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    int total = AutoPlay(N);
    cout << total;
}

void InitVisited(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }
}

void InitIdxBoard(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            idxBoard[i][j] = 0;
        }
    }
}

int AutoPlay(int N) {
    int score = 0;
    while (true) {
        InitVisited(N);
        // 블록 그룹 중에서 가장 블록이 많고 행열이 작은 그룹 택 1
        // 무엇을 반환? 시작 번호
        Node max = SearchBlockGroup(N);
        if (max.x == -1 && max.y == -1) 
            break;
        score += max.score * max.score;
        // 삭제 후 맵 변경(중력)
        DeleteMap(N, max);

        ApplyGravity(N);
        // 90도로 반시계회전
        Rotation(N);
        // 다시 한 번 중력
        ApplyGravity(N);
    }
    return score;
}

void DeleteMap(int N, Node start) {
    queue<pair<int, int>> que;
    que.push({ start.x, start.y });
    int block = board[start.x][start.y];
    board[start.x][start.y] = -2;

    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;
        que.pop();

        for (int i = 0; i < Dir; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];
            
            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
            if (board[nextX][nextY] == block || board[nextX][nextY] == 0) {
                board[nextX][nextY] = -2;
                que.push({ nextX, nextY });
            }
        }
    }
}

void Rotation(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            newBoard[i][j] = board[j][N-i-1];
        }
    }
    copy(&newBoard[0][0], &newBoard[0][0] + MaxSize * MaxSize, &board[0][0]);
}

void ApplyGravity(int N) {
    for (int j = 0; j < N; j++) DropBlock(j, N);
}

void DropBlock(int startColumn, int N) {
    int curRow = N;
    queue<int> emptyBlockRow;
    while (curRow--) {
        if (board[curRow][startColumn] == -2) emptyBlockRow.push(curRow);
        else if (board[curRow][startColumn] == -1) while (!emptyBlockRow.empty()) emptyBlockRow.pop();
        else if (board[curRow][startColumn] >= 0 && !emptyBlockRow.empty()) {
            int setRow = emptyBlockRow.front();
            emptyBlockRow.pop();
            swap(board[curRow][startColumn], board[setRow][startColumn]);
            emptyBlockRow.push(curRow);
        }
    }
}

Node SearchBlockGroup(int N) { // 블록 그룹 Search (BFS)
    InitIdxBoard(N);
    int maxCnt = 0, idx = 1;
    priority_queue<Node, vector<Node>, Compare> que;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pair<int, int> cnt = { 0, 0 };
            if (idxBoard[i][j] == 0 && board[i][j] >= 1)
                cnt = BFS(N, { i, j }, board[i][j], idx);
            
            if (cnt.first >= 2) {
                if (maxCnt < cnt.first) {
                    maxCnt = cnt.first;
                    while (!que.empty()) que.pop();
                    que.push({ i,j, cnt.second, cnt.first });
                    idx += 1;
                }
                else if (maxCnt == cnt.first) {
                    que.push({ i,j, cnt.second, cnt.first });
                }
            }
        }
    }

    Node result;
    if (!que.empty()) result = que.top();
    else result = { -1, -1, 0, 0 };
    return result;
}

pair<int, int> BFS(int N, pair<int, int> start, int color, int idx) { // 같은 블록 or 무지개 탐색
    queue<pair<int, int>> que;
    que.push(start);
    InitVisited(N);
    visited[start.first][start.second] = true;
    idxBoard[start.first][start.second] = idx;

    int cnt = 1, rainbowCnt = 0;

    while (!que.empty()) {
        int curX = que.front().first;
        int curY = que.front().second;
        que.pop();

        for (int i = 0; i < Dir; i++) {
            int nextX = curX + dirX[i];
            int nextY = curY + dirY[i];

            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
            if (board[nextX][nextY] == -1) continue;
            if (visited[nextX][nextY]) continue;
            if (board[nextX][nextY] != 0 && board[nextX][nextY] != color) continue;
            visited[nextX][nextY] = true;
            cnt += 1;
            if (board[nextX][nextY] == 0) rainbowCnt += 1;
            if (board[nextX][nextY] != 0) idxBoard[nextX][nextY] = idx;
            que.push({ nextX, nextY });
        }
    }
    return { cnt, rainbowCnt };
}