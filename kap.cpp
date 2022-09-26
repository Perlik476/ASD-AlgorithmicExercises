#include <iostream>
#include <bits/stdc++.h>

using namespace std;

using point = pair<long long, long long>;


vector<long long> dijkstra(const vector<vector<pair<int, long long>>> &edges, int source) {
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



long long distance(point a, point b) {
    return min(abs(a.first - b.first), abs(a.second - b.second));
}

void add_edge(vector<vector<pair<int, long long>>> &edges, int a, int b, long long d) {
    edges[a].push_back({b, d});
}


int main() {
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<pair<point, int>> points(n + 2);
    vector<pair<point, int>> points_x_sorted(n + 2);
    vector<pair<point, int>> points_y_sorted(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> points[i].first.first >> points[i].first.second;
        points[i].second = i;
        points_x_sorted[i] = points[i];
        points_y_sorted[i] = {{points_x_sorted[i].first.second, points_x_sorted[i].first.first}, i};
    }
    sort(points_x_sorted.begin() + 1, points_x_sorted.end() - 1);
    sort(points_y_sorted.begin() + 1, points_y_sorted.end() - 1);
    for (int i = 1; i <= n; i++) {
        points_y_sorted[i] = {{points_y_sorted[i].first.second, points_y_sorted[i].first.first}, points_y_sorted[i].second};
    }


    vector<vector<pair<int, long long>>> edges(n + 2);
    for (int i = 1; i <= n; i++) {
        if (i != 1) {
            add_edge(edges, points_x_sorted[i].second, points_x_sorted[i - 1].second,
                     distance(points_x_sorted[i].first, points_x_sorted[i - 1].first));
            add_edge(edges, points_y_sorted[i].second, points_y_sorted[i - 1].second,
                     distance(points_y_sorted[i].first, points_y_sorted[i - 1].first));
        }
        if (i != n) {
            add_edge(edges, points_x_sorted[i].second, points_x_sorted[i + 1].second,
                     distance(points_x_sorted[i].first, points_x_sorted[i + 1].first));
            add_edge(edges, points_y_sorted[i].second, points_y_sorted[i + 1].second,
                     distance(points_y_sorted[i].first, points_y_sorted[i + 1].first));
        }

    }

    auto result = dijkstra(edges, 1);

    cout << result[n];

    return 0;
}
