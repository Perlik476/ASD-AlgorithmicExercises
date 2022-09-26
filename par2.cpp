#include <iostream>
#include <bits/stdc++.h>

using namespace std;

pair<int, int> bfs(const vector<vector<int>> &edges, int start) {
    vector<bool> visited(edges.size() + 1, false);
    queue<pair<int, int>> q;
    q.push({start, 0});
    pair<int, int> result = {start, 0};
    while (!q.empty()) {
        auto [v, d] = q.front();
        q.pop();
        visited[v] = true;
        if (d > result.second) {
            result = {v, d};
        }
        for (auto u : edges[v]) {
            if (!visited[u]) {
                q.push({u, d + 1});
            }
        }
    }
    return result;
}

void dfs(const vector<vector<int>> &edges, int current, vector<vector<int>> &jump_pointers, vector<bool> &visited) {
    if (!visited[current]) {
        visited[current] = true;
        for (auto v : edges[current]) {
            //cout << "v: " << v << ", " << current << "\n";
            if (!visited[v]) {
                jump_pointers[v][0] = current;
                dfs(edges, v, jump_pointers, visited);
            }
        }
    }
}

void dfs(const vector<vector<int>> &edges, int start, vector<vector<int>> &jump_pointers) {
    vector<bool> visited(edges.size() + 1, false);
    dfs(edges, start, jump_pointers, visited);
}

void set_jump_pointers(vector<vector<int>> &jump_pointers, const int n, const int N) {
    for (int i = 1; i < N; i++) {
        for (int v = 1; v <= n; v++) {
            jump_pointers[v][i] = jump_pointers[jump_pointers[v][i - 1]][i - 1];
        }
    }
}

int get_vertex_of_dist(int v, int d, const vector<vector<int>> &jump_pointers, int n, int N) {
    static int power_static = 1;
//    cout << "xd";
    while (2 * power_static <= n) {
        power_static *= 2;
//        cout << "power: " << power_static;
    }
    int power = power_static;
    for (int i = N - 1; i >= 0; i--) {
//        cout << "i: " << i << "\n";
        if (d >= power) {
            v = jump_pointers[v][i];
            d -= power;
        }
        power /= 2;
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    int N = 0;
    int n_temp = n;
    while (n_temp) {
        N++;
        n_temp /= 2;
    }
    //cout << N << "\n";

    vector<vector<int>> edges(n + 1);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (a != -1) {
            edges[i].push_back(a);
            edges[a].push_back(i);
        }
        if (b != -1) {
            edges[i].push_back(b);
            edges[b].push_back(i);
        }
    }

    auto [v, _] = bfs(edges, 1);
    auto [u, diam] = bfs(edges, v);

    //cout << u << ", " << v << ", " << diam << "\n";

    vector<vector<int>> jump_pointers_u(n + 1);
    vector<vector<int>> jump_pointers_v(n + 1);
    for (int i = 0; i <= n; i++) {
        jump_pointers_u[i].resize(N, 0);
        jump_pointers_v[i].resize(N, 0);
    }

    dfs(edges, u, jump_pointers_u);
    dfs(edges, v, jump_pointers_v);

    set_jump_pointers(jump_pointers_u, n, N);
    set_jump_pointers(jump_pointers_v, n, N);

//    cout << u << "\n";
//    for (auto vec : jump_pointers_u) {
//        for (int i = 0; i < N; i++) {
//            cout << vec[i] << ", ";
//        }
//        cout << "\n";
//    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int a, d;
        cin >> a >> d;
        if (d == 0) {
            cout << a << "\n";
        }
        else {
            int x = get_vertex_of_dist(a, d, jump_pointers_u, n, N);
            int y = get_vertex_of_dist(a, d, jump_pointers_v, n, N);

            cout << (x == 0 && y == 0 ? -1 : (x == 0) ? y : x) << "\n";
        }
    }



    return 0;
}
