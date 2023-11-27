#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    char ch;
    int index;
};

vector<int> solution(string s) {
    vector<int> answer;
    vector<Node> indexList;
    
    for (int index = 0; index < s.length(); index++) {
        char currentCh = s[index];
        auto it = find_if(indexList.begin(), indexList.end(), [currentCh] (Node& node)
                          { return node.ch == currentCh; } );
        if (it == indexList.end()){
            answer.push_back(-1);
            indexList.push_back({s[index], index});
            }
        else {
            answer.push_back(index - (it->index));
            it->index = index;
            }
            
        }
    
    return answer;
}