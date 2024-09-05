#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long Mod = 1000000007; // overflow를 막기 위한 mod 연산 시 사용되는 수
const long long PrimePower = 101; // 소수 거듭 제곱 -> 왜 소수가 작으면 틀렸다고 뜰까..?

void RabinKarp(string text, string pattern, int N, int M);
// 문자열, 패턴, 문자열의 크기, 패턴의 크기
vector<int> result;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string T, P;

    getline(cin, T);
    getline(cin, P);

    int N = T.size(), M = P.size();
    RabinKarp(T, P, N, M);

    cout << result.size() << "\n";
    for (auto num : result)
        cout << num << ' ';
}

void RabinKarp(string text, string pattern, int N, int M) {
    long long patternHash = 0, textHash = 0;
    long long head = 1;

    // 패턴과 문자열의 첫번째 해시값 부분 계산 
    // textHash = textHash[0] + textHash[1] + ... + textHash[M - 1]
    // patternHash = patternHash[0] + patternHash[1] + ... + patternHash[M -1]
    for (int i = 0; i < M; i++) {
        textHash = (PrimePower * textHash + text[i]) % Mod;
        patternHash = (PrimePower * patternHash + pattern[i]) % Mod;

        if (i != M - 1) // PrimePower^(M - 1) = hash
            head = (head * PrimePower) % Mod;
    }

    // slide pattern
    for (int i = 0; i <= N - M; i++) {
        // 패턴 해시값들의 합과 문자열 해시값들의 합이 동일하다면
        // 원래는 다른 문자열일 수 있으므로 비교해주어야함 -> 비교하면 해당 문제에서는 시간 초과
        // 다른 방법이 있을까..?
        if (patternHash == textHash) result.push_back(i + 1);

        // 다음 부분 문자열의 문자열 해시값
        if (i == N - M) continue;
        textHash = (PrimePower * (textHash - text[i] * head) + text[i + M]) % Mod;

        if (textHash < 0) textHash += Mod; // 음수일 경우 양수로 변경
    }
}