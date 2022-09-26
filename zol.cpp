#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    set<int> s;
    for (int i = 1; i <= n; i++) {
        s.insert(i);
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;

        auto it = s.erase(s.find(k));

        if (it != s.begin()) {
            it--;
            cout << *it << " ";
            it++;
        }
        else {
            cout << -1 << " ";
        }
        if (it != s.end()) {
            cout << *it << "\n";
        }
        else {
            cout << -1 << "\n";
        }

    }

    return 0;
}
