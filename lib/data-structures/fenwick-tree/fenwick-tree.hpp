#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Fenwick Tree (Point Update, Prefix Query)
 * Realiza atualizações pontuais e consultas de prefixo.
 * Complexidade: O(log N) para update e query.
 * Memória: O(N)
 * Requisitos:
 * - NODE: operator+=, operator- e construtor default.
 */

/* --- Exemplo de NODE (Soma) ---
struct Node {
    ll val;
    Node(ll v = 0) : val(v) {}
    void operator+=(const Node& other) { val += other.val; }
    Node operator-(const Node& other) const {
        return Node(val - other.val);
    }
};
*/

template <typename NODE>
struct FenwickTree {
  int N;
  vector<NODE> bit;

  FenwickTree(int n) : N(n), bit(n + 1) {}

  void update(int idx, NODE v) {
    for (idx++; idx <= N; idx += idx & -idx) {
      bit[idx] += v;
    }
  }

  NODE query(int idx) { // [0, idx]
    NODE res;
    for (idx++; idx > 0; idx -= idx & -idx) {
      res += bit[idx];
    }
    return res;
  }

  NODE query(int l, int r) { // [l, r]
    if (l > r) return NODE();
    return query(r) - query(l - 1);
  }
};
