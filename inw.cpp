#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int current_max = 0;
    int number = 0;
    for (int i = 1; i <= n; i++) {
        current_max = max(current_max, a[i]);
        if (i == current_max) {
            number++;
        }
    }

    cout << number << "\n";

    int j = 0;
    current_max = 0;
    for (int i = 1; i <= n; i++) {
        current_max = max(current_max, a[i]);
        if (i == current_max) {
            cout << i - j << " ";
            sort(a.begin() + j + 1, a.begin() + i + 1);
            for (int k = j + 1; k <= i; k++) {
                cout << a[k] << " ";
            }
            cout << "\n";
            j = i;
        }
    }

    return 0;
}
