#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void Init();
void Start();
void Rotation(char section, bool isClockwise);
void RotationUp();
void RotationDown();
void RotationFront();
void RotationBack();
void RotationLeft();
void RotationRight();
void RotationFace(int section);
void Print();

enum { U, D, F, B, L, R };
// 0 : U, 1 : D, 2 : F, 3 : B, 4 : L , 5: R

const int MaxSize = 3;
const int MaxSection = 6;


char cube[MaxSection][MaxSize][MaxSize];

string sections = "wyrogb";
// white, yellow, red, orage, green, blue

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;

    while (tc--) {
        Init();
        Start();
    }

    return 0;
}

void Init() {
    for (int i = 0; i < MaxSection; i++) {
        for (int j = 0; j < MaxSize; j++) {
            for (int k = 0; k < MaxSize; k++) {
                cube[i][j][k] = sections[i];
            }
        }
    }
}

void Start() {
    int num;
    string dir;

    cin >> num;
    while (num--) {
        cin >> dir;
        Rotation(dir[0], dir[1] == '+');
    }

    Print();
}

void Print() {
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            cout << cube[0][i][j];
        }
        cout << "\n";
    }
}

void Rotation(char section, bool isClockwise) {
    int cnt = isClockwise ? 1 : 3;
    while (cnt--) {
        switch (section) {
        case 'U':
            RotationUp();
            break;
        case 'D':
            RotationDown();
            break;
        case 'F':
            RotationFront();
            break;
        case 'B':
            RotationBack();
            break;
        case 'L':
            RotationLeft();
            break;
        case 'R':
            RotationRight();
            break;
        }
    }
}

// F -> L -> B -> R
void RotationUp() {
    RotationFace(U);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[F][0][i];
    for (int i = 0; i < MaxSize; i++) 
        cube[F][0][i] = cube[R][0][i];
    for (int i = 0; i < MaxSize; i++)
        cube[R][0][i] = cube[B][0][i];
    for (int i = 0; i < MaxSize; i++)
        cube[B][0][i] = cube[L][0][i];
    for (int i = 0; i < MaxSize; i++)
        cube[L][0][i] = temp[i];
}

// F -> R -> B -> L
void RotationDown() {
    RotationFace(D);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[F][2][i];
    for (int i = 0; i < MaxSize; i++)
        cube[F][2][i] = cube[L][2][i];
    for (int i = 0; i < MaxSize; i++)
        cube[L][2][i] = cube[B][2][i];
    for (int i = 0; i < MaxSize; i++)
        cube[B][2][i] = cube[R][2][i];
    for (int i = 0; i < MaxSize; i++)
        cube[R][2][i] = temp[i];
}

// U -> R -> D -> L
void RotationFront() {
    RotationFace(F);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[U][2][i];
    for (int i = 0; i < MaxSize; i++)
        cube[U][2][i] = cube[L][MaxSize - i - 1][2];
    for (int i = 0; i < MaxSize; i++)
        cube[L][i][2] = cube[D][0][i];
    for (int i = 0; i < MaxSize; i++)
        cube[D][0][i] = cube[R][MaxSize - i - 1][0];
    for (int i = 0; i < MaxSize; i++)
        cube[R][i][0] = temp[i];
}

// U -> L -> D -> R
void RotationBack() {
    RotationFace(B);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[U][0][i];
    for (int i = 0; i < MaxSize; i++)
        cube[U][0][i] = cube[R][i][2];
    for (int i = 0; i < MaxSize; i++)
        cube[R][i][2] = cube[D][2][MaxSize - i - 1];
    for (int i = 0; i < MaxSize; i++)
        cube[D][2][i] = cube[L][i][0];
    for (int i = 0; i < MaxSize; i++)
        cube[L][i][0] = temp[MaxSize - i - 1];
}

// U -> F -> D -> B
void RotationLeft() {
    RotationFace(L);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[U][i][0];
    for (int i = 0; i < MaxSize; i++)
        cube[U][i][0] = cube[B][MaxSize - i - 1][2];
    for (int i = 0; i < MaxSize; i++)
        cube[B][i][2] = cube[D][MaxSize - i - 1][0];
    for (int i = 0; i < MaxSize; i++)
        cube[D][i][0] = cube[F][i][0];
    for (int i = 0; i < MaxSize; i++)
        cube[F][i][0] = temp[i];
}

// U -> B -> D -> F
void RotationRight() {
    RotationFace(R);

    char temp[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        temp[i] = cube[U][i][2];
    for (int i = 0; i < MaxSize; i++)
        cube[U][i][2] = cube[F][i][2];
    for (int i = 0; i < MaxSize; i++)
        cube[F][i][2] = cube[D][i][2];
    for (int i = 0; i < MaxSize; i++)
        cube[D][i][2] = cube[B][MaxSize - i - 1][0];
    for (int i = 0; i < MaxSize; i++)
        cube[B][i][0] = temp[MaxSize - i - 1];
}

void RotationFace(int section) {
    char temp[MaxSize][MaxSize];

    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            temp[i][j] = cube[section][i][j];
        }
    }

    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            cube[section][i][j] = temp[MaxSize - j - 1][i];
        }
    }
}