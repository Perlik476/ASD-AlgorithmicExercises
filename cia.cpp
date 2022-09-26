#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    set<int> s;
    s.insert(0);
    s.insert(n);

    multiset<int, greater<>> d;
    d.insert(n);

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (s.find(x) == s.end()) {
            auto it = s.upper_bound(x);
            int upper = *it;
            it--;
            int lower = *it;

//            cout << "x: " << x << " lower: " << lower << " upper: " << upper << "\n";

            s.insert(x);

            auto it2 = d.find(upper - lower);
            d.erase(it2);
            d.insert(upper - x);
            d.insert(x - lower);
        }

        cout << *d.begin() << "\n";
    }

    return 0;
}
