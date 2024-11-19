#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

const int Mod = 60;

int ConvertSeconds(string str);

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands) {
    string answer = "";
    
    int videoLen, curPos, opStart, opEnd;
    videoLen = ConvertSeconds(video_len);
    curPos = ConvertSeconds(pos);
    opStart = ConvertSeconds(op_start);
    opEnd = ConvertSeconds(op_end);
    
    for (string command : commands) {
        if (curPos >= opStart && curPos <= opEnd) curPos = opEnd;
        if (command == "next") {
            curPos = curPos + 10 >= videoLen ? videoLen : curPos + 10;
        }
        else if (command == "prev") {
            curPos = curPos - 10 < 0 ? 0 : curPos - 10;
        }
    }
    
    if (curPos >= opStart && curPos <= opEnd) curPos = opEnd;
    
    string min, sec;
    min = curPos / 60 < 10 ? '0' + to_string(curPos / 60) : to_string(curPos / 60);
    sec = curPos % 60 < 10 ? '0' + to_string(curPos % 60) : to_string(curPos % 60);
    answer = min + ':' + sec;
    
    return answer;
}

int ConvertSeconds(string str) {
    stringstream ss(str);
    string buf;
    
    vector<int> result;
    while(getline(ss, buf, ':')) result.push_back(stoi(buf));
    
    return result[0] * 60 + result[1];
}