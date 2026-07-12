#pragma once
#include <bits/stdc++.h>
using namespace std;

/* DSU (Disjoint Set Union / Union-Find)
 * Mantém conjuntos disjuntos com união e busca eficiente.
 * Complexidade: O(α(N)); α é a inversa de Ackermann.
 * Memória: O(N)
 * Métodos:
 * - find(i): Retorna o representante do conjunto de i.
 * - join(i, j): Une os conjuntos de i e j, retorna true se uniu.
 * - same(i, j): Verifica se i e j estão no mesmo conjunto.
 * - size(i): Retorna o tamanho do conjunto de i.
 */

struct DSU {
  int n;
  vector<int> parent;
  vector<int> sz;
  int num_sets;

  DSU(int _n) : n(_n), parent(_n), sz(_n, 1), num_sets(_n) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }

  bool join(int i, int j) {
    i = find(i), j = find(j);
    if (i != j) {
      if (sz[i] < sz[j]) swap(i, j);
      parent[j] = i;
      sz[i] += sz[j];
      num_sets--;
      return true;
    }
    return false;
  }

  int size(int i) { return sz[find(i)]; }
  bool same(int i, int j) { return find(i) == find(j); }
};
