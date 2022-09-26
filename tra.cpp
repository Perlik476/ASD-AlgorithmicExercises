#include <iostream>
#include <bits/stdc++.h>

using namespace std;

using edges_t = vector<vector<pair<int, int>>>;

long long dijkstra(const edges_t &edges, int source, int destination) {
    int n = (int) edges.size();
    vector<long long> dist(n, LONG_LONG_MAX);
    vector<bool> visited(n, false);
    dist[source] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    q.push({dist[source], source});

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
        if (visited[v]) {
            continue;
        }
        visited[v] = true;
        for (const auto &[u, w] : edges[v]) {
            if (d + w < dist[u]) {
                dist[u] = d + w;
                q.push({dist[u], u});
            }
        }
    }
    return dist[destination];
}


int main() {
    ios_base::sync_with_stdio(false);

    int n, m, a, b, d;
    cin >> n >> m >> a >> b >> d;

    edges_t edges(n + 1);
    edges_t edges2(n + 1);

    for (int i = 0; i < m; i++) {
        long long u, v, c1, p1, c2, p2;
        cin >> u >> v >> c1 >> p1 >> c2 >> p2;

        edges[u].push_back({v, c1});
        edges[v].push_back({u, c2});

        edges2[u].push_back({v, c1 + (d - 1) * p1});
        edges2[v].push_back({u, c2 + (d - 1) * p2});
    }

    long long d1 = dijkstra(edges, a, b) + dijkstra(edges, b, a);
    long long d2 = dijkstra(edges2, a, b) + dijkstra(edges2, b, a);
    long long res = min(d1, d2);

    cout << res << "\n";

    return 0;
}
