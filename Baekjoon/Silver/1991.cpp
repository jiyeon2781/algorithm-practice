#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    char node; // 현재 노드
    Node* left; // 왼쪽 자식 노드
    Node* right; // 오른쪽 자식 노드

    Node(char a) {
        node = a;
        left = nullptr;
        right = nullptr;
    }

    void PreOrder() { // 전위 순회 (루트 -> 왼쪽 -> 오른쪽)
        cout << node;
        if (left != nullptr) left->PreOrder();
        if (right != nullptr) right->PreOrder();
    }
    
    void InOrder() { // 중위 순회 (왼쪽 -> 루트 -> 오른쪽)
        if (left != nullptr) left->InOrder();
        cout << node;
        if (right != nullptr) right->InOrder();
    }
    
    void PostOrder() { // 후위 순회 (왼쪽 -> 오른쪽 -> 루트)
        if (left != nullptr) left->PostOrder();
        if (right != nullptr) right->PostOrder();
        cout << node;
    }
};

void SearchNode(Node* node, char a);

Node* current;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    char node, left, right;
    Node* root = new Node('A');

    while (N--) {
        cin >> node >> left >> right;
        SearchNode(root, node);
        if (current == nullptr) continue;
        if (left != '.') current->left = new Node(left); // 왼쪽 노드 생성
        if (right != '.') current->right = new Node(right); // 오른쪽 노드 생성

    }
    root->PreOrder();
    cout << "\n";
    root->InOrder();
    cout << "\n";
    root->PostOrder();
    return 0;
}

void SearchNode(Node* node, char a) {
    if (node == nullptr) return; // 노드가 비어있을 때
    if (node->node == a) { // 노드를 찾았다면
        current = node; // 현재 노드에 저장
        return;
    }
    if (node->left != nullptr) SearchNode(node->left, a);
    if (node->right != nullptr) SearchNode(node->right, a);
}
