#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    long long d;
    cin >> d;

    set<long long> s;
    int cnt = 0;
    for (int i = 0; i <  n; i++) {
        int c;
        long long x;
        cin >> c >> x;

        if (c == 1) {
            s.insert(x);
            if (s.find(x + d) != s.end()) {
                cnt++;
            }
            if (s.find(x - d) != s.end()) {
                cnt++;
            }
        }
        if (c == -1) {
            s.erase(x);
            if (s.find(x + d) != s.end()) {
                cnt--;
            }
            if (s.find(x - d) != s.end()) {
                cnt--;
            }
        }

        cout << ((cnt > 0) ? "TAK" : "NIE") << "\n";
    }

    return 0;
}
