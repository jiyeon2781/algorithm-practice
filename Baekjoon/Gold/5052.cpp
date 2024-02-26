#include <iostream>
#include <algorithm>
#include <queue>

#define NUM_SIZE 10

using namespace std;

bool isPrefix;
bool isNotNull;

struct Trie {
    bool finish;
    Trie* node[NUM_SIZE];

    Trie() {
        finish = false;
        fill(node, node + NUM_SIZE, nullptr);
    }

    void insert(string& str, int index) {
        if (str.size() <= index) {
            if (isNotNull) isPrefix = true;
            finish = true;
            return;
        }

        if (str.size() > index && finish) {
            isPrefix = true;
            return;
        }

        int current = str[index] - '0';
        if (node[current] == nullptr) {
            node[current] = new Trie();
            isNotNull = false;
        }
        node[current]->insert(str, index + 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc, N;
    cin >> tc;

    string number;
    while (tc--) {
        Trie* root = new Trie();

        cin >> N;
        isPrefix = false;
        while (N--) {
            cin >> number;
            isNotNull = true;
            root->insert(number, 0);
        }
        if (isPrefix) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
