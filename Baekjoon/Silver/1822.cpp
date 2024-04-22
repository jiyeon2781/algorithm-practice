#include <iostream>
#include <set>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int countA, countB;
	cin >> countA >> countB;

	set<long long> nums;
	long long num;

	while (countA--) {
		cin >> num;
		nums.insert(num);
	}

	while (countB--) {
		cin >> num;
		auto it = nums.find(num);
		if (it == nums.end()) continue;
		nums.erase(it);
	}

	cout << nums.size() << "\n";
	for (long long element : nums) {
		cout << element << ' ';
	}

	return 0;
}