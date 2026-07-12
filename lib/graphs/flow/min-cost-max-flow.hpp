#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Min-Cost Max-Flow (SPFA/Bellman-Ford based)
 * Complexidade: O(VE·flow) no pior caso.
 * Memória: O(V + E)
 *
 * Métodos:
 * add_edge(u, v, cap, cost) → aresta u→v com cap e custo
 * add_edge(u, v, cap, rcap, cost) → capacidade reversa rcap
 * flow(s, t) → {fluxo máximo, custo mínimo} de s a t
 * flow(s, t, limit) → limita o fluxo total a limit
 *
 * Observações:
 * - Suporta custos negativos (usa SPFA em vez de Dijkstra).
 * - Sem custos negativos, Dijkstra+potenciais dá O(E log V)/aug.
 * - Retorna o menor custo para o fluxo máximo obtido.
 */

template <typename Cap, typename Cost>
struct MCMF {
  struct Edge {
    int to, rev;
    Cap cap;
    Cost cost;
  };

  int N;
  vector<vector<Edge>> g;

  MCMF(int n) : N(n), g(n) {}

  void add_edge(int u, int v, Cap cap, Cost cost, Cap rcap = 0) {
    g[u].push_back({v, (int)g[v].size(), cap, cost});
    g[v].push_back({u, (int)g[u].size() - 1, rcap, -cost});
  }

  pair<Cap, Cost> flow(int s, int t,
                       Cap limit = numeric_limits<Cap>::max()) {
    Cap total_flow = 0;
    Cost total_cost = 0;

    while (limit > 0) {
      vector<Cost> dist(N, numeric_limits<Cost>::max());
      vector<bool> in_queue(N, false);
      vector<int> prev_node(N, -1), prev_edge(N, -1);

      dist[s] = 0;
      queue<int> q;
      q.push(s);
      in_queue[s] = true;

      while (!q.empty()) {
        int v = q.front();
        q.pop();
        in_queue[v] = false;
        for (int i = 0; i < (int)g[v].size(); i++) {
          auto &e = g[v][i];
          if (e.cap > 0 && dist[v] + e.cost < dist[e.to]) {
            dist[e.to] = dist[v] + e.cost;
            prev_node[e.to] = v;
            prev_edge[e.to] = i;
            if (!in_queue[e.to]) {
              in_queue[e.to] = true;
              q.push(e.to);
            }
          }
        }
      }

      if (dist[t] == numeric_limits<Cost>::max()) break;

      Cap pushed = limit;
      for (int v = t; v != s; v = prev_node[v])
        pushed = min(pushed, g[prev_node[v]][prev_edge[v]].cap);

      for (int v = t; v != s; v = prev_node[v]) {
        auto &e = g[prev_node[v]][prev_edge[v]];
        e.cap -= pushed;
        g[v][e.rev].cap += pushed;
      }

      total_flow += pushed;
      total_cost += pushed * dist[t];
      limit -= pushed;
    }

    return {total_flow, total_cost};
  }
};
