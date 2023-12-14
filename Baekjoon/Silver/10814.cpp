#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Information {
    string name;
    int age;
    int number;
};

bool compare(Information mem1, Information mem2) {
    if (mem1.age == mem2.age)
        return mem1.number < mem2.number;
    return mem1.age < mem2.age;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, age;
    cin >> N;
    string name;
    vector<Information> members;

    for (int i = 0; i < N; i++) {
        cin >> age >> name;
        members.push_back({ name, age, i });
    }

    sort(members.begin(), members.end(), compare);

    for (int i = 0; i < N; i++) {
        cout << members[i].age << ' ' << members[i].name << "\n";
    }
    return 0;
}
