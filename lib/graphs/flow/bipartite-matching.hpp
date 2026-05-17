#pragma once
#include "dinic.hpp"
using namespace std;

/* Bipartite Matching via Dinic
 * Matching máximo em grafo bipartido.
 * Complexidade: O(E * sqrt(V))
 *
 * Vértices esquerda: [0, n), direita: [n, n+m).
 *
 * Campos públicos após match():
 *   size   = tamanho do matching máximo
 *   match_l[i] = vértice da direita matched com i (-1 se não matched)
 *   match_r[j] = vértice da esquerda matched com j (-1 se não matched)
 *
 * Métodos:
 *   add_edge(i, j) → aresta entre esquerda i e direita j
 *   match()        → executa o matching, retorna tamanho
 */

struct BipartiteMatching {
    int n, m;
    Dinic<int> g;
    int S, T;
    vector<int> match_l, match_r;
    int size = 0;

    BipartiteMatching(int n, int m)
        : n(n), m(m), g(n + m + 2),
          S(n + m), T(n + m + 1),
          match_l(n, -1), match_r(m, -1) {
        for (int i = 0; i < n; i++) g.add_edge(S, i, 1);
        for (int j = 0; j < m; j++) g.add_edge(n + j, T, 1);
    }

    void add_edge(int i, int j) {
        g.add_edge(i, n + j, 1);
    }

    int match() {
        size = g.flow(S, T);
        for (int i = 0; i < n; i++)
            for (auto& e : g.g[i])
                if (e.to != S && e.cap == 0) {
                    match_l[i] = e.to - n;
                    match_r[e.to - n] = i;
                }
        return size;
    }
};
