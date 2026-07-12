#pragma once
#include <bits/stdc++.h>
using namespace std;

/* LCA (Lowest Common Ancestor) via Binary Lifting
 * Ancestral comum mais próximo de dois vértices da árvore.
 * Complexidade: O(N log N) no build, O(log N) por query.
 * Memória: O(N log N)
 * Requisitos:
 * - Grafo deve ser uma árvore (conexo e acíclico).
 * Métodos:
 * - lca(u, v): Retorna o LCA de u e v.
 * - dist(u, v): Retorna a distância entre u e v.
 * - is_ancestor(u, v): Verifica se u é ancestral de v.
 * - parent(u): Retorna o pai de u (up[u][0]).
 * - kth_ancestor(u, k): k-ésimo ancestral; -1 se não existe.
 */

struct LCA {
  int N, LOG;
  vector<int> d;
  vector<vector<int>> up;

  LCA(const vector<vector<int>> &adj, int root = 0)
      : N(adj.size()), LOG(__lg(N) + 1), d(N),
        up(N, vector<int>(LOG + 1, -1)) {

    auto dfs = [&](auto self, int u, int p, int dep) -> void {
      d[u] = dep;
      up[u][0] = (p == -1) ? u : p;
      for (int j = 1; j <= LOG; j++)
        up[u][j] = up[up[u][j - 1]][j - 1];
      for (int v : adj[u]) {
        if (v == p) continue;
        self(self, v, u, dep + 1);
      }
    };

    dfs(dfs, root, -1, 0);
  }

  int parent(int u) { return up[u][0] == u ? -1 : up[u][0]; }

  int kth_ancestor(int u, int k) {
    if (k > d[u]) return -1;
    for (int j = 0; j <= LOG; j++)
      if ((k >> j) & 1) u = up[u][j];
    return u;
  }

  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int diff = d[u] - d[v];
    for (int j = 0; j <= LOG; j++)
      if ((diff >> j) & 1) u = up[u][j];
    if (u == v) return u;
    for (int j = LOG; j >= 0; j--)
      if (up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
      }
    return up[u][0];
  }

  int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
  }

  bool is_ancestor(int u, int v) { return lca(u, v) == u; }
};
