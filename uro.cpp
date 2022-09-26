#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    const unsigned long long mod = 1e9;

    int n;
    cin >> n;

    vector<unsigned long long> dp(n + 1); // ile ok ciągów kończących się na i

    unsigned long long sum = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        unsigned long long last_dp = dp[x];
        dp[x] = (((sum- dp[x]) % mod) + 1) % mod;
        sum = ((((sum - last_dp) + sum) % mod) + 1) % mod;
    }

    cout << sum << "\n";

    return 0;
}
