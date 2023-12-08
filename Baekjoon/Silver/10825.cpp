#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Information {
    string name;
    int korean, english, math;
};

bool compare(Information a, Information b) {
    if (a.korean == b.korean) {
        if (a.english == b.english) {
            if (a.math == b.math) return a.name < b.name;
            return a.math > b.math;
        }
        return a.english < b.english;
    }
    return a.korean > b.korean;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<Information> students;
    string name;
    int math, english, korean;
    for (int i = 0; i < n; i++) {
        cin >> name >> korean >> english >> math;
        students.push_back({ name, korean, english, math });
    }

    sort(students.begin(), students.end(), compare);

    for (int i = 0; i < n; i++) {
        cout << students[i].name << "\n";
    }
    return 0;
}
