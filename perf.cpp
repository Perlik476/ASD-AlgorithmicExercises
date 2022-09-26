#include <iostream>
#include <bits/stdc++.h>

using namespace std;

using edges_t = vector<vector<pair<int, long long>>>;


vector<long long> dijkstra(const edges_t &edges, int source) {
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
    return dist;
}


int main() {
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    edges_t edges(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[a].push_back({b, c});
        edges[b].push_back({a, c});
    }

    auto dist = dijkstra(edges, n);

    int v = 1;
    long long d = 0;
    std::cout << v << " ";
    int i = 0;
    while (v != n) {
        int next = -1;
        long long cur_w = 0;
        for (auto &[u, w] : edges[v]) {
            if (d + w + dist[u] == dist[1]) {
                if (next == -1 || u < next) {
                    next = u;
                    cur_w = w;
                }
            }
        }
        v = next;
        d += cur_w;
        std::cout << v << " ";
    }

    return 0;
}
