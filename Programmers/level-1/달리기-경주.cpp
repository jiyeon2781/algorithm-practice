#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

int CurrentNumber(const vector<string>& players, const string& call);

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    unordered_map<string, int> rank;
    
    for (int i = 0; i < players.size(); i++) {
        rank[players[i]] = i;
    }
    
    for (string calling : callings) {
        int num = rank[calling];
        rank[calling] -= 1;
        rank[players[num - 1]] += 1;
        swap(players[num - 1], players[num]);
    }
    
    return players;
}
