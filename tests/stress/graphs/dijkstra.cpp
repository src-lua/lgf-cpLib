#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/graphs/dijkstra.hpp"

int main() {
    mt19937 rng(9);
    const ll INF = numeric_limits<ll>::max();
    for (int t = 0; t < 1000; t++) {
        int n = 1 + rng() % 12;
        vector<vector<pair<int,ll>>> adj(n);
        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        int E = rng() % (n * n + 1);
        for (int e = 0; e < E; e++) {
            int u = rng() % n, v = rng() % n; ll w = rng() % 20;
            adj[u].push_back({v, w}); d[u][v] = min(d[u][v], w);
        }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s = rng() % n;
        auto dist = dijkstra<ll>(adj, s);
        for (int v = 0; v < n; v++) assert(dist[v] == d[s][v]);
    }
    puts("dijkstra: vs floyd-warshall, 1k grafos");
    return 0;
}
