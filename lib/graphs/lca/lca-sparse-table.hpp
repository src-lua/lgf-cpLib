#pragma once
#include <bits/stdc++.h>
#include "../../data-structures/sparse-table/sparse-table.hpp"
using namespace std;

/* LCA (Lowest Common Ancestor) via RMQ
 * Ancestral comum mais próximo de dois vértices da árvore.
 * Complexidade: O(N log N) no build, O(1) por query.
 * Memória: O(N log N)
 * Requisitos:
 * - Grafo deve ser uma árvore (conexo e acíclico).
 * Métodos:
 * - lca(u, v): Retorna o LCA de u e v.
 * - dist(u, v): Retorna a distância entre u e v.
 * - is_ancestor(u, v): Verifica se u é ancestral de v.
 * - parent(u): Retorna o pai de u.
 */

struct LCANode {
  int dep, id;
  LCANode(int d = 1e9, int pos = -1) : dep(d), id(pos) {}

  static LCANode merge(const LCANode &l, const LCANode &r) {
    return l.dep < r.dep ? l : r;
  }
};

struct LCA {
  int N;
  vector<int> first, tour, d, p;
  SparseTable<LCANode> st;

  LCA(const vector<vector<int>> &adj, int root = 0)
      : N(adj.size()), first(N), d(N), p(N, -1),
        st(vector<LCANode>()) {

    tour.reserve(2 * N);
    vector<LCANode> nodes;
    nodes.reserve(2 * N);

    auto dfs = [&](auto self, int u, int par, int dep) -> void {
      p[u] = par;
      d[u] = dep;
      first[u] = tour.size();
      tour.push_back(u);
      nodes.push_back({dep, (int)tour.size() - 1});
      for (int v : adj[u]) {
        if (v == par) continue;
        self(self, v, u, dep + 1);
        tour.push_back(u);
        nodes.push_back({dep, (int)tour.size() - 1});
      }
    };

    dfs(dfs, root, -1, 0);
    st = SparseTable<LCANode>(nodes);
  }

  int parent(int u) { return p[u]; }

  int lca(int u, int v) {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);
    return tour[st.query(l, r).id];
  }

  int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
  }

  bool is_ancestor(int u, int v) { return lca(u, v) == u; }
};
