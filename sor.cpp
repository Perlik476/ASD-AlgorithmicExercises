#include <iostream>

using namespace std;

using ull = unsigned long long;

#define N 1000
#define MOD 2000000000

int tab[N];
unsigned long long L[N][N];
unsigned long long R[N][N];

bool L_has_value[N][N];
bool R_has_value[N][N];

ull calculateR(int i, int j);

ull add(ull a, ull b) {
    return (a + b) % MOD;
}

ull calculateL(int i, int j) {
    //cout << "L: " << i << ", " << j << "\n";
    if (L_has_value[i][j]) {
        return L[i][j];
    }
    else if (i == j) {
        L[i][j] = 1;
        L_has_value[i][j] = true;
        return L[i][j];
    }
    // else if (i == j + 1) {
    //     L[i][j] = 1;
    //     L_has_value[i][j] = true;
    //     return L[i][j];
    // }
    L[i][j] = add((tab[i] < tab[i + 1] ? calculateL(i + 1, j) : 0),
        (tab[i] < tab[j] ? calculateR(i + 1, j) : 0));
    L_has_value[i][j] = true;
    return L[i][j];
}

ull calculateR(int i, int j)  {
    //cout << "R: " << i << ", " << j << "\n";
    if (R_has_value[i][j]) {
        return R[i][j];
    }
    else if (i == j) {
        R[i][j] = 1;
        R_has_value[i][j] = true;
        return R[i][j];
    }
    // else if (i == j + 1) {
    //     R[i][j] = 1;
    //     R_has_value[i][j] = true;
    //     return R[i][j];
    // }
    R[i][j] = add((tab[i] < tab[j] ? calculateL(i, j - 1) : 0),
        (tab[j - 1] < tab[j] ? calculateR(i, j - 1) : 0));
    R_has_value[i][j] = true;
    return R[i][j];
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    //L[i,j] = # permutacji, z których można otrzymać fragment A[i..j] przy założeniu, że ostatni element wyjściowej permutacji to A[i].
    //R[i,j] = # permutacji, z których można otrzymać fragment A[i..j] przy założeniu, że ostatni element wyjściowej permutacji to A[j].


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L_has_value[i][j] = 0;
            R_has_value[i][j] = 0;
            L[i][j] = 0;
            R[i][j] = 0;
        }
    }

    cout << add(calculateL(0, n - 1), calculateR(0, n - 1)) / 2;


}
