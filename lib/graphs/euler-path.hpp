#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Caminho/Circuito Euleriano — Hierholzer — O(V + E)
 *
 * Condições de existência:
 *   Grafo não-direcionado:
 *     - Circuito: todos os vértices têm grau par.
 *     - Caminho: exatamente dois têm grau ímpar.
 *   Grafo direcionado:
 *     - Circuito: in_degree[v] == out_degree[v] para todo v.
 *     - Caminho: um vértice com out-in=1, um com in-out=1.
 *
 * euler(adj, s) → caminho com E+1 vértices; vazio se inválido.
 * adj[u] = lista de {v, edge_id} para arestas u→v.
 * No não-direcionado, insira ambas as direções com o mesmo id.
 */

vector<int> euler(vector<vector<pair<int, int>>> &adj, int s) {
  int edges = 0;
  for (auto &v : adj) edges += v.size();
  // Para direcionado, remova a divisão por 2.
  edges /= 2;

  vector<bool> used(edges, false);
  vector<int> ptr(adj.size(), 0);
  vector<int> path, stk = {s};

  while (!stk.empty()) {
    int v = stk.back();
    bool found = false;
    while (ptr[v] < (int)adj[v].size()) {
      auto [u, eid] = adj[v][ptr[v]++];
      if (!used[eid]) {
        used[eid] = true;
        stk.push_back(u);
        found = true;
        break;
      }
    }
    if (!found) {
      path.push_back(v);
      stk.pop_back();
    }
  }

  if ((int)path.size() != edges + 1) return {};
  reverse(path.begin(), path.end());
  return path;
}
