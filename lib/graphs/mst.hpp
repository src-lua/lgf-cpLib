#pragma once
#include <bits/stdc++.h>
#include "../data-structures/dsu.hpp"
using namespace std;

/* MST — Árvore Geradora Mínima (Kruskal + DSU)
 * Complexidade: O(E log E). Grafo não-direcionado ponderado.
 *
 * mst(n, edges) → {custo total, arestas usadas}
 *   edges: vetor de {peso, u, v}.
 * Se desconexo, devolve a floresta mínima; used tem < n-1.
 *
 * Para árvore MÁXIMA, negue os pesos ou ordene decrescente.
 */

template <typename T>
pair<T, vector<pair<int, int>>>
mst(int n, vector<tuple<T, int, int>> edges) {
  sort(edges.begin(), edges.end());
  DSU dsu(n);
  T total = 0;
  vector<pair<int, int>> used;
  for (auto &[w, u, v] : edges)
    if (dsu.join(u, v)) {
      total += w;
      used.push_back({u, v});
    }
  return {total, used};
}
