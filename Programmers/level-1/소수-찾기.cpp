#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    vector<bool> isNotPrime(n);
    isNotPrime[0] = true;
    isNotPrime[1] = true;
    
    for (int i = 2; i <= n; i++) {
        if (isNotPrime[i]) continue;
        for (int j = i + i; j <= n; j += i) {
            if (!isNotPrime[j]) isNotPrime[j] = true;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        if (!isNotPrime[i]) answer += 1;
    }
    
    return answer;
}