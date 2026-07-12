#pragma once
#include "tarjan.hpp"

/* 2-SAT — Complexidade: O(V + E)
 *
 * Literal x: use i para x_i=true, ~i para x_i=false.
 *
 *   add_impl(x, y) → x → y e contrapositiva ~y → ~x
 *   add_or(x, y)    → x ∨ y
 *   add_xor(x, y)   → exatamente um de x, y é true
 *   add_iff(x, y)   → x ↔ y
 *   force(x)        → x = true
 *   solve()         → {satisfatível, ans[]}; ans[i] = 0 ou 1
 */

struct TwoSat {
  int n;
  Tarjan t;
  vector<int> ans;

  TwoSat(int n) : n(n), t(2 * n), ans(n, -1) {}

  // Converte i em 2*i e ~i em 2*i+1.
  static int node(int x) { return x >= 0 ? 2 * x : -2 * x - 1; }

  // implicação x → y (e contrapositiva ~y → ~x)
  void add_impl(int x, int y) {
    int nx = node(x), ny = node(y);
    t.add_edge(nx, ny);
    t.add_edge(ny ^ 1, nx ^ 1);
  }

  // x ∨ y
  void add_or(int x, int y) { add_impl(~x, y); }

  // x XOR y (exatamente um verdadeiro)
  void add_xor(int x, int y) {
    add_or(x, y);
    add_or(~x, ~y);
  }

  // x ↔ y
  void add_iff(int x, int y) {
    add_impl(x, y);
    add_impl(~x, ~y);
  }

  // força x = true
  void force(int x) { add_impl(~x, x); }

  pair<bool, vector<int>> solve() {
    t.build();
    ans.assign(n, -1);
    for (int i = 0; i < n; i++) {
      if (t.comp[2 * i] == t.comp[2 * i + 1]) return {false, {}};
      ans[i] = t.comp[2 * i] < t.comp[2 * i + 1] ? 1 : 0;
    }
    return {true, ans};
  }
};
