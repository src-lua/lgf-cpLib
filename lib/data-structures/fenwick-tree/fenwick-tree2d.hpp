#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Fenwick Tree 2D (Point Update, Rectangle Query)
 * Atualizações pontuais e consultas de prefixo em matrizes.
 * Complexidade: O(log N * log M) para update e query.
 * Memória: O(N * M)
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
struct FenwickTree2D {
  int N, M;
  vector<vector<NODE>> bit;

  FenwickTree2D(int n, int m)
      : N(n), M(m), bit(n + 1, vector<NODE>(m + 1)) {}

  void update(int r, int c, NODE v) { // point update
    for (int i = r + 1; i <= N; i += i & -i) {
      for (int j = c + 1; j <= M; j += j & -j) {
        bit[i][j] += v;
      }
    }
  }

  NODE query(int r, int c) { // [(0,0), (r,c)]
    NODE res;
    for (int i = r + 1; i > 0; i -= i & -i) {
      for (int j = c + 1; j > 0; j -= j & -j) {
        res += bit[i][j];
      }
    }
    return res;
  }

  // Retângulo fechado [(r1,c1), (r2,c2)].
  NODE query(int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return NODE();
    return query(r2, c2) - query(r1 - 1, c2) -
           query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
  }
};
