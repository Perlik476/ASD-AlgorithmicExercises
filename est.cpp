#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v[i] = x;
    }

    sort(v.begin(), v.end());

    int result = 1;
    int current = 1;
    for (int i = 1; i < v.size(); i++) {
//        cout << v[i] << " " << v[i - 1] << "\n";
        if (v[i] - v[i - 1] <= 1) {
            current++;
            result = max(result, current);
        }
        else {
            current = 1;
        }
    }

    cout << result << "\n";


    return 0;
}
