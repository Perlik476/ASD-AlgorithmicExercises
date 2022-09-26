#include <bits/stdc++.h>

using namespace std;

void activateBit(long long &bitmask, int j) {
    bitmask = bitmask | 1LL << j;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int number_of_players, number_of_matches;
    cin >> number_of_players >> number_of_matches;

    vector<long long> bitmasks(number_of_players);

    for (int match = 0; match < number_of_matches; match++) {
        for (int player = 0; player < number_of_players; player++) {
            int current_player;
            cin >> current_player;
            if (player >= number_of_players / 2) {
                activateBit(bitmasks[current_player - 1], match);
            }
        }
    }

    set<long long> s(bitmasks.begin(), bitmasks.end());

    cout << (s.size() == bitmasks.size() ? "TAK" : "NIE");

    return 0;
}
