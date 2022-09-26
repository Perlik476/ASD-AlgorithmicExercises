#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    long long d;
    cin >> d;

    multiset<long long> s;
    long long a = 0;
    long long b = 0;
    int cnt = 0;
    for (int i = 0; i <  n; i++) {
        long long x;
        cin >> x;

        auto it = s.insert(x);
        auto it_find = s.find(x + d);
        if (it_find != s.end() && it_find != it) {
            cnt++;
            b = x;
            a = x + d;
        }
        it_find = s.find(x - d);
        if (it_find != s.end() && it_find != it) {
            cnt++;
            a = x;
            b = x - d;
        }
    }

    if (cnt == 0) {
        cout << "NIE\n";
    }
    else {
        cout << a << " " << b << "\n";
    }

    return 0;
}
