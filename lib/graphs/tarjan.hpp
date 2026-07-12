#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Tarjan SCC (Strongly Connected Components)
 * Complexidade: O(V + E)
 *
 * Campos públicos após build():
 *   comp[v]  = SCC de v, em ordem topológica reversa
 *   scc[i]   = lista de vértices do i-ésimo SCC
 *   dag      = grafo condensado sem arestas duplicadas
 *   n_scc    = número de SCCs
 *
 * Se há aresta SCC a → SCC b, então comp[a] > comp[b].
 * Para ordem topológica direta, percorra n_scc-1 ... 0.
 */

struct Tarjan {
  int n, n_scc = 0;
  vector<vector<int>> g, scc, dag;
  vector<int> comp;

  Tarjan(int n) : n(n), g(n), comp(n, -1) {}

  Tarjan(const vector<vector<int>> &adj)
      : n(adj.size()), g(adj), comp(adj.size(), -1) {
    build();
  }

  void add_edge(int u, int v) { g[u].push_back(v); }

  void build() {
    vector<int> low(n), num(n, -1), stk;
    vector<bool> on_stk(n, false);
    int timer = 0;

    function<void(int)> dfs = [&](int v) {
      low[v] = num[v] = timer++;
      stk.push_back(v);
      on_stk[v] = true;
      for (int u : g[v]) {
        if (num[u] == -1) {
          dfs(u);
          low[v] = min(low[v], low[u]);
        } else if (on_stk[u]) low[v] = min(low[v], num[u]);
      }
      if (low[v] == num[v]) {
        scc.push_back({});
        while (true) {
          int u = stk.back();
          stk.pop_back();
          on_stk[u] = false;
          comp[u] = n_scc;
          scc.back().push_back(u);
          if (u == v) break;
        }
        n_scc++;
      }
    };

    for (int i = 0; i < n; i++)
      if (num[i] == -1) dfs(i);

    dag.assign(n_scc, {});
    for (int u = 0; u < n; u++)
      for (int v : g[u])
        if (comp[u] != comp[v]) dag[comp[u]].push_back(comp[v]);

    for (auto &adj : dag) {
      sort(adj.begin(), adj.end());
      adj.erase(unique(adj.begin(), adj.end()), adj.end());
    }
  }
};
