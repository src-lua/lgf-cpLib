#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Pontos de Articulação — Tarjan
 * Complexidade: O(V + E)
 * Grafo não-direcionado.
 *
 * Sua remoção aumenta o número de componentes conexas.
 *
 * Campos públicos após build():
 *   is_ap[v] = true se v é ponto de articulação
 *   get()    = lista dos pontos de articulação
 */

struct Articulations {
  int n;
  vector<vector<int>> g;
  vector<bool> is_ap;

  Articulations(int n) : n(n), g(n), is_ap(n, false) {}

  Articulations(const vector<vector<int>> &adj)
      : n(adj.size()), g(adj), is_ap(adj.size(), false) {
    build();
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void build() {
    vector<int> num(n, -1), low(n);
    int timer = 0;

    function<void(int, int)> dfs = [&](int v, int par) {
      low[v] = num[v] = timer++;
      int children = 0;
      for (int u : g[v]) {
        if (num[u] == -1) {
          children++;
          dfs(u, v);
          low[v] = min(low[v], low[u]);
          if (par == -1 && children > 1) is_ap[v] = true;
          if (par != -1 && low[u] >= num[v]) is_ap[v] = true;
        } else if (u != par) {
          low[v] = min(low[v], num[u]);
        }
      }
    };

    for (int i = 0; i < n; i++)
      if (num[i] == -1) dfs(i, -1);
  }

  // Lista dos pontos de articulação.
  vector<int> get() const {
    vector<int> res;
    for (int i = 0; i < n; i++)
      if (is_ap[i]) res.push_back(i);
    return res;
  }
};
