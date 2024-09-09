#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxSize = 10001;

struct Node {
    int start;
    int end;
    int cost;
};

bool compare(const Node& a, const Node& b) {
    return a.cost < b.cost;
}

void InitArray(int v);
void Kruskal(int v);
int FindParent(int x);
void Union(int a, int b);

vector<Node> edges;

int parent[MaxSize];
int ranking[MaxSize];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E;

    cin >> V >> E;

    int A, B, C;

    while (E--) {
        cin >> A >> B >> C;
        edges.push_back({ A, B, C }); // 가중치의 오름차순으로 정렬
    }

    sort(edges.begin(), edges.end(), compare);

    Kruskal(V);
}

void Kruskal(int v) {
    int vertexCnt = 0, resultCost = 0;
    InitArray(v);

    for (int i = 0; i < edges.size(); i++) {
        if (FindParent(edges[i].start) == FindParent(edges[i].end)) // 사이클이면 continue
            continue;
        Union(edges[i].start, edges[i].end);
        resultCost += edges[i].cost; 
        vertexCnt += 1;

        if (vertexCnt == v - 1) break;
    }
    cout << resultCost;
}


void InitArray(int v) { // union find를 위한 배열 초기화
    for (int i = 1; i <= v; i++) {
        parent[i] = i;
        ranking[i] = 0;
    }
}

int FindParent(int x) { // parent node 찾기 -> 경로 압축으로 최적화
    if (parent[x] == x) return x;
    else return parent[x] = FindParent(parent[x]);
}

void Union(int a, int b) { // a, b의 부모를 하나로 통일
    int x = FindParent(a);
    int y = FindParent(b);

    if(x == y) return; // 두 값의 parent가 같으면 합치지 않음

    // 시간초과로 인해 union 연산 최적화
    // ranking에 트리 높이 저장, 항상 높이가 더 낮은 트리를 높은 트리 밑에 넣음
    if (ranking[x] < ranking[y]) parent[x] = y; 
    else {
         parent[y] = x;
         if (ranking[x] == ranking[y]) ranking[x] += 1;
    }
}

// 참고
// 1. union find : https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html
// 2. kruskal : https://gmlwjd9405.github.io/2018/08/29/algorithm-kruskal-mst.html