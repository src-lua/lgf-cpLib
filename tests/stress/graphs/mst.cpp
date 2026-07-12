#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/graphs/mst.hpp"

int main() {
    mt19937 rng(7);
    for (int t = 0; t < 2000; t++) {
        int n = 2 + rng() % 8;
        vector<tuple<int,int,int>> es;
        vector<vector<int>> w(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (rng() % 2) {
            int c = 1 + rng() % 20; es.push_back({c, i, j}); w[i][j] = w[j][i] = min(w[i][j], c);
        }
        auto [cost, used] = mst(n, es);
        // Prim
        vector<int> d(n, 1e9), vis(n, 0); d[0] = 0; ll pc = 0; int cnt = 0;
        for (int it = 0; it < n; it++) {
            int v = -1; for (int i = 0; i < n; i++) if (!vis[i] && (v < 0 || d[i] < d[v])) v = i;
            if (d[v] >= (int)1e9) break;
            vis[v] = 1; pc += d[v]; cnt++;
            for (int j = 0; j < n; j++) if (!vis[j]) d[j] = min(d[j], w[v][j]);
        }
        if (cnt == n) { assert(cost == pc); assert((int)used.size() == n - 1); }
        else assert((int)used.size() < n - 1); // desconexo
    }
    puts("mst: Kruskal vs Prim, 2k grafos (incl. desconexos)");
    return 0;
}
