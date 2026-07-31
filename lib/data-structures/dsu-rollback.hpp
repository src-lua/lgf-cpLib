#pragma once
#include <bits/stdc++.h>
using namespace std;

/* DSU com Rollback (Union by Size, sem path compression)
 * Complexidade: O(log N) para find, join e rollback.
 * Memória: O(N + calls a join)
 * Métodos:
 * - find(i):    raiz do conjunto de i.
 * - join(i, j): une os conjuntos; sempre empilha no histórico
 *               (mesmo se já estavam unidos). Retorna true se uniu.
 * - rollback(): desfaz o último join (empilhado ou fantasma).
 * - same(i, j): verifica se i e j estão no mesmo conjunto.
 * - size(i):    tamanho do conjunto de i.
 *
 * IMPORTANTE: rollback() deve ser chamado uma vez por join(),
 * independente do retorno — join() sempre empilha no histórico.
 */

struct DSURollback {
  int n, num_sets;
  vector<int> parent, sz;
  vector<pair<int,int>> history;

  DSURollback(int n) : n(n), num_sets(n), parent(n), sz(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    while (parent[i] != i) i = parent[i];
    return i;
  }

  bool join(int i, int j) {
    i = find(i); j = find(j);
    if (i == j) { history.push_back({-1, -1}); return false; }
    if (sz[i] < sz[j]) swap(i, j);
    parent[j] = i;
    sz[i] += sz[j];
    num_sets--;
    history.push_back({j, i});
    return true;
  }

  void rollback() {
    auto [child, p] = history.back();
    history.pop_back();
    if (child != -1) {
      sz[p] -= sz[child];
      parent[child] = child;
      num_sets++;
    }
  }

  int size(int i) { return sz[find(i)]; }
  bool same(int i, int j) { return find(i) == find(j); }
};
