#include <bits/stdc++.h>
using namespace std;
#include "lib/graphs/lca/lca-binary-lifting.hpp"

int main() {
    mt19937 rng(8);
    for (int t = 0; t < 2000; t++) {
        int n = 1 + rng() % 30;
        vector<vector<int>> adj(n);
        vector<int> par(n, -1), dep(n, 0);
        for (int i = 1; i < n; i++) { int p = rng() % i; adj[i].push_back(p); adj[p].push_back(i); par[i] = p; }
        for (int i = 1; i < n; i++) { int d = 0, x = i; while (par[x] != -1) { x = par[x]; d++; } dep[i] = d; }
        LCA lca(adj); // root = 0
        auto naive = [&](int u, int v) {
            while (dep[u] > dep[v]) u = par[u];
            while (dep[v] > dep[u]) v = par[v];
            while (u != v) { u = par[u]; v = par[v]; }
            return u;
        };
        for (int q = 0; q < 25; q++) {
            int u = rng() % n, v = rng() % n, w = naive(u, v);
            assert(lca.lca(u, v) == w);
            assert(lca.dist(u, v) == dep[u] + dep[v] - 2 * dep[w]);
        }
        for (int q = 0; q < 25; q++) {
            int u = rng() % n, k = rng() % (n + 2);
            int x = u; for (int s = 0; s < k && x != -1; s++) x = par[x];
            assert(lca.kth_ancestor(u, k) == x);
        }
    }
    puts("lca binary-lifting: lca + dist + kth_ancestor vs naive, 2k arvores");
    return 0;
}
