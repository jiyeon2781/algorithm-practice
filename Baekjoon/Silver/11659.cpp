#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	vector<int> numbers;
	
	int N, M, num, start, end;
	cin >> N >> M;
	
	numbers.push_back(0);
	while (N--) {
		cin >> num;
		numbers.push_back(num);
	}

	for (int i = 1; i < numbers.size(); i++) {
		numbers[i] = numbers[i - 1] + numbers[i];
	}

	while (M--) {
		cin >> start >> end;
		cout << numbers[end] - numbers[start - 1] << "\n";
	}

	return 0;
}