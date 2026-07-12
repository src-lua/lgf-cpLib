#pragma once
#include <bits/stdc++.h>
#include "../../data-structures/segment-tree/lazy-segment-tree.hpp"
using namespace std;

/* HLD Não-Comutativo com Lazy Propagation
 * Para merge(A, B) != merge(B, A), como matrizes.
 * DoubleNode guarda as ordens normal e invertida do merge.
 */

template <typename NODE>
struct DoubleNode {
  NODE down, up;

  DoubleNode() : down(NODE()), up(NODE()) {}
  DoubleNode(const NODE &n) : down(n), up(n) {}
  DoubleNode(const NODE &d, const NODE &u) : down(d), up(u) {}

  static DoubleNode merge(const DoubleNode &l,
                          const DoubleNode &r) {
    return {NODE::merge(l.down, r.down),
            NODE::merge(r.up, l.up)};
  }

  template <typename TAG>
  void apply(const TAG &t, int l, int r) {
    down.apply(t, l, r);
    up.apply(t, l, r);
  }
};

template <typename NODE, typename TAG>
struct HLD {
  int n, t;
  vector<int> p, sz, d, head, pos;
  LazySegmentTree<DoubleNode<NODE>, TAG> st;

  HLD(const vector<vector<int>> &adj, const vector<NODE> &vals,
      int root = 0)
      : n(adj.size()), t(0), p(n), sz(n), d(n), head(n), pos(n),
        st(n) {

    vector<vector<int>> g = adj;
    d[root] = 0, p[root] = root;

    auto dfs_sz = [&](auto self, int u) -> void {
      sz[u] = 1;
      int best_v = -1, max_sz = -1;
      for (auto &v : g[u]) {
        if (v == p[u]) continue;
        d[v] = d[u] + 1;
        p[v] = u;
        self(self, v);
        sz[u] += sz[v];
        if (sz[v] > max_sz) {
          max_sz = sz[v];
          best_v = v;
        }
      }
      if (best_v != -1) {
        for (int i = 0; i < (int)g[u].size(); i++) {
          if (g[u][i] == best_v && i != 0) {
            swap(g[u][0], g[u][i]);
            break;
          }
        }
      }
    };

    auto dfs_hld = [&](auto self, int u) -> void {
      pos[u] = t++;
      for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == p[u]) continue;
        head[v] = (i == 0 ? head[u] : v);
        self(self, v);
      }
    };

    dfs_sz(dfs_sz, root);
    head[root] = root;
    dfs_hld(dfs_hld, root);

    vector<DoubleNode<NODE>> base(n);
    for (int i = 0; i < n; i++)
      base[pos[i]] = DoubleNode<NODE>(vals[i]);
    st = LazySegmentTree<DoubleNode<NODE>, TAG>(base);
  }

  void update_path(int u, int v, const TAG &tag) {
    while (head[u] != head[v]) {
      if (d[head[u]] > d[head[v]]) {
        st.update(pos[head[u]], pos[u], tag);
        u = p[head[u]];
      } else {
        st.update(pos[head[v]], pos[v], tag);
        v = p[head[v]];
      }
    }
    if (d[u] > d[v]) st.update(pos[v], pos[u], tag);
    else st.update(pos[u], pos[v], tag);
  }

  NODE query_path(int u, int v) {
    NODE l, r;
    while (head[u] != head[v]) {
      if (d[head[u]] > d[head[v]]) {
        l = NODE::merge(l, st.query(pos[head[u]], pos[u]).up);
        u = p[head[u]];
      } else {
        r = NODE::merge(st.query(pos[head[v]], pos[v]).down, r);
        v = p[head[v]];
      }
    }
    if (d[u] > d[v]) {
      l = NODE::merge(l, st.query(pos[v], pos[u]).up);
    } else {
      r = NODE::merge(st.query(pos[u], pos[v]).down, r);
    }
    return NODE::merge(l, r);
  }

  void update_subtree(int u, const TAG &tag) {
    st.update(pos[u], pos[u] + sz[u] - 1, tag);
  }

  NODE query_subtree(int u) {
    return st.query(pos[u], pos[u] + sz[u] - 1).down;
  }
};
