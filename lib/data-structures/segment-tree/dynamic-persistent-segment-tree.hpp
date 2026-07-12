#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Persistent Dynamic Segment Tree (Point Update, Range Query)
 * Consulta versões anteriores e aloca nós sob demanda.
 * Ideal para intervalos grandes e múltiplas versões.
 * Complexidade: O(log N) por update e query.
 * Memória: O(Q log N) onde Q é o número de updates.
 * Requisitos:
 * - NODE deve ter: static merge(const NODE&, const NODE&) e
 *   construtor identidade.
 */

/* --- Exemplo de NODE (Soma) ---
struct Node {
    int val;
    Node(int v = 0) : val(v) {}
    static Node merge(const Node& l, const Node& r) {
        return Node(l.val + r.val);
    }
};
*/

template <typename NODE>
struct PersistentSegmentTree {
  struct InternalNode {
    NODE data;
    int l, r;
    InternalNode() : data(NODE()), l(0), r(0) {}
  };

  int N;
  vector<InternalNode> st;
  vector<int> roots;

  PersistentSegmentTree(int n) : N(n) {
    st.reserve(4e6);
    st.emplace_back();
    roots.push_back(0);
  }

  int update(int root, int L, int R, int idx, NODE v) {
    int node = st.size();
    if (root == 0) st.emplace_back();
    else st.push_back({st[root]});

    if (L == R) {
      st[node].data = NODE::merge(st[node].data, v);
      return node;
    }

    int mid = L + (R - L) / 2;

    // A ordem do LHS importa antes do C++17.
    if (idx <= mid) {
      int prev = (root == 0) ? 0 : st[root].l;
      st[node].l = update(prev, L, mid, idx, v);
    } else {
      int prev = (root == 0) ? 0 : st[root].r;
      st[node].r = update(prev, mid + 1, R, idx, v);
    }

    auto& nd = st[node];
    nd.data = NODE::merge(st[nd.l].data, st[nd.r].data);
    return node;
  }

  NODE query(int node, int L, int R, int i, int j) {
    if (node == 0 || i > R || j < L) return NODE();
    if (i <= L && R <= j) return st[node].data;
    int mid = L + (R - L) / 2;
    return NODE::merge(query(st[node].l, L, mid, i, j),
                       query(st[node].r, mid + 1, R, i, j));
  }

  void update(int idx, NODE v) {
    roots.push_back(update(roots.back(), 0, N - 1, idx, v));
  }

  NODE query(int version, int l, int r) {
    return query(roots[version], 0, N - 1, l, r);
  }
};
