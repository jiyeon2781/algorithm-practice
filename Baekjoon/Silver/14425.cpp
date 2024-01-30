#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#define SIZE 26

using namespace std;

struct Trie {
    bool finish; // 끝나는 지점 확인(문자의 끝 node만 true로 체크)
    Trie* node[SIZE]; // 알파벳 개수가 26개이므로

    Trie() { // 할당 및 생성
        finish = false;
        fill(node, node + SIZE, nullptr);
    }

    void insert(string &str, int index) {  // string 문자를 삽입하기 위한 과정
        if (str.size() <= index) {
            finish = true;
            return;
        }
        int current = str[index] - 'a'; // 현재 문자를 가져옴
        if (node[current] == nullptr) node[current] = new Trie();
        // 연결된 노드가 존재하지 않을 때 노드 생성 후 그다음 문자열 탐색 -> 기존 다른 문자열에 의해 노드 존재시 PASS
        node[current]->insert(str, index + 1);
        // 다음 문자열로 넘어가는 과정
    }
    bool find(string &str, int index) { // 문자열 마지막까지 탐색했을 경우
        if (str.size() <= index) return finish;

        int current = str[index] - 'a';
        if (node[current] == nullptr) return false; // 노드 생성되지 않았을 때
        return node[current]->find(str, index + 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    Trie* root = new Trie();
    string str;

    for (int i = 0; i < N; i++) {
        cin >> str;
        root->insert(str, 0);
    }

    int result = 0;
    while (M--) {
        cin >> str;
        if (root->find(str, 0)) result += 1;
    }
    cout << result << "\n";
    return 0;
}